
#include "Interface/NoteInterfaceEditable.h"
NoteInterfaceEditable::NoteInterfaceEditable(Version* v){
  version = v;
  titre = new QLineEdit(v->titre);
  save = new QPushbutton("save");

}
