#include "Borne.h"

Borne::Borne() : iBORnuméro(0) {}

Borne::Borne(int numéro) : iBORnuméro(numéro) {}

int Borne::getnumero() {
    return iBORnuméro;
}

void Borne::setnumero(int numéro) {
    iBORnuméro = numéro;
}

std::vector<Cartes> Borne::getCarteJ1() {
    return vBORcartesJ1;
}

std::vector<Cartes> Borne::getCarteJ2() {
    return vBORcartesJ2;
}


void Borne::ajouterCarteJ1(const Cartes& carte) {
    vBORcartesJ1.push_back(carte);
}

void Borne::ajouterCarteJ2(const Cartes& carte) {
    vBORcartesJ2.push_back(carte);
}
