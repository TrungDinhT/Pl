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

    class Iterator: public iterator<relation>{
        friend class RelationsManager;
        Iterator(relation** r, unsigned int n): iterator(r,n){}
    };
    Iterator begin(){ return Iterator(relations,nbRelations); }
    Iterator end(){ return Iterator(relations + nbRelations, nbRelations); }

    class Const_Iterator: public const_iterator<relation>{
        friend class RelationsManager;
        Const_Iterator(relation** r, unsigned int n): const_iterator(r,n){}
    };
    Const_Iterator cbegin(){ return Const_Iterator(relations,nbRelations); }
    Const_Iterator cend(){ return Const_Iterator(relations + nbRelations,nbRelations); }
};

#endif //RELATIONMANAGER_H
