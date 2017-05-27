#ifndef EXCEPTION_H
#define EXCEPTION_H

class exception{
public:
    exception(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};


#endif // EXCEPTION_H
