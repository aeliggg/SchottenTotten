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

void Joueur::retirerCarte(const Cartes& carte) {
    for (size_t i = 0; i < vJOUCartesMain.size(); ++i) {
        if (vJOUCartesMain[i].getnumero() == carte.getnumero() && vJOUCartesMain[i].getcouleur() == carte.getcouleur()) {
            vJOUCartesMain.erase(vJOUCartesMain.begin() + i);
            break;
        }
    }
}
const std::vector<Cartes>& Joueur::getMain() const {
    return vJOUCartesMain;
}
