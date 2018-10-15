#include "monomio.h"

// costruttori/distruttori
monomio::monomio(int c, int e) : coeff(c), exp(e)
{
    if (coeff == 0)     // se il coefficiente è uguale a 0
        exp = 0;        // setto anche l'esponente a 0
}

// metodi di supporto
int monomio::getCoeff() const
{
    return coeff;
}

int monomio::getExp() const
{
    return exp;
}

// metodi di classe
QString monomio::toQString() const
{
    QString s;
    // se il coefficiente è nullo
    if (!coeff) {
        s = "+0";
        return s;
    }
    // se l'esponente è nullo
    if (!exp) {
        if (coeff > 0)
            s = '+' + QString::number(coeff);
        else s = QString::number(coeff);
        return s;
    }
    // se coefficiente ed esponente non sono nulli
    if (coeff == 1)
        s = '+';
    if (coeff == -1)
        s = '-';
    if (coeff > 0 && coeff != 1)
        s = '+' + QString::number(coeff);
    if (coeff < 0 && coeff != -1)
        s = QString::number(coeff);
    // se exp == 1, altrimenti
    if (exp == 1)
        s = s + 'x';
    else s = s + "x^" + QString::number(exp);
    return s;
}

// overloading degli operatori
monomio monomio::operator+(const monomio& m) const
{
    if (exp != m.exp)
        throw eccezione("ERRORE\nNon puoi sommare monomi con esponenti diversi");
    return monomio(coeff + m.coeff, exp);

}

monomio monomio::operator-(const monomio& m) const
{
    if (exp != m.exp)
        throw eccezione("ERRORE\nNon puoi sottrarre monomi con esponenti diversi");
    return monomio(coeff - m.coeff, exp);
}

monomio monomio::operator*(const monomio& m) const
{
    return monomio(coeff * m.coeff, exp + m.exp);
}

monomio monomio::operator/(const monomio& m) const
{
    return monomio(coeff / m.coeff, exp - m.exp);
}

bool monomio::operator<(const monomio& m) const
{
    return exp < m.exp || (exp == m.exp && coeff < m.coeff);
}

bool monomio::operator==(const monomio& m) const
{
    return coeff == m.coeff && exp == m.exp;
}

bool monomio::operator!=(const monomio& m) const
{
    return !(*this == m);
}

ostream& operator<<(ostream& os, const monomio& m)
{
    if (!m.coeff)
        return os << "+0";
    if (!m.exp)
        return os << showpos << m.coeff;
    if (m.coeff == 1) {
        if (m.exp == 1)
            return os << "+x";
        return os << "+x^" << noshowpos << m.exp;
    }
    if (m.coeff == -1) {
        if (m.exp == 1)
            return os << "-x";
        return os << "-x^" << noshowpos << m.exp;
    }
    if (m.exp == 1)
        return os << showpos << m.coeff << "x";
    return os << showpos << m.coeff << "x^" << noshowpos << m.exp;
}
