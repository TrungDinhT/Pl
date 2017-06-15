#ifndef GLOBALINTERFACE_H
#define GLOBALINTERFACE_H

#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"
#include "NoteInterfaceEditable.h"
#include "ManagerInterface.h"
#include "RelationManager/RelationManager.h"
#include "corbeilleinterface.h"


class GlobalInterface : public QWidget {
  Q_OBJECT
  QGridLayout* principale;
  //NoteInterface* NI;
  NoteInterfaceEditable* NIE;
  //RelationInterface* RI;
  ManagerInterface* MI;
  //MyQToolbar* TB;
  NotesManager* NM;
  RelationsManager *RM;
  Note* NoteCurrent;
  Version* VersionCurrent;
  QListWidget* liste;


  
public :
  GlobalInterface();
  
public slots : 
  //void modifierNote();
  void changerNote(QListWidgetItem* item);
  void sauverNote(Version* v);
  void supprimerNote();
  void miseEnRelationNote();
  void changerVersionNote();
  void versionActiveNote();
  void choixVersionNote(QListWidgetItem* item);
  void raffraichissementMI();
  void sauvegardeGeneral();
};



#endif // GLOBALINTERFACE_H
