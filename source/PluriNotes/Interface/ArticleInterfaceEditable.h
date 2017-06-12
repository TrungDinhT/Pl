#ifndef ARTICLEINTERFACEEDITABLE_H
#define ARTICLEINTERFACEEDITABLE_H

#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"
#include "NoteInterfaceEditable.h"

class articleInterfaceEditable: public NoteInterfaceEditable{

    Q_OBJECT

public:
   articleInterfaceEditable(Article* a = 0);
    
public slots:
   //void saveArticle();


signals:
    void sauvegarde(Article* a);
private:
   //QLineEdit* titre;
   QTextEdit* text;
   //QPushButton* save;

   Article* article;//Article* article;
   //QString savedName;

};

#endif // ARTICLEINTERFACEEDITABLE_H
