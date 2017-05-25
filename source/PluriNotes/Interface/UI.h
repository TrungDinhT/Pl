#ifndef UI_H
#define UI_H

#include "ArticleInterface.h"
/*#include "TacheInterface.h"
#include "ImageInterface.h"
*/

#include "NoteManager/NoteManager.h"
#include <unordered_map>
//pour manager des sub fenetres

class fenetre: public QMainWindow{
   Q_OBJECT

public:
    fenetre();
    void addSubFenetre(QMdiSubWindow* s, char t){
        fenetreManager.insert({s,t});
    }

public slots:
    void creerArticle();
    //void creerTache();
    //void creerImage();

    void openFile();
    void saveFile();
    void saveFileAs();
private:
    QMdiArea *zoneCentrale;
    std::unordered_map<QMdiSubWindow*, char> fenetreManager;

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
    QAction *sauvegarderSous;
    QAction *charger;
    //QAction *supprimerNotes;
    QAction *annuler;
    QAction *retablir;


};


#endif // UI_H
