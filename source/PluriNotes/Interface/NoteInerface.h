#ifndef NOTEINERFACE_H
#define NOTEINERFACE_H

#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"


class NoteInterface : public QWidget {
  Q_OBJECT
  Version* version;
  QLabel* titre;
  QPushButton* modifier;
  QPushButton* supprimer;
  QPushButton* relier;
  
  
public :
  NoteInterface(Version* v);
  
public slots : 
  //void modification();
  //void suppression();
  //void relation();


};


#endif // NOTEINERFACE_H
