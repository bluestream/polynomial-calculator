#include "gradosecondo.h"

// costruttori/distruttori
gradoSecondo::gradoSecondo(polinomio& p) : equazione(p)
{
    a = getPolinomio().getCoeff(2);
    b = getPolinomio().getCoeff(1);
    c = getPolinomio().getCoeff(0);
}

// metodi di classe
double gradoSecondo::getDelta() const
{
    return (b * b) - (4 * a * c);
}

// metodi virtuali
vector<double> gradoSecondo::solve() const
{
    if (!getPolinomio().checkPositiveDegrees())
        throw eccezione("ERRORE\nTutti gli esponenti devono essere >= 0");
    vector<double> result;
    double delta = getDelta();
    if (delta < 0) throw eccezione("ERRORE\nDelta negativo, non ci sono soluzioni reali");
    else {
        double x1 = (-b - sqrt(delta)) / (2 * a);
        double x2 = (-b + sqrt(delta)) / (2 * a);
        result.push_back(x1);
        result.push_back(x2);
    }
    return result;
}


