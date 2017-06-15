#ifndef ARTICLEINTERFACEEDITABLE_H
#define ARTICLEINTERFACEEDITABLE_H

#include <QtWidgets>
#include "NoteInterfaceEditable.h"

class GlobalInterface;

class articleInterfaceEditable: public NoteInterfaceEditable{
    Q_OBJECT
    friend class GlobalInterface;
public:
   articleInterfaceEditable(const QString id, Article* a = nullptr);

   /*fonction pour ajouter reference
    *quand l'utilisateur entre \ref{id} dans n'importe quel champs de l'note (où on peut avoir texte)
    */
   void ajouteReference() const;

public slots:
   virtual void saveNote();


signals:
  //void sauvegarde(Article* a);
private:
   //QLineEdit* titre;
   QTextEdit* text;
   QVBoxLayout* principale;
   //QPushButton* save;

   Article* article;//Article* article;
   //QString savedName;

};

#endif // ARTICLEINTERFACEEDITABLE_H
