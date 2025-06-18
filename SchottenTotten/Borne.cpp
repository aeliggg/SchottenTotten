#include "Borne.h"
#include <iostream>

Borne::Borne() : iBORnuméro(0) {}
Borne::Borne(int numéro) : iBORnuméro(numéro) {}

int Borne::getnumero() const { return iBORnuméro; }
Joueur* Borne::getGagnant() const { return GagnantBorne; }
Joueur* Borne::getFirst() const { return FirstPlayer; }
void Borne::setnumero(int numéro) { iBORnuméro = numéro; }

const std::vector<std::unique_ptr<Carte>>& Borne::getCarteJ1() const {
    return vBORcartesJ1;
}
const std::vector<std::unique_ptr<Carte>>& Borne::getCarteJ2() const {
    return vBORcartesJ2;
}

void Borne::ajouterCarteJ1(std::unique_ptr<Carte> carte) {
    if (vBORcartesJ1.size() < (combatDeBoue ? 4 : 3)) {
        vBORcartesJ1.push_back(std::move(carte));
    }
    else {
        std::cout << "Deja " << (combatDeBoue ? 4 : 3) << " cartes sur la borne" << std::endl;
    }
}
void Borne::ajouterCarteJ2(std::unique_ptr<Carte> carte) {
    if (vBORcartesJ2.size() < (combatDeBoue ? 4 : 3)) {
        vBORcartesJ2.push_back(std::move(carte));
    }
    else {
        std::cout << "Deja " << (combatDeBoue ? 4 : 3) << " cartes sur la borne" << std::endl;
    }
}

bool Borne::operator<(const Borne& other) const {
    return iBORnuméro < other.iBORnuméro;
}

void Borne::viderCartes() {
    vBORcartesJ1.clear();
    vBORcartesJ2.clear();
    protegee = false;
}