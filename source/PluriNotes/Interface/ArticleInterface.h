#ifndef ARTICLEINTERFACE_H
#define ARTICLEINTERFACE_H

#include <QtWidgets>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"

class articleInterface: public QDialog{

    Q_OBJECT

public:
   articleInterface(Article* a);

public slots:
   void saveArticle();
   void activerSave(QString str);
   void activerSave1();
   void autoSave();

private:
   QLineEdit* titre;
   QTextEdit* text;
   QPushButton* save;

   Article* article;

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
