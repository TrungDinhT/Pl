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

NotesManager* NotesManager::instance = nullptr;

NotesManager& NotesManager::getManager(){
    if (!instance) instance=new NotesManager;
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

void NotesManager::save(const QString& id) {
    Note* n = new Note(id);
    addNotes(n);
}

NotesManager::~NotesManager(){
    save(); //save all file when exiting the program
    for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
    delete[] notes;
}

Note* NotesManager::getNote(const QString& id){
    // si l'article existe deja, on en renvoie une reference
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) return notes[i];
    }
    // sinon il envoie erreur
    throw _Exception("Error: article not found");
}

void NotesManager::save() const{
    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw _Exception(QString("Error open file xml : cannot save file"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("Notes");
    for(unsigned int i=0;i<nbNotes;i++){
        char type = notes[i]->getId()[0].toLatin1();
        switch(type){
            case 'A': { stream.writeStartElement("article");
                        break;}
            case 'I': { stream.writeStartElement("image");
                        break;}
            case 'T': { stream.writeStartElement("tache");
                        break;}
        }
        stream.writeTextElement("dateCreation",notes[i]->getDateCreation().toString("dd.MM.yyyy-hh:mm:ss"));
        stream.writeTextElement("id",notes[i]->getId());
        switch(notes[i]->getEtat()){
            case ARCHIVE: { stream.writeTextElement("Etat","archive");
                            break;}
            case ACTIVE: { stream.writeTextElement("Etat","active");
                           break;}
            case RIP: { stream.writeTextElement("Etat","rip");
                        break;}
        }
        stream.writeStartElement("Versions");
        for(Note::Iterator it = notes[i]->begin(); it!= notes[i]->end();it++)
        {
            stream.writeTextElement("titre",(*it)->getTitre());
            stream.writeTextElement("dateModification",(*it)->getDateModif().toString("dd.MM.yyyy-hh:mm:ss"));
            switch(type){
                case 'A':{ Article* a = static_cast<Article*>(*it);
                          stream.writeTextElement("text",a->getText());
                          break;
                        }
                /*case 'I':{ Image* a = static_cast<Article*>(*it);
                        }
                case 'T':*/
                default:  break;
            }
        }
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

void NotesManager::load(){
    QFile fichier(filename);
    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
            throw _Exception("Erreur ouverture fichier notes");
    }
    QXmlStreamReader stream(&fichier);
    int i = -1;
    while(!stream.atEnd() && !stream.hasError()) {
        qDebug()<<"Debut\n";
        QXmlStreamReader::TokenType token = stream.readNext();
        if(token == QXmlStreamReader::StartDocument) continue;
        if(token == QXmlStreamReader::StartElement) {
            if(stream.name() == "Notes") continue;
            if(stream.name() == "article") {
                qDebug()<<"new article\n";
                QString id;
                QDateTime dateCrea;
                EtatNote etat;
                stream.readNext();
                if(stream.tokenType() == QXmlStreamReader::StartElement) {
                    if(stream.name() == "dateCreation")
                    {
                        stream.readNext();
                        dateCrea = QDateTime::fromString(stream.text().toString(),"dd.MM.yyyy-hh:mm:ss");
                        qDebug()<<"dateCrea="<<dateCrea<<"\n";
                    }
                    if(stream.name() == "id") {
                        stream.readNext();
                        id=stream.text().toString();
                        qDebug()<<"id="<<id<<"\n";
                    }
                    if(stream.name() == "etat") {
                        stream.readNext();
                        QString tempType =stream.text().toString();
                        if(tempType == "archive")
                            etat = ARCHIVE;
                        else if(tempType == "active")
                            etat = ACTIVE;
                        else
                            etat = RIP;
                    }
                    Note* n = new Note(dateCrea,id,etat);
                    if(stream.name() == "Versions"){
                        stream.readNext();
                        QString titre;
                        QDateTime dateModif;
                        QString texte;
                        while(!(stream.tokenType() == QXmlStreamReader::EndElement && (stream.name() == "article" || stream.name() == "tache" || stream.name() == "multimedia" || stream.name() == "Notes" || stream.name()=="Versions"))){
                        //qDebug()<<stream.name();
                            qDebug()<< "boucle version";
                            if(stream.tokenType() == QXmlStreamReader::StartElement) {
                                if(stream.name() == "titre") {
                                    stream.readNext();
                                    titre=stream.text().toString();
                                    qDebug()<<"titre="<<titre<<"\n";
                                }
                                if(stream.name() == "texte") {
                                    stream.readNext();
                                    texte=stream.text().toString();
                                    qDebug()<<"text="<<texte<<"\n";
                                }
                                if(stream.name() == "dateModification") {
                                    stream.readNext();
                                    dateModif = QDateTime::fromString(stream.text().toString(),"dd.MM.yyyy-hh:mm:ss");
                                    qDebug()<<"dateModif="<<dateModif<<"\n";
                                }

                            }
                            stream.readNext();
                            Article* a = new Article(titre,dateModif,texte);
                            n->addVersion(a);
                            i++;
                            qDebug()<<"ajout article "<<titre<<"\n";
                        }
                    }
                    addNotes(n);
                    qDebug()<<"ajout note"<<id<<"\n";
                }
                stream.readNext();
            }
            /*    if(stream.name() == "tache") {
                    qDebug()<<"new tache\n";
                    QString id;
                    QString titre;
                    QDate dateCrea;
                    QDate dateModif;
                    QString action;
                    QDate dateEcheance;
                    qDebug() << dateEcheance;
                    Type_Statut statut;
                    unsigned int priorite;
                    condition co;
                    //QXmlStreamAttributes attributes = stream.attributes();
                    stream.readNext();

                    while(!(stream.tokenType() == QXmlStreamReader::EndElement && (stream.name() == "article" || stream.name() == "tache" || stream.name() == "multimedia" || stream.name() == "Notes"))){
                        //qDebug()<<stream.name();
                        if(stream.tokenType() == QXmlStreamReader::StartElement) {
                            if(stream.name() == "Current")
                            {
                                while((stream.name() != "Memento" && stream.name() != "article" && stream.name() != "tache" && stream.name() != "multimedia"))
                                {
                                    qDebug()<< "boucle current";
                                    qDebug() <<stream.name();
                                    if(stream.tokenType() == QXmlStreamReader::StartElement) {
                                        if(stream.name() == "id") {
                                            stream.readNext();
                                            id=stream.text().toString();
                                            qDebug()<<"id="<<id<<"\n";
                                        }
                                        if(stream.name() == "titre") {
                                            stream.readNext();
                                            titre=stream.text().toString();
                                            qDebug()<<"titre="<<titre<<"\n";
                                        }
                                        if(stream.name() == "action") {
                                            stream.readNext();
                                            action=stream.text().toString();
                                            qDebug()<<"action="<<action<<"\n";
                                        }
                                        if(stream.name() == "dateCrea")
                                        {
                                            stream.readNext();
                                            dateCrea = QDate::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                            qDebug()<<"dateCrea="<<dateCrea<<"\n";
                                        }
                                        if(stream.name() == "dateModif")
                                        {
                                            stream.readNext();
                                            dateModif = QDate::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                            qDebug()<<"dateModif="<<dateModif<<"\n";
                                        }
                                        if(stream.name() == "dateEcheance")
                                        {
                                           stream.readNext();
                                           dateEcheance = QDate::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                           qDebug()<<"dateEcheance="<<dateEcheance<<"\n";
                                        }
                                        if(stream.name() == "statut") {
                                            stream.readNext();
                                            QString tempType =stream.text().toString();
                                            if(tempType == "attente")
                                                statut = En_attente;
                                            else if(tempType == "cours")
                                                statut = En_cours;
                                            else if(tempType == "termine")
                                                statut = termine;
                                        }
                                        if(stream.name() == "priorite"){
                                            stream.readNext();
                                            priorite = stream.text().toInt();
                                            qDebug()<<"priorite="<<priorite<<"\n";
                                        }
                                        if(stream.name() == "etat") {
                                            stream.readNext();
                                            QString tempType =stream.text().toString();
                                            if(tempType == "archive")
                                                co = archive;
                                            else
                                                co = active;
                                        }
                                    }
                                    stream.readNext();
                                }
                                Tache* tache = new Tache(id,titre,action,dateEcheance,dateCrea,dateModif,priorite,statut,co);
                                addNote(tache);
                                i++;
                            }
                            if(stream.name() == "Memento")
                            {
                                while(stream.tokenType() != QXmlStreamReader::EndElement || (stream.name() != "Memento" && stream.name() != "article" && stream.name() != "tache" && stream.name() != "multimedia")){
                                    qDebug()<<"elem memento";
                                    qDebug() << stream.name();
                                    if(stream.tokenType() == QXmlStreamReader::StartElement) {
                                        if(stream.name() == "titre") {
                                            stream.readNext();
                                            titre=stream.text().toString();
                                            qDebug()<<"titre="<<titre<<"\n";
                                        }
                                        if(stream.name() == "action") {
                                            stream.readNext();
                                            action=stream.text().toString();
                                            qDebug()<<"action="<<action<<"\n";
                                        }
                                        if(stream.name() == "dateModif")
                                        {
                                            stream.readNext();
                                            dateModif = QDate::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                            qDebug()<<"dateModif="<<dateModif<<"\n";
                                        }
                                        if(stream.name() == "dateEcheance")
                                        {
                                           stream.readNext();
                                           dateEcheance = QDate::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                           qDebug()<<"dateEcheance="<<dateEcheance<<"\n";
                                        }
                                        if(stream.name() == "statut") {
                                            stream.readNext();
                                            QString tempType =stream.text().toString();
                                            if(tempType == "attente")
                                                statut = En_attente;
                                            else if(tempType == "cours")
                                                statut = En_cours;
                                            else if(tempType == "termine")
                                                statut = termine;
                                        }
                                        if(stream.name() == "priorite"){
                                            stream.readNext();
                                            priorite = stream.text().toInt();
                                            qDebug()<<"priorite="<<priorite<<"\n";
                                        }

                                    }
                                    stream.readNext();
                                }
                                Gardien* mementos = this->ListNotes[i]->getGardien();
                                Memento* memento = new MementoTache(titre,action,dateModif,dateEcheance,statut,priorite);
                                mementos->addMemento(memento);
                            }
                        }
                        stream.readNext();
                    }
                    qDebug()<<"ajout tache "<<id<<"\n";
                }
                if(stream.name() == "multimedia") {
                    qDebug()<<"new multimedia\n";
                    QString id;
                    QString titre;
                    QDate dateCrea;
                    QDate dateModif;
                    QString description;
                    QString fichier;
                    Type_Media type;
                    condition co;

                    //QXmlStreamAttributes attributes = stream.attributes();
                    stream.readNext();

                    while(!(stream.tokenType() == QXmlStreamReader::EndElement && (stream.name() == "article" || stream.name() == "tache" || stream.name() == "multimedia" || stream.name() == "Notes"))){
                        qDebug("coucou");
                        qDebug()<<stream.name();
                        if(stream.tokenType() == QXmlStreamReader::StartElement) {
                            if(stream.name() == "Current")
                            {
                                while((stream.name() != "Memento" && stream.name() != "article" && stream.name() != "tache" && stream.name() != "multimedia"))
                                {
                                    qDebug()<< "boucle current";
                                    qDebug() <<stream.name();
                                    if(stream.tokenType() == QXmlStreamReader::StartElement) {
                                        if(stream.name() == "id") {
                                            stream.readNext();
                                            id=stream.text().toString();
                                            qDebug()<<"id="<<id<<"\n";
                                        }
                                        if(stream.name() == "titre") {
                                            stream.readNext();
                                            titre=stream.text().toString();
                                            qDebug()<<"titre="<<titre<<"\n";
                                        }
                                        if(stream.name() == "description") {
                                            stream.readNext();
                                            description=stream.text().toString();
                                            qDebug()<<"description="<<description<<"\n";
                                        }
                                        if(stream.name() == "dateCrea")
                                        {
                                            stream.readNext();
                                            dateCrea = QDate::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                            qDebug()<<"dateCrea="<<dateCrea<<"\n";
                                        }
                                        if(stream.name() == "dateModif")
                                        {
                                            stream.readNext();
                                            dateModif = QDate::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                            qDebug()<<"dateModif="<<dateModif<<"\n";
                                        }
                                        if(stream.name() == "type") {
                                            stream.readNext();
                                            QString tempType =stream.text().toString();
                                            if(tempType == "video")
                                                type = video;
                                            else if(tempType == "audio")
                                                type = audio;
                                            else if(tempType == "image")
                                                type = image;
                                        }
                                        if(stream.name() == "fichier"){
                                            stream.readNext();
                                            fichier = stream.text().toString();
                                            qDebug()<<"fichier="<<fichier<<"\n";
                                        }
                                        if(stream.name() == "etat") {
                                            stream.readNext();
                                            QString tempType =stream.text().toString();
                                            if(tempType == "archive")
                                                co = archive;
                                            else
                                                co = active;
                                        }
                                    }
                                    stream.readNext();
                                }
                                Multimedia* multimedia = new Multimedia(id,titre,description,fichier,type,dateCrea,dateModif,co);
                                addNote(multimedia);
                                i++;
                            }
                            if(stream.name() == "Memento")
                            {
                                while(stream.tokenType() != QXmlStreamReader::EndElement || (stream.name() != "Memento" && stream.name() != "article" && stream.name() != "tache" && stream.name() != "multimedia")){
                                    qDebug()<<"elem memento";
                                    qDebug() << stream.name();
                                    if(stream.tokenType() == QXmlStreamReader::StartElement) {
                                        if(stream.name() == "titre") {
                                            stream.readNext();
                                            titre=stream.text().toString();
                                            qDebug()<<"titre="<<titre<<"\n";
                                        }
                                        if(stream.name() == "description") {
                                            stream.readNext();
                                            description=stream.text().toString();
                                            qDebug()<<"description="<<description<<"\n";
                                        }
                                        if(stream.name() == "dateModif")
                                        {
                                            stream.readNext();
                                            dateModif = QDate::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                            qDebug()<<"dateModif="<<dateModif<<"\n";
                                        }
                                        if(stream.name() == "type") {
                                            stream.readNext();
                                            QString tempType =stream.text().toString();
                                            if(tempType == "video")
                                                type = video;
                                            else if(tempType == "audio")
                                                type = audio;
                                            else if(tempType == "image")
                                                type = image;
                                        }
                                        if(stream.name() == "fichier"){
                                            stream.readNext();
                                            fichier = stream.text().toString();
                                            qDebug()<<"fichier="<<fichier<<"\n";
                                        }
                                    }
                                    stream.readNext();
                                }
                                Gardien* mementos = this->ListNotes[i]->getGardien();
                                Memento* memento = new MementoMultimedia(titre,description,fichier,type,dateModif);
                                mementos->addMemento(memento);
                            }
                        }
                        stream.readNext();
                    }
                    qDebug()<<"ajout multimedia "<<id<<"\n";
                }
*/


        }
    }
    // Error handling.
    if(stream.hasError()) {
        throw _Exception("Erreur lecteur fichier notes");
    }
    stream.clear();
    qDebug()<<"fin load\n";
}

/*
Note* NotesManager::getNewNote(char type){
    Note* n;
    switch (type) {
    case 'A': n = new Article;
              break;
    case 'I':
    case 'T':
    default:
              break;
    }
    addNotes(n);
    return n;
}

void NotesManager::load() {
    QFile fin(filename);
    // If we can't open it, show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw exception("Error : cannot open file");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next.
            if(xml.name() == "notes") continue;
            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "article") {
                qDebug()<<"new article\n";
                QString identificateur;
                QString titre;
                QString text;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "article")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
                        }

                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found text
                        if(xml.name() == "text") {
                            xml.readNext();
                            text=xml.text().toString();
                            qDebug()<<"text="<<text<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout note "<<identificateur<<"\n";
                addNotes(identificateur,titre,text);
            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw exception("Error parsing xml : cannot read file");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";

}

/*

void NotesManager::addArticle(Article* a){
    for(unsigned int i=0; i<nbArticles; i++){
        if (articles[i]->getId()==a->getId()) throw exception("Error: note already existed");
    }
    if (nbArticles==nbMaxArticles){
        Article** newArticles= new Article*[nbMaxArticles+5];
        for(unsigned int i=0; i<nbArticles; i++) newArticles[i]=articles[i];
        Article** oldArticles=articles;
        articles=newArticles;
        nbMaxArticles+=5;
        if (oldArticles) delete[] oldArticles;
    }
    articles[nbArticles++]=a;
}

void NotesManager::addArticle(const QString& id, const QString& ti, const QString& te){
    for(unsigned int i=0; i<nbArticles; i++){
        if (articles[i]->getId()==id) throw exception("Error : id already existed");
    }
    Article* a=new Article(id,ti,te);
    addArticle(a);
}

Article* NotesManager::getArticle(const QString& id){
    // si l'article existe deja, on en renvoie une reference
    for(unsigned int i=0; i<nbArticles; i++){
        if (articles[i]->getId()==id) return articles[i];
    }
    // sinon il envoie erreur
    throw exception("Error: article not found");
}

Article* NotesManager::getNewArticle(){
    Article* a = new Article;
    addArticle(a);
    return a;
}


NotesManager::NotesManager():articles(nullptr),nbArticles(0),nbMaxArticles(0),filename(""){}

NotesManager::~NotesManager(){
    //if (filename!="") save(); save all file when exiting the program
    for(unsigned int i=0; i<nbArticles; i++) delete articles[i];
    delete[] articles;
}

void NotesManager::save() const {
    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw exception(QString("Error open file xml : cannot save file"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("notes");
    for(unsigned int i=0; i<nbArticles; i++){
        stream.writeStartElement("article");
        stream.writeTextElement("dateCreation",articles[i]->getDateCreation().toString("dd.MM.yyyy-hh:mm:ss"));
        stream.writeTextElement("id",articles[i]->getId());
        stream.writeTextElement("title",articles[i]->getTitle());
        stream.writeTextElement("text",articles[i]->getText());
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

void NotesManager::save(Article *a) const{
    QFile newfile(filename);
    if (!newfile.open(QIODevice::ReadWrite | QIODevice::Text))
        throw exception(QString("Error open file xml : cannot save file"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("notes");

    stream.writeStartElement("article");
    stream.writeTextElement("dateCreation",a->getDateCreation().toString("dd.MM.yyyy-hh:mm:ss"));
    stream.writeTextElement("id",a->getId());
    stream.writeTextElement("title",a->getTitle());
    stream.writeTextElement("text",a->getText());
    stream.writeEndElement();

    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

void NotesManager::load() {
    QFile fin(filename);
    // If we can't open it, show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw exception("Error : cannot open file");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next.
            if(xml.name() == "notes") continue;
            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "article") {
                qDebug()<<"new article\n";
                QString identificateur;
                QString titre;
                QString text;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "article")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
                        }

                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found text
                        if(xml.name() == "text") {
                            xml.readNext();
                            text=xml.text().toString();
                            qDebug()<<"text="<<text<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout note "<<identificateur<<"\n";
                addArticle(identificateur,titre,text);
            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw exception("Error parsing xml : cannot read file");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";

}
*/



