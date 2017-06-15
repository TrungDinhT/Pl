#ifndef NOTEINERFACEEDITABLE_H
#define NOTEINERFACEEDITABLE_H

#include <QtWidgets>

//#include "NoteManager/notes.h"

//#include "globalInterface.h"
class GLobalInterface;

class Version;

class NoteInterfaceEditable : public QWidget {
    Q_OBJECT
    friend class GlobalInterface;

protected:
  QString id; //ca sert a distinguer les notes
  const Version* version;
  QLineEdit* titre;
  QPushButton* save;
  QPushButton* supprimer;
  QPushButton* relier;
  QPushButton* changerversion;
  QPushButton* rendreversionactive;
  
public :
  NoteInterfaceEditable(const Version* v, const QString& id);

  /*fonction pour ajouter reference
   *quand l'utilisateur entre \ref{id} dans n'importe quel champs de l'note (où on peut avoir texte)
   */
  virtual void ajouteReference() const =0;


public slots : 
    virtual void saveNote() = 0;

signals :
    void sauvegarde(Version*);


};


#endif //NOTEINERFACEEDITABLE_H
