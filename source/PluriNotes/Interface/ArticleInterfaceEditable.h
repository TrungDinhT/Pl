#ifndef ARTICLEINTERFACEEDITABLE_H
#define ARTICLEINTERFACEEDITABLE_H

#include <QtWidgets>
#include "NoteInterfaceEditable.h"

class GlobalInterface;

class Article;

class articleInterfaceEditable: public NoteInterfaceEditable{
    Q_OBJECT
    friend class GlobalInterface;
public:
   articleInterfaceEditable(const QString id, const Article* a = nullptr);

   /*fonction pour ajouter reference
    *quand l'utilisateur entre \ref{id} dans n'importe quel champs de l'note (où on peut avoir texte)
    */
   void ajouteReference() const;

public slots:
   virtual void saveNote();

private:
   QTextEdit* text;
   QVBoxLayout* principale;

   const Article* article;

};

#endif // ARTICLEINTERFACEEDITABLE_H
