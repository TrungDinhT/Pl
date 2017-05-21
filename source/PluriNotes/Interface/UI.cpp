#include "Interface/UI.h"


fenetre::fenetre(){
    //creer
    creerAction();
    creerMenu();

    zoneCentrale = new QWidget;
    setCentralWidget(zoneCentrale);


    //decorer la fenetre
    setWindowTitle("PluriNotes");
    setMinimumSize(600,600);

    //connect
}

void fenetre::creerAction(){
    nouveau = new QAction("&Nouveau",this);
    nouveau->setShortcut(QKeySequence("Ctrl+N"));

    quitter = new QAction("&Quitter",this);
    quitter->setShortcut(QKeySequence("Ctrl+Q"));
    QObject::connect(quitter,SIGNAL(triggered()),qApp,SLOT(quit()));

    sauvegarder = new QAction("&Sauvegarder",this);
    sauvegarder->setShortcut(QKeySequence("Ctrl+S"));
    //sauvegarder = new QAction("Sauvegarder sous",this);

    charger = new QAction("&Ovrir",this);
    charger->setShortcut(QKeySequence("Ctrl+O"));

    annuler = new QAction("&Annuler",this);
    annuler->setShortcut(QKeySequence("Ctrl+Z"));
    annuler->setEnabled(false);

    retablir = new QAction("&Retablir",this);
    retablir->setShortcut(QKeySequence("Ctrl+Y"));
    retablir->setEnabled(false);
}

void fenetre::creerMenu(){
    //tag Fichier
    QMenu* fichier = menuBar()->addMenu("&Fichier");
    fichier->addAction(nouveau);
    fichier->addAction(charger);
    fichier->addAction(sauvegarder);
    fichier->addSeparator();
    fichier->addAction(quitter);

    //tag Edition
    QMenu *edit = menuBar()->addMenu("&Edition");
    edit->addAction(annuler);
    edit->addAction(retablir);
}

void fenetre::creerOutils(){}

void fenetre::creerBarreEtat(){}

