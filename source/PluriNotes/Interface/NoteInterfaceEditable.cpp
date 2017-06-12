
#include "NoteInterfaceEditable.h"
NoteInterfaceEditable::NoteInterfaceEditable(Version* v):version(v),QWidget(){
  //version = v;
  titre = new QLineEdit(v->getTitre());
  //sauver = new QPushButton("sauver");
  save = new QPushButton("save");
  connect(save,SIGNAL(clicked()),this,SLOT(saveArticle()));
  supprimer = new QPushButton("supprimer");
  relier = new QPushButton("relier");
  changerversion = new QPushButton("changer de version");
  rendreversionactive = new QPushButton("rendre la version active");
}
