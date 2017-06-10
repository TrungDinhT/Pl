#ifndef ARTICLEINTERFACE_H
#define ARTICLEINTERFACE_H

#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"

class articleInterface: public QDialog{

    Q_OBJECT

public:
   articleInterface(Article& a);

    
public slots:
   void modifArticle();
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
