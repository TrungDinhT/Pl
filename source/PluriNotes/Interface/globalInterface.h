#ifndef GLOBALINTERFACE_H
#define GLOBALINTERFACE_H

#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"
#include "NoteInterfaceEditable.h"




class GlobalInterface : public QWidget {
  Q_OBJECT
  QGridLayout* principale;
  //NoteInterface* NI;
  NoteInterfaceEditable* NIE;
  //RelationInterface* RI;
  //ManagerInterface* MI;
  //MyQToolbar* TB;
  NotesManager* NM;
  Note* NoteCurrent;
  Version* VersionCurrent;
  
public :
  GlobalInterface();
  
public slots : 
  //void modifierNote();
  void sauverNote(Version* v);
  void supprimerNote();
  void miseEnRelationNote();
  void changerVersionNote();
  void versionActiveNote();
  };


#endif // GLOBALINTERFACE_H
