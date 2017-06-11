/*#include "NoteManager/notes.h"
#include "RelationManager/relation.h"
#include "Corbeille/corbeille.h"*/

#include "Interface/UI.h"
#include <QApplication>

#include "RelationManager/relation.h"
#include "RelationManager/RelationManager.h"

int main(int argc, char *argv[])

{

    QApplication app(argc, argv);


    fenetre fen;

    fen.show();


    return app.exec();

}
