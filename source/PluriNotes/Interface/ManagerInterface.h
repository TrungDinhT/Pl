#ifndef MANAGERINTERFACE_H
#define MANAGERINTERFACE_H


#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"
#include "RelationManager/RelationManager.h" //ca sert apres
#include "corbeilleinterface.h"

class GLobalInterface;
class list_version_item;
class ManagerInterface : public QWidget {
    Q_OBJECT
    friend class GlobalInterface;
protected:

  NotesManager* NM;
  Note* NoteCurrent;
  QVBoxLayout* principale;
  QHBoxLayout* bouttons;
  QListWidget* liste_note;
  QPushButton* ajouter;
  QPushButton* sauvegarder;
  QListWidget* listeVersion;
  QPushButton* corbeille;
  QPushButton* rafrachir;
  corbeilleInterface* c;

public :
  ManagerInterface();
  virtual void extension_choix_version(){}

public slots :
  void ajoutNote();
  void choixAjoutNote(QListWidgetItem *item);
  void ouvrirCorbeille();

signals :
  void refresh();
};

#endif // MANAGERINTERFACE_H

