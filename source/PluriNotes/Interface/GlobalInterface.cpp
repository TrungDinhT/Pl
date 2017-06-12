#include "GlobalInterface.h"
#include "ArticleInterfaceEditable.h"
GlobalInterface::GlobalInterface(){
  NM = &(NotesManager::getManager());
  qDebug()<<"creation ref\n";
  NotesManager::Iterator itn = NM->begin();
  qDebug()<<"creation itn\n";
  NoteCurrent = *itn;
  qDebug()<<"affectation noteCurrent\n";
  Note::Iterator itv = NoteCurrent->begin();
  qDebug()<<"creation itv\n";
  principale = new QGridLayout(this);
  qDebug()<<"creation layout\n";
  VersionCurrent = *itv;
  qDebug()<<"affectation VersionCurrent\n";
  //if(typeid(*VersionCurrent).name()=="Article"){
  NIE = new articleInterfaceEditable(static_cast <Article*>(VersionCurrent));
  qDebug()<<"creer article interface\n";
  //}

  principale->addWidget(NIE/*,0,1*/);
  qDebug()<<"ajout article\n";
  //RI = new RelationInterface() ;
  //MI = ManagerInterface();
  //TB  =MyQToolbar();
  connect(NIE,SIGNAL(sauvegarde(Version*)),this,SLOT(sauverNote(Version*)));
  connect(NIE->relier,SIGNAL(clicked()),this,SLOT(miseEnRelationNote()));
  connect(NIE->supprimer,SIGNAL(clicked()),this,SLOT(supprimerNote()));
  connect(NIE->changerversion,SIGNAL(clicked()),this,SLOT(changerVersionNote()));
  connect(NIE->rendreversionactive,SIGNAL(clicked()),this,SLOT(versionActiveNote()));
  qDebug()<<"connexion\n";

}
/*
void GlobalInterface::modifierNote(){
  delete NI;
  NIE = new NoteInterfaceEditable(VersionCurrent);
  principale->addWidget(NIE,0,1);
  //connect(NIE->save,SIGNAL(clicked()),this,SLOT(sauverNote()));
  connect(NIE,SIGNAL(sauvegarde(Version*)),this,SLOT(sauverNote(Version*)));
}*/
void GlobalInterface::sauverNote(Version* v){
  //article->getText() = texte.text;
  //article.actualiserDateModif(); //à définir
  //articleInterface a = new articleInterface(article);
  NoteCurrent->addVersion(v);
/*
  delete NIE;
  NI = new NoteInterface(v);
  principale->addWidget(NI,0,1);
  connect(NI->modifier,SIGNAL(clicked()),this,SLOT(modifierNote()));
  connect(NI->relier,SIGNAL(clicked()),this,SLOT(miseEnRelationNote()));
  connect(NI->supprimer,SIGNAL(clicked()),this,SLOT(supprimerNote()));
  connect(NI->changerversion,SIGNAL(clicked()),this,SLOT(changerVersionNote()));
  connect(NI->rendreversionactive,SIGNAL(clicked()),this,SLOT(versionActiveNote()));*/
}
void GlobalInterface::supprimerNote(){
//à completer
}
void GlobalInterface::miseEnRelationNote(){
//à completer
}

void GlobalInterface::changerVersionNote(){
//liste deroulante des version existante
}

void GlobalInterface::versionActiveNote(){
  
//changement de place le la version dans la liste
}
