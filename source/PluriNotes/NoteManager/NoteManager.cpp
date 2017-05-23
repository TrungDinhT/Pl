/*move note.xml to samples/files => have to modify load and save methods
*/


#include "notes.h"
#include "NoteManager.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QFileDialog>


NotesManager::Handler NotesManager::handler=Handler();

NotesManager& NotesManager::getManager(){
    if (!handler.instance) handler.instance=new NotesManager;
    return *handler.instance;
}

void NotesManager::freeManager(){
    delete handler.instance;
    handler.instance=nullptr;
}

void NotesManager::addArticle(Article* a){
    for(unsigned int i=0; i<nbArticles; i++){
        if (articles[i]->getId()==a->getId()) throw NotesException("Error: note already existed");
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
        if (articles[i]->getId()==id) throw NotesException("Error : id already existed");
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
    throw NotesException("Error: article not found");
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
        throw NotesException(QString("Error open file xml : cannot save file"));
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
        throw NotesException(QString("Error open file xml : cannot save file"));
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
        throw NotesException("Error : cannot open file");
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
        throw NotesException("Error parsing xml : cannot read file");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}


