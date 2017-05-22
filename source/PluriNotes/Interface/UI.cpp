#include "Interface/UI.h"


fenetre::fenetre(){
    //creer
    creerAction();
    creerMenu();

    zoneCentrale = new QMdiArea;
    setCentralWidget(zoneCentrale);


    //decorer la fenetre
    setWindowTitle("PluriNotes");
    setMinimumSize(600,600);

    //connect
}


void fenetre::creerAction(){
    nouvArticle = new QAction("&Article",this);
    nouvArticle->setShortcut(QKeySequence("Ctrl+N"));
    connect(nouvArticle,SIGNAL(triggered()),this,SLOT(creerArticle()));

    nouvImage = new QAction("&Image",this);
    //connect(nouvImage,SIGNAL(triggered()),this,SLOT(creerImage()));

    nouvTache = new QAction("&Tache",this);
    //connect(nouvTache,SIGNAL(triggered()),this,SLOT(creerTache()));

    quitter = new QAction("&Quitter",this);
    quitter->setShortcut(QKeySequence("Ctrl+Q"));
    connect(quitter,SIGNAL(triggered()),qApp,SLOT(quit()));

    sauvegarder = new QAction("&Sauvegarder",this);
    sauvegarder->setShortcut(QKeySequence("Ctrl+S"));
    //sauvegarder = new QAction("Sauvegarder sous",this);

    charger = new QAction("&Ouvrir",this);
    charger->setShortcut(QKeySequence("Ctrl+O"));

    annuler = new QAction("Annuler",this);
    annuler->setShortcut(QKeySequence("Ctrl+Z"));
    annuler->setEnabled(false);

    retablir = new QAction("Retablir",this);
    retablir->setShortcut(QKeySequence("Ctrl+Y"));
    retablir->setEnabled(false);
}

void fenetre::creerMenu(){

    //tag Fichier
    QMenu* fichier = menuBar()->addMenu("&Fichier");

    //differents nouveax notes
    QMenu* nouveau = fichier->addMenu("&Nouveau");
    nouveau->addAction(nouvArticle);
    nouveau->addAction(nouvImage);
    nouveau->addAction(nouvTache);

    //autres actions
    fichier->addAction(charger);
    fichier->addAction(sauvegarder);
    fichier->addSeparator();
    fichier->addAction(quitter);

/*-------------------------------------------*/

    //tag Edition
    QMenu *edit = menuBar()->addMenu("&Edition");
    edit->addAction(annuler);
    edit->addAction(retablir);
}

void fenetre::creerBarreOutils(){}

void fenetre::creerBarreEtat(){}

void fenetre::creerArticle(){
    articleInterface* aI = new articleInterface;
    zoneCentrale->addSubWindow(aI);
    aI->exec();
}
