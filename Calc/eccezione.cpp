#include "eccezione.h"

// costruttori/distruttori
eccezione::eccezione(const QString& s) : msg(s) {}

// metodi di supporto
QString eccezione::getMsg() const
{
    return msg;
}
