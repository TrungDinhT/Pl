#ifndef IMAGEINTERFACE_H
#define IMAGEINTERFACE_H

#include <QtWidgets>
#include "NoteInterfaceEditable.h"

class GlobalInterface;

class MultimediaInterfaceEditable: public NoteInterfaceEditable{
    Q_OBJECT
    friend class GlobalInterface;
public:
   MultimediaInterfaceEditable(const QString id, Multimedia* m = nullptr);

   /*fonction pour ajouter reference
    *quand l'utilisateur entre \ref{id} dans n'importe quel champs de l'note (où on peut avoir texte)
    */
   void ajouteReference() const;

public slots:
   virtual void saveNote();
   void changer_chemin();


signals:
private:
   QTextEdit* description;
   QPushButton* changer_media;
   QVBoxLayout* principale;
   QPixmap* image;
   QLabel* im;
   QString chemin;
   //QMediaPlayer video;

   Multimedia* multimedia;

};

#endif // IMAGEINTERFACE_H
