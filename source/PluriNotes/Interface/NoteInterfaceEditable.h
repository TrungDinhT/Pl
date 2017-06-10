#ifndef NOTEINERFACEEDITABLE_H
#define NOTEINERFACEEDITABLE_H

#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"


class NoteInterface : public QWidget {
  Q_OBJECT
  Note* note;
  QLineEdit* titre;
  QPushbutton* save;
  
  
public :
  NoteInterface(note* n);
  
public slots : 


}

#endif //NOTEINERFACEEDITABLE_H
