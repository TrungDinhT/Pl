#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>
#include <QDebug>

class _Exception{
public:
    _Exception(const QString& message):info(message){
        qDebug()<<"error info: "<<info<<"\n";
    }
    QString getInfo() const { return info; }
private:
    QString info;
};


#endif // EXCEPTION_H
