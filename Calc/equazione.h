#ifndef EQUAZIONE_H
#define EQUAZIONE_H

#include "polinomio.h"
#include <cmath>

class equazione
{
public:
    // costruttori/distruttori
    equazione(polinomio&);
    virtual ~equazione() = default;

    // metodi di supporto
    polinomio getPolinomio() const;

    // metodi di classe
    QString getType() const;    // ritorna il tipo dell'equazione

    // metodi virtuali puri
    virtual vector<double> solve() const = 0;       // ritorna un vettore che contiene le soluzioni            

private:
    polinomio& pol;
};

#endif // EQUAZIONE_H

// Classe base astratta
