#include "gradon.h"

// costruttori/distruttori
gradoN::gradoN(polinomio& p) : equazione(p) {}

// metodi virtuali
vector<double> gradoN::solve() const
{    
    throw eccezione("ERRORE\n" + getType() + ", non supportata per la risoluzione\n");
}
