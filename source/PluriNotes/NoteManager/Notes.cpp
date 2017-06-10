#include "Notes.h"

NoteManager* NoteManager::instance;

NoteManager& NoteManager::getManager(){
    if (!instance) instance=new NoteManager;
    return *instance;
}

void NoteManager::freeManager(){
    delete instance;
    instance=NULL;
}

void NoteManager::addNote(Note* n){
	for(unsigned int i=0; i<nbNotes; i++){
		if (notes[i]->getId()==n->getId()) throw NotesException("error, creation of an already existent note");
	}
	if (nbNotes==nbNotesMax){
		Note** newNotes= new Note*[nbNotesMax+5];
		for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
		Note** oldNotes=notes;
		notes=newNotes;
		nbNotesMax+=5;
		if (oldNotes) delete[] oldNotes;
	}
	notes[nbNotes++]=n;
}

void NoteManager::addNote(const string& ti){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("Erreur : identificateur d�j� existant");
    }
    Note* n=new Note(ti);
    addNote(n);
}

Note& NoteManager::getNote(const string& id){
    // si l'article existe d�j�, on en renvoie une r�f�rence
    for(unsigned int i=0; i<nbNotes; i++){
		if (notes[i]->getId()==id) return *notes[i];
	}
    // sinon il est cr��
    Note* n=new Note("");
    addNote(n);
    return *n;
}

NoteManager::NoteManager():notes(NULL),nbNotes(0),nbNotesMax(0),filename(""){}

NoteManager::~NoteManager(){
    if (filename!="") save();
	for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
	delete[] notes;
}

/*
void NoteManager::save() const {
    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("notes");
    for(unsigned int i=0; i<nbNotes; i++){
        stream.writeStartElement("note");
        stream.writeTextElement("id",notes[i]->getId());
        stream.writeTextElement("title",notes[i]->getTitle());
        stream.writeTextElement("text",notes[i]->getText());
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

void NotesManager::load() {
    QFile fin(filename);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw NotesException("Erreur ouverture fichier notes");
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
            if(xml.name() == "note") {
                qDebug()<<"new note\n";
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
        throw NotesException("Erreur lecteur fichier notes, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}
*/

/*
void Note::addVersion(Version* v){
	for(unsigned int i=0; i<nbVersions; i++){
		if (versions[i]->getId()==v->getId()) throw NotesException("error, creation of an already existent note");
	}
	if (nbVersions==nbVersionsMax){
		Version** newVersions= new Version*[nbVersionsMax+5];
		for(unsigned int i=0; i<nbVersions; i++) newVersions[i]=versions[i];
		Version** oldVersions=versions;
		versions=newVersions;
		nbVersionsMax+=5;
		if (oldVersions) delete[] oldVersions;
	}
	versions[nbVersions++]=v;
}

void Note::addVersion(const string& ti){
    for(unsigned int i=0; i<nbVersions; i++){
        if (versions[i]->getId()==id) throw NotesException("Erreur : identificateur d�j� existant");
    }
    Version* v=new Version(ti);
    addVersion(v);
}

Version& Note::getVersion(const string& id){
    // si l'article existe d�j�, on en renvoie une r�f�rence
    for(unsigned int i=0; i<nbVersions; i++){
		if (versions[i]->getId()==id) return *versions[i];
	}
    // sinon il est cr��
    Version* v=new Version("");
    addVersion(v);
    return *v;
}
*/

Note::~Note(){
	for(unsigned int i=0; i<nbVersions; i++) delete versions[i];
	delete[] versions;
}

/*
void NoteManager::save() const {
    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("versions");
    for(unsigned int i=0; i<nbVersions; i++){
        stream.writeStartElement("note");
        stream.writeTextElement("id",versions[i]->getId());
        stream.writeTextElement("title",versions[i]->getTitle());
        stream.writeTextElement("text",versions[i]->getText());
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

void NotesManager::load() {
    QFile fin(filename);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw NotesException("Erreur ouverture fichier notes");
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
            if(xml.name() == "version") {
                qDebug()<<"new version\n";
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
        throw NotesException("Erreur lecteur fichier notes, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}
*/
