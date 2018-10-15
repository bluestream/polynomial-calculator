#ifndef ECCEZIONE_H
#define ECCEZIONE_H

#include <QString>

class eccezione
{
public:
    // costruttori/distruttori
    eccezione(const QString&);
    ~eccezione() = default;

    // metodi di supporto
    QString getMsg() const;

private:
    QString msg;
};

#endif // ECCEZIONE_H
