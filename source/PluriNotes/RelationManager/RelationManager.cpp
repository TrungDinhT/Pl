#include "RelationManager.h"
#include "exception.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QFileDialog>
#include "NoteManager/NoteManager.h"

NotesManager& NM = NotesManager::getManager();

RelationsManager* RelationsManager::instance = nullptr;

RelationsManager& RelationsManager::getInstance(){
    if (!instance)
    {
        instance=new RelationsManager;
        QString location = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        instance->setFileName(location+"/relationslog.xml");
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
        stream.writeStartElement("couples");
        for(relation::Iterator c = relations[i]->begin(); c!=relations[i]->end(); c++)
        {
            stream.writeStartElement("couple");
            stream.writeTextElement("Label",(*c)->label);
            stream.writeTextElement("fromNote ID",(*c)->getFromNote()->getId());
            stream.writeTextElement("toNote ID",(*c)->getToNote()->getId());
            stream.writeEndElement();
        }
        stream.writeEndElement();
        stream.writeEndElement();
    }
    stream.writeEndDocument();
    newfile.close();
}

void RelationsManager::load(){
    QFile file(filename);

    // If we can't open it, show an error message.
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw _Exception("Error : cannot open file");

    int countRela = -1;
    QXmlStreamReader stream(&file);
    while(!stream.atEnd() && !stream.hasError())
    {
        countRela++;
        QXmlStreamReader::TokenType token = stream.readNext();
        if(token == QXmlStreamReader::StartDocument) continue;
        if(token == QXmlStreamReader::StartElement)
        {
            if(stream.name() == "relation")
            {
                qDebug()<<"new relation \n";
                QString titre;
                QString description;
                bool oriente;
                relation* r;
                stream.readNext();
                while(!(stream.tokenType() == QXmlStreamReader::EndElement && stream.name() == "relation"))
                {
                    stream.readNext();
                    if(stream.tokenType()== QXmlStreamReader::StartElement)
                    {
                        if(stream.name() == "titre")
                        {
                            stream.readNext();
                            titre=stream.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        if(stream.name() == "description")
                        {
                            stream.readNext();
                            description=stream.text().toString();
                            qDebug()<<"description="<<description<<"\n";
                        }
                        if(stream.name() == "orientation")
                        {
                            stream.readNext();
                            if(stream.text().toString()=="true") oriente=true;
                            else oriente = false;
                            qDebug()<<"oriente="<<oriente<<"\n";
                        }
                        if(stream.name()=="couples")
                        {
                            qDebug()<<"boucle couples\n";
                            if(titre!="\ref")
                                r = new relationNonPreexistance(titre,description,oriente);
                            else
                                r = getRelation("\ref");

                            stream.readNext();
                            while(!(stream.tokenType() == QXmlStreamReader::EndElement && stream.name() == "couples"))
                            {
                                stream.readNext();
                                if(stream.tokenType()==QXmlStreamReader::StartElement)
                                {
                                    if(stream.name()=="couple")
                                    {
                                        QString label;
                                        QString fromNoteID;
                                        QString toNoteID;
                                        qDebug()<<"couple: \n";
                                        stream.readNext();
                                        while(!(stream.tokenType() == QXmlStreamReader::EndElement && stream.name() == "couple"))
                                        {
                                            stream.readNext();
                                            if(stream.tokenType() == QXmlStreamReader::StartElement)
                                            {
                                                if(stream.name() == "Label")
                                                {
                                                    stream.readNext();
                                                    label=stream.text().toString();
                                                    qDebug()<<"label="<<label<<"\n";
                                                }
                                                if(stream.name() == "fromNote ID") \
                                                {
                                                        stream.readNext();
                                                        fromNoteID=stream.text().toString();
                                                        qDebug()<<"fromNote ID="<<fromNoteID<<"\n";
                                                }
                                                if(stream.name() == "toNote ID")
                                                {
                                                    stream.readNext();
                                                    toNoteID=stream.text().toString();
                                                    qDebug()<<"toNote ID="<<toNoteID<<"\n";
                                                }
                                            }
                                        }
                                        r->addCouple(NM.load(fromNoteID),NM.load(toNoteID),label);
                                        qDebug()<<"ajout couple "<<label<<"\n";
                                    }
                                }
                            }
                        }
                    }
                }
                qDebug()<<"ajout relation "<<titre<<"\n";
                if(titre!="\ref") addRelations(r);
            }
        }
    }

    // Error handling.
    if(countRela && stream.hasError()) {
        throw _Exception("Error parsing xml : cannot read file");
    }
    stream.clear();
    qDebug()<<"fin load\n";
}
