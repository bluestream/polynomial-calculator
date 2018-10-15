#ifndef GRADOSECONDO_H
#define GRADOSECONDO_H

#include "equazione.h"

class gradoSecondo : public equazione
{
public:
    // costruttori/distruttori
    gradoSecondo(polinomio&);
    virtual ~gradoSecondo() = default;

    // metodi di classe
    double getDelta() const;

    // metodi virtuali
    virtual vector<double> solve() const;

private:
    double a, b, c;
};

#endif // GRADOSECONDO_H

// Forma standard: ax^2 + bx + c
