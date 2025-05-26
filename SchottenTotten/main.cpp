#include <iostream>
#include "Cartes.h"
#include "Joueur.h"
#include "Partie.h"

int main() {
    std::string Nom1 = "Alice";
    std::string Nom2 = "Bob";
    Joueur joueur1(Nom1);
    Joueur joueur2(Nom2);

    Partie partie(&joueur1, &joueur2);

    std::cout << "Joueur 1 : " << joueur1.getNom() << std::endl;
    std::cout << "Joueur 2 : " << joueur2.getNom() << std::endl;

    std::vector<Cartes> cartes = partie.getCartes();
    std::cout << "Nombre total de cartes dans la partie : " << cartes.size() << std::endl;


    std::cout << "\nMain de " << joueur1.getNom() << " :" << std::endl;
    std::vector<Cartes> main1 = joueur1.getMain();
    for (unsigned int uiIndex = 0; uiIndex < main1.size(); ++uiIndex) {
        std::cout << "Carte " << main1[uiIndex].getnumero() << " de couleur " << main1[uiIndex].getcouleur() << std::endl;
    }

    std::cout << "\nMain de " << joueur2.getNom() << " :" << std::endl;
    std::vector<Cartes> main2 = joueur2.getMain();
    for (unsigned int uiIndex = 0; uiIndex < main2.size(); ++uiIndex) {
        std::cout << "Carte " << main2[uiIndex].getnumero() << " de couleur " << main2[uiIndex].getcouleur() << std::endl;
    }
    partie.jouer();

    return 0;
}
