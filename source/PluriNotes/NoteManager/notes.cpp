#include "notes.h"
#include <QString>

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


void Note::setVersionActive(Version *v){//çàd la fait passer en dernier
    for(unsigned int k=0; k<nbVer-1; k++){
        if(versions[k]==v){
            Version* temp = versions[nbVer-1];
            versions[nbVer-1] = v;
            versions[k] = temp;
        }
    }
}
Version* Note::VersionActive(){///< c'est à dire la fait passer en dernier version
    return versions[nbVer-1];
}

Version* Note::getVer(const QString& titre){
    for(unsigned int i=0; i<nbVer; i++){
        if (versions[i]->getTitre()==titre) return versions[i];
    }
    throw _Exception("Error: version not found");
}


Version* Note::getVerParDate(const QString& date){
    for(unsigned int i=0; i<nbVer; i++){
        if (versions[i]->getDateModif().toString("dd.MM.yyyy-hh:mm:ss")==date) return versions[i];
    }
    throw _Exception("Error: version not found");
}

Note* Note::getNewNote(const QString &id, Version* v){
    Note* n = new Note(id);
    n->addVersion(v);
    return n;
}

void Note::afficher(QString &contenu) const {
    contenu += "--------------------------------------------- \nid de note: " + id +" \n" +
            "date de creation: " + dateCreation.toString("dd.MM.yyyy-hh:mm:ss") + " \n";
    versions[nbVer-1]->afficher(contenu);
}

void Article::afficher(QString &contenu) const{
    contenu += "date de derniere modification: " + dateModif.toString("dd.MM.yyyy-hh:mm:ss") + " \n" +
            "type de note: Article \n" +
            "titre: " + titre +  " \n" +
            "text: " + text + " \n" +
            "--------------------------------------------- \n";
}

void Multimedia::afficher(QString &contenu) const{
    QString typeMedia;
    switch(typeEnregistrement){
        case AUDIO: { typeMedia = "AUDIO";
                      break;
                    }
        case IMAGE: { typeMedia = "IMAGE";
                      break;
                    }
        case VIDEO: { typeMedia = "VIDEO";
                      break;
                    }
    }
    contenu += "date de derniere modification: " + dateModif.toString("dd.MM.yyyy-hh:mm:ss") + " \n" +
            "type de note: Multimedia \n" +
            "titre: " + titre +  " \n" +
            "type multimedia: " + typeMedia + " \n" +
            "nom de fichier media: " + nomFichier + " \n" +
            "description: " + description + " \n" +
            "--------------------------------------------- \n";
}

void Tache::afficher(QString &contenu) const{
    QString etat;
    switch(statut){
        case EN_ATTENTE: { etat = "EN ATTENTE";
                           break;
                         }
        case EN_COURS: { etat = "EN COURS";
                         break;
                       }
        case TERMINE: { etat = "TERMINE";
                        break;
                      }
    }
    contenu += "date de derniere modification: " + dateModif.toString("dd.MM.yyyy-hh:mm:ss") + " \n" +
            "type de note: Tache \n" +
            "titre: " + titre +  " \n" +
            "etat de tache: " + etat + " \n" +
            "action: " + action + " \n" +
            "priorite: " + QString::number(priorite) + " \n" +
            "date d'echeance du tache: " + dateEcheance.toString("dd.MM.yyyy") + " \n" +
            "--------------------------------------------- \n";
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
    stream.writeTextElement("dateEcheance",dateEcheance.toString("dd.MM.yyyy"));
    stream.writeEndElement();
}

