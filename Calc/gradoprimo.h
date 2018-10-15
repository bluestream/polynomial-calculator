#ifndef GRADOPRIMO_H
#define GRADOPRIMO_H

#include "equazione.h"

class gradoPrimo : public equazione
{
public:
    // costruttori/distruttori
    gradoPrimo(polinomio&);
    virtual ~gradoPrimo() = default;

    // metodi virtuali
    virtual vector<double> solve() const;

private:
    double a, b;
};

#endif // GRADOPRIMO_H

// Forma standard: ax + b
