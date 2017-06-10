#ifndef ARTICLEINTERFACEEDITABLE_H
#define ARTICLEINTERFACEEDITABLE_H

#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"

class articleInterfaceEditable: public QDialog{

    Q_OBJECT

public:
   articleInterfaceEditable(Article& a);
    
public slots:
   void saveArticle();

private:
   QLineEdit* titre;
   QTextEdit* text;
   QPushButton* save;

   Article& article;//Article* article;
   QString savedName;

};

#endif // ARTICLEINTERFACE_H
