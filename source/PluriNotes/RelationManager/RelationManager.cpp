#include "RelationManager.h"
#include "exception.h"


static RelationsManager* RelationsManager::instance = nullptr;

RelationsManager& RelationsManager::getInstance(){
    if (!instance) instance=new RelationsManager;
    return *instance;
}

void RelationsManager::freeInstance(){
    delete instance;
    instance=nullptr;
}

//relation* RelationsManager::getNewRelation(){}

//relation* RelationsManager::getRelation(){}

//relation* RelationsManager::deleteRelation()
