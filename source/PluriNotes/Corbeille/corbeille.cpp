#include "corbeille.h"


corbeille* corbeille::instance = nullptr;

corbeille& corbeille::getCorbeille(){
    if (!instance)
        instance=new corbeille;
    return *instance;
}

void corbeille::freeCorbeille(){
    delete instance;
    instance=nullptr;
}

void corbeille::addNotes(Note* n){
    for(unsigned int i=0; i<nbNotes; i++){
        if (deletedNotes[i]->getId()==n->getId()) throw _Exception("Error: note already existed");
    }
    if (nbNotes==nbMaxNotes){
        Note** newNotes= new Note*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=deletedNotes[i];
        Note** oldNotes=deletedNotes;
        deletedNotes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    deletedNotes[nbNotes++]=n;
}

corbeille::~corbeille(){
    for(unsigned int i=0; i<nbNotes; i++) delete deletedNotes[i];
    delete[] deletedNotes;
}

void corbeille::restaurerNote(const QString &id){
    unsigned int i;
    for(i=0;i<nbNotes && deletedNotes[i]->getId()!=id;i++);
    if(i==nbNotes)
        throw _Exception("note not found");
    else
    {
        deletedNotes[i]->setEtat(ACTIVE);

        //mettre a jour liste de notes supprime
        for(;i<nbNotes-1;i++)
            deletedNotes[i]=deletedNotes[i+1];
        nbNotes--;
    }
}

void corbeille::viderCorbeille(){
    NotesManager& nman = NotesManager::getManager();
    for(unsigned int i=0;i<nbNotes;i++)
    {
        unsigned int j;
        for(j=0;j<nman.nbNotes && nman.notes[j]->getId()!=deletedNotes[i]->getId();j++);
        delete deletedNotes[i];
        for(;j<nman.nbNotes-1;j++)
            nman.notes[j]=nman.notes[j+1];
        nman.nbNotes--;
    }
    delete[] deletedNotes;
}
