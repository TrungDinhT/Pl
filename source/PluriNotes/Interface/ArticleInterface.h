#ifndef ARTICLEINTERFACE_H
#define ARTICLEINTERFACE_H

#include <QtWidgets>
#include "NoteManager/notes.h"

class articleInterface: public Article, public QDialog{

    Q_OBJECT

public:
   articleInterface(const QString ti = "Title by default", const QString te = "Text by default");

public slots:
   void changerTitre();
   void saveArticle();
   void activerSave(QString str);
   void activerSave1();

private:
   QLineEdit* titre;
   QTextEdit* text;
   QPushButton* save;

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
