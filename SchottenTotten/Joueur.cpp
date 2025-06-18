#include "Joueur.h"
#include <limits>
#include <algorithm>
Joueur::Joueur() : sJOUnom("Inconnu") {}

Joueur::Joueur(const std::string& sNom) : sJOUnom(sNom) {}

std::string Joueur::getNom() const {
    return sJOUnom;
}

void Joueur::setNom(const std::string& nouveauNom) {
    sJOUnom = nouveauNom;
}

void Joueur::ajouterCarte(const Carte& carte) {
    vJOUCartesMain.push_back(carte);
}

void Joueur::AjouterBorne(Borne NewNbBorne) { 
    BorneGagnee.push_back(NewNbBorne); 
    std::sort(BorneGagnee.begin(),BorneGagnee.end());
}


void Joueur::retirerCarte(const Carte& carte) {
    for (size_t i = 0; i < vJOUCartesMain.size(); ++i) {
        if (vJOUCartesMain[i].getNumero() == carte.getNumero() && vJOUCartesMain[i].getCouleur() == carte.getCouleur()) {
            vJOUCartesMain.erase(vJOUCartesMain.begin() + i);
            break;
        }
    }
}
const std::vector<Carte>& Joueur::getMain() const {
    return vJOUCartesMain;
}

void Joueur::setMain(const std::vector<Carte>& nouvelleMain) {
    vJOUCartesMain = nouvelleMain;
}

bool Joueur::EstGagnant() {
    if (BorneGagnee.size() < 3) return false;
    std::vector<int> numeros;
    for (size_t i = 0; i < BorneGagnee.size(); ++i) {
        numeros.push_back(BorneGagnee[i].getnumero());
    }
    std::sort(numeros.begin(), numeros.end());
    for (size_t i = 0; i <= numeros.size() - 3; ++i) {
        if (numeros[i + 1] == numeros[i] + 1 &&
            numeros[i + 2] == numeros[i + 1] + 1) {
            return true;
        }
    }

    return false;
}
