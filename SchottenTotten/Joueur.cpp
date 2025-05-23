#include "Joueur.h"

Joueur::Joueur() {}

Joueur::Joueur(const std::string& sJOUnom) {}

std::string Joueur::getsJOUnom() {
    return sJOUnom;
}

void Joueur::setsJOUnom(const std::string& nouveausJOUnom) {
    sJOUnom = nouveausJOUnom;
}

void Joueur::ajouterCarte(const Cartes& carte) {
    vJOUCartesMain.push_back(carte);
}

void Joueur::retirerCarte(int index) {
    if (index >= 0 && index < static_cast<int>(vJOUCartesMain.size())) {
        vJOUCartesMain.erase(vJOUCartesMain.begin() + index);
    }
}

std::vector<Cartes> Joueur::getMain() const {
    return vJOUCartesMain;
}
