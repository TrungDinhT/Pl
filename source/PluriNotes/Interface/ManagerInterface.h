#ifndef MANAGERINTERFACE_H
#define MANAGERINTERFACE_H


#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"
#include "RelationManager/RelationManager.h" //ca sert apres
#include "Corbeille/corbeille.h"

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

public :
  ManagerInterface();
  virtual void extension_choix_version(){}

public slots :
  void ajoutNote();
  //void choixAjoutNote(list_version_item *item);
  void choixAjoutNote(QListWidgetItem *item);
  void ouvrirCorbeille();

signals :
  void refresh();
};
/*
class list_version_item : public QListWidgetItem {
    Q_OBJECT
    friend class ManagerInterface;
protected:

  Version* version;

public :
  list_version_item(QString s,Version *v):QListWidgetItem(s,nullptr,1000),version(v){}
  Version* getVersion(){return version;}

public slots :
  //void clickNote();

signals :
  //void clicNote();
};
*/
#endif // MANAGERINTERFACE_H

