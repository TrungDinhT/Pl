#include "NoteInterfaceEditable.h"
NoteInterfaceEditable::NoteInterfaceEditable(Note* n){
  note = n;
  titre = new QLineEdit(n->titre);
  sauver = new QPushButton("sauver");
}
