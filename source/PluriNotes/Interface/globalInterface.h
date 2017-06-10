#ifndef GLOBALINTERFACE_H
#define GLOBALINTERFACE_H

#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"


class GlobalInterface : public QWidget {
  Q_OBJECT
  QHBoxLayout* principale;
  NoteInterface* NI;
  RelationInterface* RI;
  ManagerInterface* MI;
  MyQToolbar* TB;
  NoteManager& NM;
  
public :
  GlobalIterface();
  
public slots : 
  void modifierNote();
  void sauverNote();
  void supprimerNote();
  void miseEnRelationNote();
  }







#endif // GLOBALINTERFACE_H
