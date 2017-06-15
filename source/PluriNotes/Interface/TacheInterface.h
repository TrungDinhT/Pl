#ifndef TACHEINTERFACE_H
#define TACHEINTERFACE_H

#include <QtWidgets>
#include "NoteInterfaceEditable.h"

class Tache;

class GlobalInterface;

class TacheInterfaceEditable: public NoteInterfaceEditable{
    Q_OBJECT
    friend class GlobalInterface;
public:
   TacheInterfaceEditable(const QString id, const Tache* m = nullptr);

   /** fonction pour ajouter reference
    *quand l'utilisateur entre \ref{id} dans n'importe quel champs de l'note (où on peut avoir texte)
    */
   void ajouteReference() const;

public slots:
   virtual void saveNote();


signals:
private:

   QTextEdit* action;
   QSpinBox* priorite;
   QComboBox* statut;
   QDateTimeEdit* dateEcheance;
   QVBoxLayout* principale;


   const Tache* tache;

};

#endif // TACHEINTERFACE_H
