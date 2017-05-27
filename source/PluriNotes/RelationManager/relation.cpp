#include "relation.h"
#include "exception.h"

static relationPreexistance* relationPreexistance::instance = nullptr;

relationPreexistance& relationPreexistance::getInstance(){
    if (!instance) instance=new relationPreexistance;
    return *instance;
}

void relationPreexistance::freeInstance(){
    delete instance;
    instance=nullptr;
}

void relation::addCouple(couple* c){
    if(nbCouples==nbMaxCouples){
        couple** newCouples = new couples*[nbMaxCouples+5];
        for(unsigned int i=0;i<nbCouples;i++)
            newCouples[i] = couples[i];
        couple** oldCouples = couples;
        couples = newCouples;
        if(oldCouples) delete[] oldCouples;
        nbMaxCouples +=5;
    }
    couples[nb++] = c;
}

void relation::deleteCouple(couple *c){
    unsigned int i;

    //trouver la position de couple c dans le tableau de couple
    for(i=0;i<nbCouples&&couples[i]!=c;i++)
    if(i==nbCouples) throw exception("Error: couple not found");
    //deplacer tous les couples apres cet couple a gauche
    else for(;i<nbCouples-1;i++) couples[i]=couples[i+1];

    nbCouples--;
}
