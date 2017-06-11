#ifndef MYQTOOLBAR_H
#define MYQTOOLBAR_H

#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"


class MyQToolbar : public QToolbar {
  Q_OBJECT
  QAction* sauvegarder;
  //QAction* undo;
  
  
public :
  MyQToolbar();
  
public slots : 
  //void retour();
  void sauvegarde_physique();

}






#endif // MYQTOOLBAR_H
