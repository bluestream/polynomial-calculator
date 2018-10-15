#ifndef POLINOMIO_H
#define POLINOMIO_H

#include "monomio.h"
#include <list>
#include <vector>

using std::list;
using std::vector;

class polinomio
{
public:
    // costruttori/distruttori
    polinomio();
    ~polinomio() = default;

    // metodi di supporto
    int getSize() const;    // ritorna il numero di elementi presenti nel polinomio

    // metodi di classe
    QString toQString() const;          // converte il polinomio in una stringa
    void addMonomio(monomio&);          // aggiunge un monomio alla lista
    int getHighestDegree() const;       // trova il grado più alto presente nel polinomio
    int getCoeff(int) const;            // ritorna il coefficiente di un monomio di grado n
    bool checkPositiveDegrees() const;  // controlla che non ci siano monomi con esponenti negativi
    void clearItems();                  // elimina tutti gli elementi della lista
    void sortItems();                   // ordina il polinomio per esponente decrescente
    void negate();                      // cambia il segno del polinomio
    void removeZeros();                 // rimuove gli eventuali zeri presenti
    void simplify();                    // raccoglie e semplifica monomi simili (con lo stesso esponente)
    polinomio derivate() const;         // calcola la derivata del polinomio
    static const polinomio zero();      // ritorna un polinomio costante inizializzato a 0

    // funzione di divisione che ritorna quoziente e resto
    vector<polinomio> divide(const polinomio&) const;

    // overloading degi operatori
    polinomio operator+(const polinomio&) const;
    polinomio operator-(const polinomio&) const;
    polinomio operator*(const polinomio&) const;
    polinomio& operator=(const polinomio&);
    bool operator==(const polinomio&) const;
    bool operator!=(const polinomio&) const;
    friend ostream& operator<<(ostream&, const polinomio&);

private:
    list<monomio> L;
};

#endif // POLINOMIO_H
