#ifndef RELATIONMANAGER_H
#define RELATIONMANAGER_H

#include "relation.h"
#include "iterator.h"
#include "exception.h"

class RelationsManager{
private:

    relation** relations;
    unsigned int nbRelations;
    unsigned int nbMaxRelations;
    void addRelations(relation* r);

    static RelationsManager* instance; // pointeur sur l'unique instance
    RelationsManager(): relations(new relation*[1]),nbRelations(1),nbMaxRelations(1){
        relations[0]= relationPreexistance::getInstance();
    }
    ~RelationsManager(){
        for(unsigned int i=0;i<nbRelations;i++)
            delete relations[i];
        delete[] relations;
    }
    RelationsManager(const RelationsManager& m);
    RelationsManager& operator=(const RelationsManager& m);

public:

    relation& getRelation(const QString& titre);
    relation& getNewRelation(const QString& titre, const QString& desc, bool ori=true);

    void deleteRelation(const QString& titre);

    static RelationsManager& getInstance();
    static void freeInstace(); // free the memory used by the RelationsManager; it can be rebuilt later

    void load(const QString& filename);
    void save(const QString &filename); //filename = name + path to save

    class iterator<relation, RelationsManager>;
    iterator<relation, RelationsManager> beginIt(){ return iterator<relation, RelationsManager>(relations); }
    iterator<relation, RelationsManager> endIt(){ return iterator<relation, RelationsManager>(relations + nbRelations); }

    class const_iterator<relation, RelationsManager>;
    const_iterator<relation, RelationsManager> beginIt(){ return const_iterator<relation, RelationsManager>(relations); }
    const_iterator<relation, RelationsManager> endIt(){ return const_iterator<relation, RelationsManager>(relations + nbRelations); }
};

#endif //RELATIONMANAGER_H
