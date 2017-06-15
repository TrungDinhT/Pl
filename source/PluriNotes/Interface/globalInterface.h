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
  NoteInterfaceEditable* NIE;
  ManagerInterface* MI;
  NotesManager* NM;
  RelationsManager *RM;
  Note* NoteCurrent;
  Version* VersionCurrent;
  QListWidget* liste;
  QListWidget* listRela;
  QPushButton* AfficherRela;

  
public :
  GlobalInterface();
  
public slots : 
  void changerNote(QListWidgetItem* item);
  void sauverNote(Version* v);
  void supprimerNote();
  void miseEnRelationNote();
  void changerVersionNote();
  void versionActiveNote();
  void choixVersionNote(QListWidgetItem* item);
  void raffraichissementMI();
  void sauvegardeGeneral();
  void afficherCouple();
};



#endif // GLOBALINTERFACE_H
