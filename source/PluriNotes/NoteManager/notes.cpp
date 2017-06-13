#include "notes.h"


void Note::addVersion(Version *v){
    if (nbVer==nbMaxVer){
        Version** newVer= new Version*[nbMaxVer+5];
        for(unsigned int i=0; i<nbVer; i++) newVer[i]=versions[i];
        Version** oldVer=versions;
        versions=newVer;
        nbMaxVer+=5;
        if (oldVer) delete[] oldVer;
    }
    versions[nbVer++]=v;
}

Note* Note::getNewNote(const QString &id, Version* v){
    Note* n = new Note(id);
    addVersion(v);
    return n;
}

void Note::save(QXmlStreamWriter &stream) const{
    stream.writeTextElement("dateCreation",dateCreation.toString("dd.MM.yyyy-hh:mm:ss"));
    stream.writeTextElement("id",id);
    switch(etat){
        case ARCHIVE: { stream.writeTextElement("etatNote","archive");
                        break;}
        case ACTIVE: { stream.writeTextElement("etatNote","active");
                       break;}
        case RIP: { stream.writeTextElement("etatNote","rip");
                    break;}
    }
    stream.writeStartElement("Versions");
    qDebug()<<"nb Ver: "<<nbVer<<"\n";
    for(unsigned int i=0;i<nbVer;i++)
    {
        versions[i]->save(stream);
        qDebug()<<"add Ver\n";
    }
    stream.writeEndElement();
}

void Article::save(QXmlStreamWriter &stream) const {
    stream.writeStartElement("article");
    stream.writeTextElement("titre",titre);
    stream.writeTextElement("dateModification",dateModif.toString("dd.MM.yyyy-hh:mm:ss"));
    stream.writeTextElement("text",text);
    stream.writeEndElement();
}

void Multimedia::save(QXmlStreamWriter &stream) const {
    stream.writeStartElement("multimedia");
    switch(typeEnregistrement){
        case VIDEO: { stream.writeTextElement("typeEnregistrements","video");
                      break;}
        case IMAGE: { stream.writeTextElement("typeEnregistrements","image");
                      break;}
        case AUDIO: { stream.writeTextElement("typeEnregistrements","audio");
                      break;}
    }
    stream.writeTextElement("titre",titre);
    stream.writeTextElement("dateModification",dateModif.toString("dd.MM.yyyy-hh:mm:ss"));
    stream.writeTextElement("description",description);
    stream.writeTextElement("pathToFile",nomFichier);
    stream.writeEndElement();
}

void Tache::save(QXmlStreamWriter &stream) const {
    stream.writeStartElement("tache");
    stream.writeTextElement("titre",titre);
    stream.writeTextElement("dateModification",dateModif.toString("dd.MM.yyyy-hh:mm:ss"));
    stream.writeTextElement("action",action);
    stream.writeTextElement("priorite",QString::number(priorite));
    switch(statut){
        case EN_ATTENTE: { stream.writeTextElement("etatTache","enAttente");
                        break;}
        case EN_COURS: { stream.writeTextElement("etatTache","enCours");
                       break;}
        case TERMINE: { stream.writeTextElement("etatTache","termine");
                    break;}
    }
    stream.writeTextElement("dateEcheance",dateEcheance.toString("dd.MM.yyyy-hh:mm:ss"));
    stream.writeEndElement();
}

Version* Note::getVer(const QString& titre){
    // si l'article existe deja, on en renvoie une reference
    for(unsigned int i=0; i<nbVer; i++){
        if (versions[i]->getTitre()==titre) return versions[i];
    }
    // sinon il envoie erreur
    throw _Exception("Error: version not found");
}

