#include "NoteManager/notes.h"
#include "RelationManager/relation.h"

#include "Interface/globalInterface.h"
#include <QApplication>
#include "NoteManager/NoteManager.h"
#include "RelationManager/RelationManager.h"
#include <QDebug>

int main(int argc, char *argv[])

{

    QApplication app(argc, argv);
    qDebug()<<"create Note\n";


    NotesManager& nm = NotesManager::getManager();

    Note* n = new Note("coucou");
    Article* a = new Article("titi","toto");
    n->addVersion(a);

    Note* n2 = new Note("coucoucou");
    Article* a2 = new Article("tititi","tototo");
    n2->addVersion(a2);


    nm.addNotes(n);
    nm.addNotes(n2);

GlobalInterface fen;
    fen.show();

    /*NotesManager& nm = NotesManager::getManager();
    qDebug()<<"create NoteManager\n";

     test save
    Note* n = new Note(QDateTime::currentDateTime(),"test1",ACTIVE);
    qDebug()<<"create Note\n";
    Article* a = new Article("testA1",QDateTime::currentDateTime(),"testestsetsetstest");
    Article* a2 = new Article("testA2",QDateTime::fromString("13.06.2017-10:30:14","dd.MM.yyyy-hh:mm:ss"),"testestsetsetstest2");
    Article* a3 = new Article("testA3",QDateTime::fromString("13.06.2017-10:32:14","dd.MM.yyyy-hh:mm:ss"),"testestsetsetstest3");
    qDebug()<<"create Article\n";
    nm.save(n->getId(),a);
    nm.save(n->getId(),a2);
    nm.save(n->getId(),a3);

    Note* n2 = new Note(QDateTime::fromString("13.06.2017-10:40:14","dd.MM.yyyy-hh:mm:ss"),"test2",ACTIVE);
    Tache* t1 = new Tache(QDateTime::fromString("14.06.2017-10:30:14","dd.MM.yyyy-hh:mm:ss"),"testT1",3,EN_COURS);
    Tache* t2 = new Tache(QDateTime::fromString("15.06.2017-10:30:14","dd.MM.yyyy-hh:mm:ss"),"testT2",4,EN_COURS);
    Tache* t3 = new Tache(QDateTime::fromString("16.06.2017-10:30:14","dd.MM.yyyy-hh:mm:ss"),"testT3",5,EN_COURS);
    qDebug()<<"create Tache\n";
    nm.save(n2->getId(),t1);
    nm.save(n2->getId(),t2);
    nm.save(n2->getId(),t3);
    qDebug()<<"add note\n";
    nm.save();
    qDebug()<<"real save\n";


    QString location = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    nm.setFilename(location+"/noteslog_testload.xml");
    nm.save();*/

    return app.exec();

}

