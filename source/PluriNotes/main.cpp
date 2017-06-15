#include "Interface/globalInterface.h"
#include <QApplication>

int main(int argc, char *argv[])

{

    QApplication app(argc, argv);
    qDebug()<<"create Note\n";

    GlobalInterface fen;
    fen.show();

    return app.exec();

}

