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
    QString filename;

    static RelationsManager* instance; // pointeur sur l'unique instance
    RelationsManager(): relations(nullptr),nbRelations(0),nbMaxRelations(0){}
    ~RelationsManager(){
        for(unsigned int i=0;i<nbRelations;i++)
            delete relations[i];
        delete[] relations;
    }
    RelationsManager(const RelationsManager& m);
    RelationsManager& operator=(const RelationsManager& m);

public:

    relation* getRelation(const QString& titre);
    relation* getNewRelation(const QString& titre, const QString& desc, bool ori=true);

    void deleteRelation(const QString& titre);

    static RelationsManager& getInstance();
    static void freeInstance(); // free the memory used by the RelationsManager; it can be rebuilt later

    void setFileName(const QString f) { filename = f; }
    const QString& getFileName () const { return filename; }
    int load();
    void save(); //filename = name + path to save

    //iterator et parcourir
    class Iterator: public _Iterator<relation>{
        friend class RelationsManager;
        Iterator(relation** r, unsigned int n): _Iterator(r,n){}
    public:
        Iterator(): _Iterator(){}
    };
    Iterator begin(){ return Iterator(relations,nbRelations); }
    Iterator end(){ return Iterator(relations + nbRelations, nbRelations); }

    class Const_Iterator: public _const_iterator<relation>{
        friend class RelationsManager;
        Const_Iterator(relation** r, unsigned int n): _const_iterator(r,n){}
    public:
        Const_Iterator(): _const_iterator(){}
    };
    Const_Iterator cbegin(){ return Const_Iterator(relations,nbRelations); }
    Const_Iterator cend(){ return Const_Iterator(relations + nbRelations,nbRelations); }
};

#endif //RELATIONMANAGER_H
