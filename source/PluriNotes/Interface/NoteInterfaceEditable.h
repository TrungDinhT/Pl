#ifndef NOTEINERFACEEDITABLE_H
#define NOTEINERFACEEDITABLE_H

#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"


class NoteInterfaceEditable : public QWidget {
  Q_OBJECT
  Version* version;
  QLineEdit* titre;
  QPushButton* save;

  
public :
  NoteInterfaceEditable(Version* v);
  
public slots : 


}

#endif //NOTEINERFACEEDITABLE_H
