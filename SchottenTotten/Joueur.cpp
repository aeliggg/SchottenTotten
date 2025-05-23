#include "Joueur.h"

Joueur::Joueur() {}

Joueur::Joueur(std::string& sNom) {
    sJOUnom = sNom;
}

std::string Joueur::getNom() {
    return sJOUnom;
}

void Joueur::setNom(std::string& nouveausJOUnom) {
    sJOUnom = nouveausJOUnom;
}

void Joueur::ajouterCarte(Cartes& carte) {
    vJOUCartesMain.push_back(carte);
}

void Joueur::retirerCarte(int index) {
    if (index >= 0 && index < static_cast<int>(vJOUCartesMain.size())) {
        vJOUCartesMain.erase(vJOUCartesMain.begin() + index);
    }
}

std::vector<Cartes> Joueur::getMain() {
    return vJOUCartesMain;
}
