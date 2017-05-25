#include "Interface/UI.h"


//creer les managers
static NotesManager& NM = NotesManager::getManager();

/*------------------------Article Interface--------------------------*/

articleInterface::articleInterface(Article *a): QDialog(),article(a),savedName(""){

    //texte et titre layout
    QFormLayout *layoutT = new QFormLayout;
    titre = new QLineEdit;
    text = new QTextEdit;
    layoutT->addRow("T&itre",titre);
    layoutT->addRow("T&exte",text);

    //bouton layout
    QHBoxLayout *layoutB = new QHBoxLayout;
    save = new QPushButton("Sauvegarder");
    layoutB->setAlignment(Qt::AlignRight);
    layoutB->addWidget(save);

    //layout commun
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(layoutT);
    layout->addLayout(layoutB);

    //decorer la fenetre
    setLayout(layout);
    setWindowTitle(titre->text());
    setMinimumSize(200,200);

    //connecter
        //connect bouton
    connect(save,SIGNAL(clicked()),this,SLOT(saveArticle()));
        //connecter champ titre
    connect(titre,SIGNAL(textEdited(QString)),this,SLOT(activerSave(QString)));
        //connecter champ text
    connect(text,SIGNAL(textChanged()),this,SLOT(activerSave1()));

}

void articleInterface::saveArticle(){

    //path to save
    if(NM.getFilename().isEmpty()||NM.getFilename()!=savedName)
    {
        QString location = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        QString f = QFileDialog::getSaveFileName(this, "Save File",location,"Xml(*.xml)");
        NM.setFilename(f);
        savedName = f;
    }

    article->setTitle(titre->text());
    article->setText(text->toPlainText());

    NM.save(article);

    QMessageBox::information(this, "Sauvegarde", "Votre article a bien ete sauvegarde...");
    save->setEnabled(false); // le bouton est de nouveau desactive
}

void articleInterface::activerSave(QString){ save->setEnabled(true); }

void articleInterface::activerSave1(){ save->setEnabled(true); }

void articleInterface::loadArticle(){

}

/*--------------------------------fenetre principale------------------------*/

fenetre::fenetre(){
    //creer
    creerAction();
    creerMenu();


    //decorer la fenetre
    zoneCentrale = new QMdiArea;
    setCentralWidget(zoneCentrale);
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
    connect(sauvegarder,SIGNAL(triggered()),this,SLOT(saveFile()));

    sauvegarderSous = new QAction("Sauvegarder sous",this);
    connect(sauvegarderSous,SIGNAL(triggered()),this,SLOT(saveFileAs()));

    charger = new QAction("&Ouvrir",this);
    charger->setShortcut(QKeySequence("Ctrl+O"));
    connect(charger,SIGNAL(triggered()),this,SLOT(openFile()));

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
    fichier->addAction(sauvegarderSous);
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
    articleInterface* aI = new articleInterface(static_cast<Article*>(NM.getNewNote('A')));
    QMdiSubWindow* sub = zoneCentrale->addSubWindow(aI);
    addSubFenetre(sub,'A');
    aI->exec();
}

void fenetre::openFile(){

}

void fenetre::saveFile(){
    QMdiSubWindow* cur = zoneCentrale->currentSubWindow();
    switch(fenetreManager[cur]){
        case 'A': static_cast<articleInterface*>(cur->widget())->saveArticle(); break;
        case 'I':
        case 'T':
        default: break;
    }
}

void fenetre::saveFileAs(){
    QMdiSubWindow* cur = zoneCentrale->currentSubWindow();
    switch(fenetreManager[cur]){
        case 'A':{
                    articleInterface* a = static_cast<articleInterface*>(cur->widget());
                    a->resetSavedName();
                    a->saveArticle();
                    break;
                 }
        case 'I':
        case 'T':
        default: break;
    }
}



