#include "equazione.h"

// costruttori/distruttori
equazione::equazione(polinomio& p) : pol(p) {}

// metodi di supporto
polinomio equazione::getPolinomio() const
{
    return pol;
}

// metodi di classe
QString equazione::getType() const
{
    return QString("Equazione di grado " + QString::number(pol.getHighestDegree()));
}
