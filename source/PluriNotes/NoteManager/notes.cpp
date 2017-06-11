#include "notes.h"


void Note::addVersion(Version *v){
    for(unsigned int i=0; i<nbVer; i++){
        if (versions[i]->getTitre()==v->getTitre()) throw _Exception("Error: version already existed");
    }
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
        case ARCHIVE: { stream.writeTextElement("Etat","archive");
                        break;}
        case ACTIVE: { stream.writeTextElement("Etat","active");
                       break;}
        case RIP: { stream.writeTextElement("Etat","rip");
                    break;}
    }
    stream.writeStartElement("Versions");
    for(unsigned int i=0;i<nbVer;i++)
        versions[i]->save(stream);
    stream.writeEndElement();
}

void Article::save(QXmlStreamWriter &stream) const {
    stream.writeStartElement("article");
    stream.writeTextElement("titre",titre);
    stream.writeTextElement("dateModification",dateModif.toString("dd.MM.yyyy-hh:mm:ss"));
    stream.writeTextElement("text",text);
    stream.writeEndElement();
}

void Image::save(QXmlStreamWriter &stream) const {
    stream.writeStartElement("image");
    stream.writeTextElement("titre",titre);
    stream.writeTextElement("dateModification",dateModif.toString("dd.MM.yyyy-hh:mm:ss"));
    stream.writeTextElement("description",description);
    stream.writeTextElement("path to file",nomFichier);
    stream.writeEndElement();
}

void Tache::save(QXmlStreamWriter &stream) const {
    stream.writeStartElement("tache");
    stream.writeTextElement("titre",titre);
    stream.writeTextElement("dateModification",dateModif.toString("dd.MM.yyyy-hh:mm:ss"));
    stream.writeTextElement("action",action);
    stream.writeTextElement("priorite",QString::number(priorite));
    switch(statut){
        case EN_ATTENTE: { stream.writeTextElement("Etat","en attente");
                        break;}
        case EN_COURS: { stream.writeTextElement("Etat","en cours");
                       break;}
        case TERMINE: { stream.writeTextElement("Etat","termine");
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

