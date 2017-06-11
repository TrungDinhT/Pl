
#include "Interface/NoteInterfaceEditable.h"
NoteInterfaceEditable::NoteInterfaceEditable(Version* v){
  version = v;
  titre = new QLineEdit(v->titre);
  sauver = new QPushButton("sauver");
}
