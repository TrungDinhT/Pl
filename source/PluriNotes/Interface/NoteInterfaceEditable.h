#ifndef NOTEINERFACEEDITABLE_H
#define NOTEINERFACEEDITABLE_H

#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"
//#include "globalInterface.h"
class GLobalInterface;

class NoteInterfaceEditable : public QWidget {
    Q_OBJECT
    friend class GlobalInterface;
protected:


  Version* version;
  QLineEdit* titre;
  QPushButton* save;
  QPushButton* supprimer;
  QPushButton* relier;
  QPushButton* changerversion;
  QPushButton* rendreversionactive;
  
public :
  NoteInterfaceEditable(Version* v);
  
public slots : 
    virtual void saveNote() = 0;

};


#endif //NOTEINERFACEEDITABLE_H
