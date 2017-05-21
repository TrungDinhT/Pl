#ifndef UI_H
#define UI_H

/*#include "ArticleInterface.h"
#include "TacheInterface.h"
#include "ImageInterface.h"
*/
#include <QtWidgets>

class fenetre: public QMainWindow{
   Q_OBJECT

public:
    fenetre();

public slots:


private:
    QWidget *zoneCentrale;

    //modulariser les creation des widgets
    void creerAction();
    void creerMenu();
    void creerOutils();
    void creerBarreEtat();
    //void creerDocker();

    //les widgets
    QAction *nouveau;
    QAction *quitter;
    QAction *sauvegarder;
    //QAction *sauvergarderSous;
    QAction *charger;
    //QAction *supprimerNotes;
    QAction *annuler;
    QAction *retablir;


};


#endif // UI_H
