
#include "NoteInterfaceEditable.h"
NoteInterfaceEditable::NoteInterfaceEditable(const Version *v, const QString& id):QWidget(),id(id),version(v){
  titre = new QLineEdit();
  save = new QPushButton("save");

  connect(save,SIGNAL(clicked()),this,SLOT(saveNote()));

  supprimer = new QPushButton("supprimer");
  addRela = new QPushButton("afficher relation");
  changerversion = new QPushButton("changer de version");
  rendreversionactive = new QPushButton("rendre la version active");
}
