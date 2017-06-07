#ifndef GLOBALINTERFACE_H
#define GLOBALINTERFACE_H

#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"


class GlobalInterface : public QWidget {
  QHBoxLayout principale;
  NoteInterface NI;
  RelationInterface RI;
  ManagerInterface MI;
  MyQToolbar TB;
  
public :
  GlobalIterface();
  
public slots : 
  }







#endif // GLOBALINTERFACE_H
