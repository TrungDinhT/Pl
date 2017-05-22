#ifndef UI_H
#define UI_H

#include "ArticleInterface.h"
/*#include "TacheInterface.h"
#include "ImageInterface.h"
*/


class fenetre: public QMainWindow{
   Q_OBJECT

public:
    fenetre();

public slots:
    void creerArticle();
    //void creerTache();
    //void creerImage();

private:
    QMdiArea *zoneCentrale;

    //modulariser les creation des widgets
    void creerAction();
    void creerMenu();
    void creerBarreOutils();
    void creerBarreEtat();
    //void creerDocker();

    //les widgets
    QAction *nouvArticle;
    QAction *nouvImage;
    QAction *nouvTache;
    QAction *quitter;
    QAction *sauvegarder;
    //QAction *sauvergarderSous;
    QAction *charger;
    //QAction *supprimerNotes;
    QAction *annuler;
    QAction *retablir;


};


#endif // UI_H
