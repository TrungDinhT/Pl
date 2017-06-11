#include "notes.h"

Article::Article(const QString& ti, const QString& te): Version(ti), text(te) {}
//Article::Article(const QString& i, const QString& ti, const QString& te): Note(ti), text(te){ specifyID(); }

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

Version* Note::getVer(const QString& titre){
    // si l'article existe deja, on en renvoie une reference
    for(unsigned int i=0; i<nbVer; i++){
        if (versions[i]->getTitre()==titre) return versions[i];
    }
    // sinon il envoie erreur
    throw _Exception("Error: version not found");
}

Note* Note::getNewNote(const QString &id, Version* v){
    Note* n = new Note(id);
    addVersion(v);
    return n;
}
