#include "gradoprimo.h"

// costruttori/distruttori
gradoPrimo::gradoPrimo(polinomio& p) : equazione(p)
{
    a = getPolinomio().getCoeff(1);
    b = getPolinomio().getCoeff(0);
}

// metodi virtuali
vector<double> gradoPrimo::solve() const
{
    if (!getPolinomio().checkPositiveDegrees())
        throw eccezione("ERRORE\nTutti gli esponenti devono essere >= 0");
    vector<double> result;
    double x = (double) -b / a;
    result.push_back(x);
    return result;
}
