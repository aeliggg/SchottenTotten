#include "Borne.h"

Borne::Borne() : iBORnuméro(0) {}

Borne::Borne(int numéro) : iBORnuméro(numéro) {}

int Borne::getnumero() {
    return iBORnuméro;
}

void Borne::setnumero(int numéro) {
    iBORnuméro = numéro;
}
