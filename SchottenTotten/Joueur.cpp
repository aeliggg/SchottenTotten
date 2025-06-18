#include "Joueur.h"
#include <algorithm>

Joueur::Joueur() : sJOUnom("Inconnu") {}
Joueur::Joueur(const std::string& sNom) : sJOUnom(sNom) {}

std::string Joueur::getNom() const { return sJOUnom; }
void Joueur::setNom(const std::string& nouveauNom) { sJOUnom = nouveauNom; }

void Joueur::ajouterCarte(std::unique_ptr<Carte> carte) {
    vJOUCartesMain.push_back(std::move(carte));
}

void Joueur::AjouterBorne(Borne NewNbBorne) {
    BorneGagnee.push_back(NewNbBorne);
    std::sort(BorneGagnee.begin(), BorneGagnee.end());
}

std::vector<Borne> Joueur::getBorne() { return BorneGagnee; }
void Joueur::setBorne(std::vector<Borne> NewBorne) { BorneGagnee = NewBorne; }
void Joueur::setMain(std::vector<std::unique_ptr<Carte>> nouvelleMain) {
    vJOUCartesMain = std::move(nouvelleMain);
}

void Joueur::retirerCarte(const Carte& carte) {
    for (auto it = vJOUCartesMain.begin(); it != vJOUCartesMain.end(); ++it) {
        if ((*it)->getNumero() == carte.getNumero() && (*it)->getCouleur() == carte.getCouleur()) {
            vJOUCartesMain.erase(it);
            break;
        }
    }
}

std::vector<std::unique_ptr<Carte>>& Joueur::getMain() { return vJOUCartesMain; }

bool Joueur::EstGagnant() {
    if (BorneGagnee.size() < 3) return false;
    std::vector<int> numeros;
    for (auto& borne : BorneGagnee) {
        numeros.push_back(borne.getnumero());
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