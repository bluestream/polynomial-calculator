#ifndef MONOMIO_H
#define MONOMIO_H

#include "eccezione.h"
#include <iostream>

using std::ostream;
using std::cout;
using std::endl;
using std::showpos;     // per visualizzare automaticamente il segno '+' nello stream di output
using std::noshowpos;   // per disattivare il flag precedente

class monomio
{
public:
    // costruttori/distruttori
    monomio(int = 0, int = 0);
    ~monomio() = default;

    // metodi di supporto
    int getCoeff() const;
    int getExp() const;

    // metodi di classe
    QString toQString() const;

    // overloading degli operatori
    monomio operator+(const monomio&) const;
    monomio operator-(const monomio&) const;
    monomio operator*(const monomio&) const;
    monomio operator/(const monomio&) const;
    bool operator<(const monomio&) const;       // necessario per la funzione std::sort()
    bool operator==(const monomio&) const;
    bool operator!=(const monomio&) const;
    friend ostream& operator<<(ostream&, const monomio&);

private:
    int coeff, exp;
};

#endif // MONOMIO_H

// Il termine noto è un monomio particolare con exp = 0
