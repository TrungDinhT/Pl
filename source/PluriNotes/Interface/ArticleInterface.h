#ifndef ARTICLEINTERFACE_H
#define ARTICLEINTERFACE_H

#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"
#include "RelationManager/relation.h"

class articleInterface: public NoteInterface{

    Q_OBJECT

public:
   articleInterface(Article* a = 0);
   ~articleInterface(){}

    
public slots:
   //void modifArticle();
   
    //void activerSave(QString str);
   //void activerSave1();
   //void loadArticle();

private:
   //QLabel* titre;
   QLabel* text;
   //QPushButton* modifier;

   Article* article;//Article* article;
   //QString savedName;

};

#endif // ARTICLEINTERFACE_H
