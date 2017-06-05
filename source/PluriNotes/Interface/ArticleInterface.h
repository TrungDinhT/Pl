#ifndef ARTICLEINTERFACE_H
#define ARTICLEINTERFACE_H

#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"

class articleInterfaceEditable: public QDialog{

    Q_OBJECT

public:
   articleInterfaceEditable(Article& a);

    
public slots:
   void saveArticle();
   //void activerSave(QString str);
   //void activerSave1();
   //void loadArticle();

private:
   QLabel* titre;
   QLabel* text;
   QPushButton* modifier;

   Article& article;//Article* article;
   //QString savedName;

};

#endif // ARTICLEINTERFACE_H
