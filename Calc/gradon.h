#ifndef GRADON_H
#define GRADON_H

#include "equazione.h"

class gradoN : public equazione
{
public:
    // costruttori/distruttori
    gradoN(polinomio&);
    virtual ~gradoN() = default;

    // metodi virtuali
    virtual vector<double> solve() const;
};

#endif // GRADON_H
