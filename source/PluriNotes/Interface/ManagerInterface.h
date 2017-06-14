#ifndef MANAGERINTERFACE_H
#define MANAGERINTERFACE_H


#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"
class GLobalInterface;

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
public :
  ManagerInterface();

public slots :
  //void ajouterNote();

signals :
  //void clicNote();
};
/*
class list_note_item : public QListWidgetItem {
    Q_OBJECT
    friend class ManagerInterface;
protected:

  Note* NoteCurrent;

public :
  list_note_item(Note* n);

public slots :
  //void clickNote();

signals :
  //void clicNote();
};

*/
#endif // MANAGERINTERFACE_H

