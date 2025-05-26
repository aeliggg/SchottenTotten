#include "Joueur.h"

Joueur::Joueur() : sJOUnom("Inconnu") {}

Joueur::Joueur(const std::string& sNom) : sJOUnom(sNom) {}

std::string Joueur::getNom() const {
    return sJOUnom;
}

void Joueur::setNom(const std::string& nouveauNom) {
    sJOUnom = nouveauNom;
}

void Joueur::ajouterCarte(const Cartes& carte) {
    vJOUCartesMain.push_back(carte);
}

void Joueur::retirerCarte(int index) {
    if (index >= 0 && static_cast<size_t>(index) < vJOUCartesMain.size()) {
        vJOUCartesMain.erase(vJOUCartesMain.begin() + index);
    }
}

std::vector<Cartes> Joueur::getMain() const {
    return vJOUCartesMain;
}
