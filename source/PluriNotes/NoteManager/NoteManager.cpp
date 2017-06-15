/*move note.xml to samples/files => have to modify load and save methods
*/


#include "notes.h"
#include "NoteManager.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QFileDialog>
#include "exception.h"
#include "RelationManager/RelationManager.h"
#include "RelationManager/relation.h"

NotesManager* NotesManager::instance = nullptr;

NotesManager& NotesManager::getManager(){
    if (!instance)
    {
        instance=new NotesManager;
        QString location = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        instance->setFilename(location+"/noteslog.xml");
        instance->load();
    }
    return *instance;
}

void NotesManager::freeManager(){
    delete instance;
    instance=nullptr;
}

void NotesManager::addNotes(Note* n){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==n->getId()) throw _Exception("Error: note already existed");
    }
    if (nbNotes==nbMaxNotes){
        Note** newNotes= new Note*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        Note** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    notes[nbNotes++]=n;
}

NotesManager::~NotesManager(){
    save(); //save all file when exiting the program
    for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
    delete[] notes;
}


void NotesManager::deleteNote(const QString &id){
    unsigned int i;
    for(i=0;i<nbNotes && notes[i]->getId()!=id;i++);
    if(i==nbNotes)
        throw _Exception("Note not found");
    relation* ref = RelationsManager::getInstance().getRelation("reference");
    relation::Iterator it;
    for(it=ref->begin();it!=ref->end() && (*it)->getToNote()->getId()!=id; it++); //search for note referencé
    if(it!=ref->end())
    {
        notes[i]->setEtat(ARCHIVE);
    }
    else
    {
        notes[i]->setEtat(RIP);
    }
}

void NotesManager::restaurerNote(const QString &id){
    unsigned int i;
    for(i=0;i<nbNotes && notes[i]->getId()!=id;i++);
    qDebug()<<"arg: "<<id<<", id found: "<<notes[i]->getId()<<"\n";
    notes[i]->setEtat(ACTIVE);
}

void NotesManager::reallyDeleteNote(const QString &id){
    unsigned int i;
    for(i=0;i<nbNotes && notes[i]->getId()!=id;i++);
    delete notes[i];
    nbNotes--;
    if(nbNotes==0)
    {
        delete[] notes;
    }
    else
    {
        for(;i<nbNotes;i++){
            notes[i]=notes[i+1];
        }
    }
    nbNotes--;
}

void NotesManager::viderCorbeille(){
    for(unsigned int i=0;i<nbNotes;i++)
    {
        if(notes[i]->getEtat()==RIP) reallyDeleteNote(notes[i]->getId());
    }
}

void NotesManager::afficher(const QString &idNoteAfficher, QString &contenu) const{
    unsigned int i;
    for(i=0;i<nbNotes && notes[i]->getId()!=idNoteAfficher;i++);
    if(i==nbNotes) throw _Exception("Note to print not found");
    notes[i]->afficher(contenu);
}

void NotesManager::save(const QString& id, Version *v) {
    unsigned int i;
    for(i=0;i<nbNotes&&notes[i]->getId()!=id;i++);
    if(i==nbNotes){
        Note* n = new Note(id);
        addNotes(n);
    }
    notes[i]->addVersion(v);
    qDebug()<<"Version added\n";
}


void NotesManager::save() const{
    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw _Exception(QString("Error open file xml : cannot save file"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("Notes");
    for(unsigned int i=0;i<nbNotes;i++)
    {
        stream.writeStartElement("Note");
        notes[i]->save(stream);
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

Note* NotesManager::load(const QString& id){
    // si l'article existe deja, on en renvoie une reference
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) return notes[i];
    }
    // sinon il envoie erreur
    return nullptr;
}

void NotesManager::load(){
    QFile fichier(filename);
    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
        throw _Exception("Erreur ouverture fichier notes");
    QXmlStreamReader stream(&fichier);
    int countItems=-1;
    while(!stream.atEnd() && !stream.hasError())
    {
        countItems++;
        QXmlStreamReader::TokenType token = stream.readNext();
        if(token == QXmlStreamReader::StartDocument) continue;
        if(token == QXmlStreamReader::StartElement)
        {
            if(stream.name() == "Notes") continue;
            if(stream.name() == "Note")
            {
                qDebug()<<"new Note\n";
                QString id;
                QDateTime dateCrea;
                EtatNote etat;
                stream.readNext();
                Note* n;
                while(!(stream.tokenType()==QXmlStreamReader::EndElement && stream.name()=="Note"))
                {
                    stream.readNext();
                    if(stream.tokenType()==QXmlStreamReader::StartElement)
                    {
                        if(stream.name() == "dateCreation")
                        {
                            stream.readNext();
                            dateCrea = QDateTime::fromString(stream.text().toString(),"dd.MM.yyyy-hh:mm:ss");
                            qDebug()<<"dateCrea="<<dateCrea<<"\n";
                        }
                        if(stream.name() == "id")
                        {
                            stream.readNext();
                            id=stream.text().toString();
                            qDebug()<<"id="<<id<<"\n";
                        }
                        if(stream.name() == "etatNote")
                        {
                            stream.readNext();
                            QString tempType =stream.text().toString();
                            if(tempType == "archive")
                                etat = ARCHIVE;
                            else if(tempType == "active")
                                etat = ACTIVE;
                            else
                                etat = RIP;
                        }
                        if(stream.name() == "Versions")
                        {
                            n = new Note(dateCrea,id,etat);
                            QString titre;
                            QDateTime dateModif;
                            stream.readNext();
                            while(!(stream.tokenType() == QXmlStreamReader::EndElement && stream.name() == "Versions"))
                            {
                                qDebug()<< "boucle version";
                                stream.readNext();

                                //article
                                if(stream.tokenType()==QXmlStreamReader::StartElement)
                                {
                                    if(stream.name()=="article")
                                    {
                                        qDebug()<<"new article\n";
                                        QString texte;
                                        stream.readNext();
                                        while(!(stream.tokenType()==QXmlStreamReader::EndElement && stream.name()=="article"))
                                        {
                                            stream.readNext();
                                            if(stream.tokenType()==QXmlStreamReader::StartElement)
                                            {
                                                if(stream.name() == "titre")
                                                {
                                                    stream.readNext();
                                                    titre=stream.text().toString();
                                                    qDebug()<<"titre="<<titre<<"\n";
                                                }
                                                if(stream.name() == "dateModification")
                                                {
                                                    stream.readNext();
                                                    dateModif = QDateTime::fromString(stream.text().toString(),"dd.MM.yyyy-hh:mm:ss");
                                                    qDebug()<<"dateModif="<<dateModif<<"\n";
                                                }
                                                if(stream.name() == "text")
                                                {
                                                    stream.readNext();
                                                    texte=stream.text().toString();
                                                    qDebug()<<"text="<<texte<<"\n";
                                                }
                                            }
                                        }
                                        Article* a = new Article(titre,dateModif,texte);
                                        n->addVersion(a);
                                        qDebug()<<"ajout article "<<titre<<"\n";
                                    }

                                    //tache
                                    if(stream.name() == "tache")
                                    {
                                        qDebug()<<"new tache\n";
                                        QString act;
                                        unsigned int prior;
                                        EtatTache status;
                                        QDateTime dateEch;
                                        stream.readNext();
                                        while(!(stream.tokenType()==QXmlStreamReader::EndElement && stream.name()=="tache"))
                                        {
                                            stream.readNext();
                                            if(stream.tokenType()==QXmlStreamReader::StartElement)
                                            {
                                                if(stream.name() == "titre")
                                                {
                                                    stream.readNext();
                                                    titre=stream.text().toString();
                                                    qDebug()<<"titre="<<titre<<"\n";
                                                }
                                                if(stream.name() == "dateModification")
                                                {
                                                    stream.readNext();
                                                    dateModif = QDateTime::fromString(stream.text().toString(),"dd.MM.yyyy-hh:mm:ss");
                                                    qDebug()<<"dateModif="<<dateModif<<"\n";
                                                }
                                                if(stream.name() == "action")
                                                {
                                                    stream.readNext();
                                                    act=stream.text().toString();
                                                    qDebug()<<"action="<<act<<"\n";
                                                }
                                                if(stream.name() == "priorite")
                                                {
                                                    stream.readNext();
                                                    prior=stream.text().toInt();
                                                    qDebug()<<"priorite="<<prior<<"\n";
                                                }
                                                if(stream.name() == "etatTache")
                                                {
                                                    stream.readNext();
                                                    QString sta=stream.text().toString();
                                                    if(sta=="enAttente")
                                                        status = EN_ATTENTE;
                                                    else if(sta=="enCours")
                                                        status = EN_COURS;
                                                    else
                                                        status = TERMINE;
                                                    qDebug()<<"etatTache="<<status<<"\n";
                                                }
                                                if(stream.name() == "dateEcheance")
                                                {
                                                    stream.readNext();
                                                    dateEch = QDateTime::fromString(stream.text().toString(),"dd.MM.yyyy");
                                                    qDebug()<<"dateEcheance="<<dateEch<<"\n";
                                                }
                                            }
                                        }
                                        Tache* t = new Tache(titre,dateModif,dateEch,act,prior,status);
                                        n->addVersion(t);
                                        qDebug()<<"ajout tache "<<titre<<"\n";
                                    }

                                    //multimedia
                                    if(stream.tokenType() == QXmlStreamReader::StartElement && stream.name() == "multimedia")
                                    {
                                        qDebug()<<"new multimedia\n";
                                        Media typeMedia;
                                        QString descript;
                                        QString pathName;
                                        stream.readNext();
                                        while(!(stream.tokenType()==QXmlStreamReader::EndElement && stream.name()=="multimedia"))
                                        {
                                            stream.readNext();
                                            if(stream.tokenType()==QXmlStreamReader::StartElement)
                                            {
                                                if(stream.tokenType() == QXmlStreamReader::StartElement && stream.name() == "titre")
                                                {
                                                    stream.readNext();
                                                    titre=stream.text().toString();
                                                    qDebug()<<"titre="<<titre<<"\n";
                                                }
                                                if(stream.tokenType() == QXmlStreamReader::StartElement && stream.name() == "dateModification")
                                                {
                                                    stream.readNext();
                                                    dateModif = QDateTime::fromString(stream.text().toString(),"dd.MM.yyyy-hh:mm:ss");
                                                    qDebug()<<"dateModif="<<dateModif<<"\n";
                                                }
                                                if(stream.tokenType() == QXmlStreamReader::StartElement && stream.name() == "typeEnregistrements")
                                                {
                                                    stream.readNext();
                                                    QString typeMed=stream.text().toString();
                                                    if(typeMed=="video")
                                                        typeMedia = VIDEO;
                                                    else if(typeMed=="image")
                                                        typeMedia = IMAGE;
                                                    else
                                                        typeMedia = AUDIO;
                                                    qDebug()<<"typeEnregistrements"<<typeMedia<<"\n";
                                                }
                                                if(stream.tokenType() == QXmlStreamReader::StartElement && stream.name() == "description")
                                                {
                                                    stream.readNext();
                                                    descript=stream.text().toString();
                                                    qDebug()<<"description"<<descript<<"\n";
                                                }
                                                if(stream.tokenType() == QXmlStreamReader::StartElement && stream.name() == "pathToFile")
                                                {
                                                    stream.readNext();
                                                    pathName=stream.text().toString();
                                                    qDebug()<<"pathToFile="<<pathName<<"\n";
                                                }
                                            }
                                        }
                                        Multimedia* m = new Multimedia(titre,dateModif,pathName,descript);
                                        n->addVersion(m);
                                        qDebug()<<"ajout multimedia "<<titre<<"\n";
                                    }
                                }
                            }
                        }
                    }
                }
                addNotes(n);
                qDebug()<<"ajout note"<<id<<"\n";
            }
        }
    }
    // Error handling.
    if(countItems && stream.hasError())
        throw _Exception("Erreur lecteur fichier notes");
    stream.clear();
    qDebug()<<"fin load\n";
}

