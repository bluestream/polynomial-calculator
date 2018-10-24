#include "polinomio.h"

// costruttori/distruttori
polinomio::polinomio() {}

// metodi di supporto
int polinomio::getSize() const
{
    return L.size();
}

// metodi di classe
QString polinomio::toQString() const
{
    QString s;
    for (auto i = L.begin(); i != L.end(); ++i)
        s = s + i->toQString();
    return s;
}

void polinomio::addMonomio(monomio& m)
{
    L.push_back(m);
}

int polinomio::getHighestDegree() const
{
    int maxDegree = L.begin()->getExp();
    for (auto i = std::next(L.begin()); i != L.end(); ++i) {
        if (i->getExp() > maxDegree)
            maxDegree = i->getExp();
    }
    return maxDegree;
}

int polinomio::getCoeff(int n) const
{
    for (auto i = L.begin(); i != L.end(); ++i) {
        if (i->getExp() == n)
            return i->getCoeff();
    }
    return 0;
}

bool polinomio::checkPositiveDegrees() const
{
    for (auto i = L.begin(); i != L.end(); ++i) {
        if (i->getExp() < 0)
            return false;
    }
    return true;
}

void polinomio::clearItems()
{
    L.clear();
}

void polinomio::sortItems()
{
    L.sort();
    L.reverse();    // necessario per riordinare la lista in modo corretto (esponenti in ordine decrescente)
}

void polinomio::negate()
{
    for (auto i = L.begin(); i != L.end(); ++i)
        *i = (*i) * (-1);   // conversione implicita da int->monomio
}

void polinomio::removeZeros()
{
    // rimuovo gli zeri solo se il polinomio contiene più di un monomio
    for (auto i = L.begin(); i != L.end() && L.size() > 1; ++i) {
        if (i->getCoeff() == 0) {
            i = L.erase(i);
            i--;
        }
    }
}

void polinomio::simplify()
{
    for (auto i = L.begin(); i != L.end();++i) {
        for (auto j = std::next(i); j != L.end(); ++j) {
            if (j->getExp() == i->getExp()) {
                *i = (*i) + (*j);
                j = L.erase(j);
                j--;
                if (i->getCoeff() == 0) // se il grado è cambiato, j = i così all'incremento successivo j == std::next(i)
                    j = i;
            }
        }
    }
    removeZeros();
}

polinomio polinomio::derivate() const
{
    polinomio p;
    for (auto i = L.begin(); i != L.end(); ++i) {
        if (i->getExp() != 0) {
            monomio m((i->getExp()) * (i->getCoeff()), (i->getExp()) - 1);
            p.addMonomio(m);
        }
    }
    return p;
}

const polinomio polinomio::zero()
{
    monomio m(0);
    polinomio p;
    p.addMonomio(m);
    return p;
}

vector<polinomio> polinomio::divide(const polinomio& p) const
{
    vector<polinomio> result;   // vettore che conterrà i risultati

    polinomio num = *this;
    polinomio den = p;

    // ordino e semplifico i polinomi prima di procedere alla divisione
    num.sortItems(); num.simplify();
    den.sortItems(); den.simplify();

    // controlli preliminari
    if (num.getHighestDegree() < den.getHighestDegree())
        throw eccezione("ERRORE\nNon puoi dividere un polinomio per uno di grado maggiore");
    if (!num.checkPositiveDegrees() || !den.checkPositiveDegrees())
        throw eccezione("ERRORE\nUn polinomio non puo' avere esponenti < 0 durante la divisione");
    if (den == polinomio::zero())
        throw eccezione("ERRORE\nNon e' possibile dividere per 0");

    // algoritmo effettivo
    polinomio q = polinomio::zero();                    // polinomio per il quoziente
    polinomio& r = num;                                 // polinomio per il resto, alias
    bool stop = false;
    while (r != polinomio::zero() && r.getHighestDegree() >= den.getHighestDegree() && !stop) {
        monomio highestGradeNum = *(r.L.begin());
        monomio highestGradeDen = *(den.L.begin());
        monomio m = highestGradeNum / highestGradeDen;    // divisione tra i due monomi di grado maggiore tra num e den
        if (m == 0)
            stop = true;
        polinomio leadDiv;
        leadDiv.addMonomio(m);
        polinomio temp = leadDiv * den;
        q = q + leadDiv;
        r = r - temp;
    }
    result.push_back(q);    // inserisco il quoziente in prima posizione
    result.push_back(r);    // inserisco il quoziente in seconda posizione
    return result;
}

// overloading degli operatori
polinomio polinomio::operator+(const polinomio& p) const
{
    polinomio a = *this;
    polinomio b = p;
    a.L.splice(a.L.end(), b.L);
    a.simplify();
    a.sortItems();
    return a;
}

polinomio polinomio::operator-(const polinomio& p) const
{
    polinomio a = *this;
    polinomio b = p;
    b.negate();
    a.L.splice(a.L.end(), b.L);
    a.simplify();
    a.sortItems();
    return a;
}

polinomio polinomio::operator*(const polinomio& p) const
{
    polinomio result;
    for (auto i = L.begin(); i != L.end(); ++i) {
        for (auto j = p.L.begin(); j != p.L.end(); ++j) {
            monomio m = (*i)*(*j);
            result.addMonomio(m);
        }
    }
    result.simplify();
    return result;
}

polinomio& polinomio::operator=(const polinomio& p)
{
    L = p.L;        // utilizzo l'operatore di assegnazione tra liste
    return *this;
}

bool polinomio::operator==(const polinomio& p) const
{
    //PRE: i polinomi sono già stati semplificati e ordinati
    if (L.size() == p.L.size()) {
        for (auto i = L.begin(), j = p.L.begin(); i != L.end(), j != p.L.end(); ++i, ++j) {
            if (*i != *j)
                return false;
        }
        return true;
    }
    else return false;
}

bool polinomio::operator!=(const polinomio& p) const
{
    return !(*this == p);
}

ostream& operator<<(ostream& os, const polinomio& p)
{
    if (p.L.empty())
        return os << "Il polinomio e' vuoto";
    for (auto i = p.L.begin(); i != p.L.end(); ++i)
        os << *i;
    return os;
}
