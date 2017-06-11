#ifndef ARTICLEINTERFACE_H
#define ARTICLEINTERFACE_H

#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"
#include "RelationManager/relation.h"

class articleInterface: public QDialog{

    Q_OBJECT

public:
   articleInterface(Article *a);
   void resetSavedName() { savedName = ""; }

public slots:
   void saveArticle();
   void activerSave(QString str);
   void activerSave1();
   void loadArticle();

private:
   QLineEdit* titre;
   QTextEdit* text;
   QPushButton* save;

   Article* article;
   QString savedName;


   /*
   QLabel* idl;
   QLabel* titrel;
   QLabel* textl;
   QHBoxLayout* cid;
   QHBoxLayout* ctitre;
   QHBoxLayout* ctext;
   QVBoxLayout* couche;
   Article* article;
   QLineEdit* id;
   */
};

#endif // ARTICLEINTERFACE_H
