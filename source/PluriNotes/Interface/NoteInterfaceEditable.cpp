
#include "NoteInterfaceEditable.h"
NoteInterfaceEditable::NoteInterfaceEditable(Version* v, const QString& id):id(id),QWidget(),version(v){
  //version = v;
  titre = new QLineEdit(v->getTitre());
  //sauver = new QPushButton("sauver");
  save = new QPushButton("save");

  connect(save,SIGNAL(clicked()),this,SLOT(saveNote()));

  supprimer = new QPushButton("supprimer");
  relier = new QPushButton("relier");
  changerversion = new QPushButton("changer de version");
  rendreversionactive = new QPushButton("rendre la version active");
}
