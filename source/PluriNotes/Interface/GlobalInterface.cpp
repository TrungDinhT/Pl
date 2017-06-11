#include "Interface/GlobalInterface.h"
GlobalInterface::GlobalInterface(){
  NM = getManager();
  iterator<Note, NotesManager> itn = NM.beginIt();
  Version::iterator itv = itn.getIterator();
  principale = new QGridLayout(this);
  NI = new NoteInterface(&(itv.current()));
  principale.addWidget(NI,0,1);
  //RI = new RelationInterface() ;
  //MI = ManagerInterface();
  //TB  =MyQToolbar();
  connect(NI->modifier,SIGNAL(clicked()),this,SLOT(modifierNote()));
  connect(NI->relier,SIGNAL(clicked()),this,SLOT(miseEnRelationNote()));
  connect(NI->supprimer,SIGNAL(clicked()),this,SLOT(supprimerNote()));
  connect(NI->changerversion,SIGNAL(clicked()),this,SLOT(changerVersionNote()));
  connect(NI->rendreversionactive,SIGNAL(clicked()),this,SLOT(versionActiveNote()));


}

void GlobalInterface::modifierNote(Note* n){
  delete NI;
  NIE = new NoteInterfaceEditable(n);
  principale.addWidget(NIE,0,1);
  connect(NI->save,SIGNAL(clicked()),this,SLOT(sauverNote()));
}
void GlobalInterface::sauverNote(Note* n){
  //article->getText() = texte.text;
  //article.actualiserDateModif(); //à définir
  //articleInterface a = new articleInterface(article);

  delete NIE;
  NI = new NoteInterface(n);
  principale.addWidget(NI,0,1);
  connect(NI->modifier,SIGNAL(clicked()),this,SLOT(modifierNote()));
  connect(NI->relier,SIGNAL(clicked()),this,SLOT(miseEnRelationNote()));
  connect(NI->supprimer,SIGNAL(clicked()),this,SLOT(supprimerNote()));
  connect(NI->changerversion,SIGNAL(clicked()),this,SLOT(changerVersionNote()));
  connect(NI->rendreversionactive,SIGNAL(clicked()),this,SLOT(versionActiveNote()));
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
//changement de place le la version dans la liste? booleen?
}
