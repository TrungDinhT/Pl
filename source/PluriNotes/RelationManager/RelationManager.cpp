#include "RelationManager.h"
#include "exception.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QFileDialog>
#include "NoteManager/NoteManager.h"

static NotesManager& NM = NotesManager::getManager();

RelationsManager* RelationsManager::instance = nullptr;

RelationsManager& RelationsManager::getInstance(){
    if (!instance)
    {
        instance=new RelationsManager;
        QString location = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        instance->setFileName(location+"relationslog.xml");
        instance->load();
    }
    return *instance;
}

void RelationsManager::freeInstance(){
    delete instance;
    instance=nullptr;
}

void RelationsManager::addRelations(relation *r){
    if(nbRelations==nbMaxRelations){
        relation** newRelations = new relation*[nbMaxRelations+5];
        for(unsigned int i=0;i<nbRelations;i++)
            newRelations[i] = relations[i];
        relation** oldRelations = relations;
        relations = newRelations;
        if(oldRelations) delete[] oldRelations;
        nbMaxRelations +=5;
    }
    relations[nbRelations++] = r;
}

relation* RelationsManager::getNewRelation(const QString& titre, const QString& desc, bool ori){
    for(unsigned int i=0;i<nbRelations;i++){
        if(relations[i]->getTitre()==titre) throw _Exception("Error: relation already existed");
    }
    addRelations(new relationNonPreexistance(titre,desc,ori));
}

relation* RelationsManager::getRelation(const QString &titre){
    unsigned int i;
    for(i=0;i<nbRelations && relations[i]->getTitre()!=titre;i++);
    if(i==nbRelations) throw _Exception("Error: relation not found");
    return relations[i];
}

void RelationsManager::deleteRelation(const QString &titre){
    if(titre=="\ref") throw _Exception("Error: cannot delete relation reference");
    unsigned int i;
    for(i=0;i<nbRelations && relations[i]->getTitre()!=titre;i++);
    if(i==nbRelations) throw _Exception("Error: relation not found");
    else{
        delete relations[i];
        for(;i<nbRelations-1;i++) relations[i]=relations[i+1]; //deplacer tous les relations apres cette relation a gauche
    }
    nbRelations--;
}

void RelationsManager::save(){
    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw _Exception(QString("Error open file xml : cannot save file"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    for(unsigned int i=0;i<nbRelations;i++)
    {
        stream.writeStartElement("relation");
        stream.writeTextElement("titre",relations[i]->getTitre());
        stream.writeTextElement("description",relations[i]->getDescription());
        if(relations[i]->getOriente()) stream.writeTextElement("orientation","true");
        else stream.writeTextElement("orientation","false");
        for(relation::Iterator c = relations[i]->begin(); c!=relations[i]->end(); c++){
            stream.writeStartElement("couple");
            stream.writeTextElement("Label",(*c)->label);
            stream.writeTextElement("fromNote ID",(*c)->getFromNote()->getId());
            stream.writeTextElement("toNote ID",(*c)->getToNote()->getId());
            stream.writeEndElement();
        }
        stream.writeEndElement();
    }
    stream.writeEndDocument();
    newfile.close();
}

void RelationsManager::load(){
    QFile file(filename);
    // If we can't open it, show an error message.
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw _Exception("Error : cannot open file");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&file);
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "relation"))
        {
            xml.readNext();
            if(xml.tokenString()== QXmlStreamReader::StartElement){
                QString titre;
                QString description;
                bool oriente;
                //we've found titre
                if(xml.name() == "titre") {
                    xml.readNext();
                    titre=xml.text().toString();
                    qDebug()<<"titre="<<titre<<"\n";
                }
                //we've found description
                if(xml.name() == "description") {
                    xml.readNext();
                    description=xml.text().toString();
                    qDebug()<<"description="<<description<<"\n";
                }
                //we've found oriente
                if(xml.name() == "orientation") {
                    xml.readNext();
                    if(xml.text().toString()=="true") oriente=true;
                    else oriente = false;
                    qDebug()<<"oriente="<<oriente<<"\n";
                }
                relation* r;
                if(titre!="\ref") r = new relationNonPreexistance(titre,description,oriente);
                else r = relations[0];
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named couple.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "couple")) {
                    QString label;
                    QString fromNoteID;
                    QString toNoteID;
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found label.
                        if(xml.name() == "Label") {
                            xml.readNext();
                            label=xml.text().toString();
                            qDebug()<<"label="<<label<<"\n";
                         }
                         // We've found fromNote ID.
                         if(xml.name() == "fromNote ID") {
                            xml.readNext();
                            fromNoteID=xml.text().toString();
                            qDebug()<<"fromNote ID="<<fromNoteID<<"\n";
                         }
                         // We've found toNoteID
                         if(xml.name() == "toNote ID") {
                            xml.readNext();
                            toNoteID=xml.text().toString();
                            qDebug()<<"toNote ID="<<toNoteID<<"\n";
                         }
                    }
                    // ...and next...
                    xml.readNext();
                    qDebug()<<"ajout couple "<<label<<"\n";
                    r->addCouple(NM.load(fromNoteID),NM.load(toNoteID),label);
                }
            qDebug()<<"ajout relation "<<titre<<"\n";
            if(titre!="\ref") addRelations(r);
            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw _Exception("Error parsing xml : cannot read file");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}
