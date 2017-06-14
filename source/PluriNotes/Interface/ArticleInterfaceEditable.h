#ifndef ARTICLEINTERFACEEDITABLE_H
#define ARTICLEINTERFACEEDITABLE_H

#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"
#include "NoteInterfaceEditable.h"

class GLobalInterface;

class articleInterfaceEditable: public NoteInterfaceEditable{
    Q_OBJECT
    friend class GlobalInterface;
public:
   articleInterfaceEditable(Article* a = 0);
    
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
