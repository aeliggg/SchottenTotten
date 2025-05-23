#include "Partie.h"

Partie::Partie(){
    std::vector<std::string> couleurs = { "rouge", "bleu", "vert", "jaune", "violet", "orange" };

    for (unsigned int uiIndexCouleur = 0; uiIndexCouleur < couleurs.size(); ++uiIndexCouleur) {
        for (unsigned int uiIndexNumero = 1; uiIndexNumero <= 9; ++uiIndexNumero) {
            Cartes carte(uiIndexNumero, couleurs[uiIndexCouleur]);
            ajouterCarte(carte);
        }
    }
}

Partie::Partie(Joueur* j1, Joueur* j2) {
    std::vector<std::string> couleurs = { "rouge", "bleu", "vert", "jaune", "violet", "orange" };

    for (unsigned int uiIndexCouleur = 0; uiIndexCouleur < couleurs.size(); ++uiIndexCouleur) {
        for (unsigned int uiIndexNumero = 1; uiIndexNumero <= 9; ++uiIndexNumero) {
            Cartes carte(uiIndexNumero, couleurs[uiIndexCouleur]);
            ajouterCarte(carte);
        }
    }
}

void Partie::ajouterCarte(const Cartes& carte) {
    cartes.push_back(carte);
}

std::vector<Cartes> Partie::getCartes() {
    return cartes;
}

Joueur* Partie::getJoueur1() {
    return joueur1;
}

Joueur* Partie::getJoueur2() {
    return joueur2;
}
