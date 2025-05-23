#include <iostream>
#include "Cartes.h"
#include "Joueur.h"
#include "Partie.h"

int main() {
    // Création de deux joueurs
    std::string Nom1 = "Alice";
    std::string Nom2 = "Bob";
    Joueur joueur1(Nom1);
    Joueur joueur2(Nom2);

    // Création de la partie
    Partie partie(&joueur1, &joueur2);

    // Affichage des joueurs
    std::cout << "Joueur 1 : " << joueur1.getNom() << std::endl;
    std::cout << "Joueur 2 : " << joueur2.getNom() << std::endl;

    // Récupération et affichage du nombre de cartes
    std::vector<Cartes> cartes = partie.getCartes();
    std::cout << "Nombre total de cartes dans la partie : " << cartes.size() << std::endl;

    // Distribution de 6 cartes à chaque joueur
    for (unsigned int uiIndex = 0; uiIndex < 6; ++uiIndex) {
        joueur1.ajouterCarte(cartes[uiIndex]);
        joueur2.ajouterCarte(cartes[uiIndex + 6]);
    }

    // Affichage des cartes de la main de joueur 1
    std::cout << "\nMain de " << joueur1.getNom() << " :" << std::endl;
    std::vector<Cartes> main1 = joueur1.getMain();
    for (unsigned int uiIndex = 0; uiIndex < main1.size(); ++uiIndex) {
        std::cout << "Carte " << main1[uiIndex].getnumero()
            << " de couleur " << main1[uiIndex].getcouleur() << std::endl;
    }

    // Affichage des cartes de la main de joueur 2
    std::cout << "\nMain de " << joueur2.getNom() << " :" << std::endl;
    std::vector<Cartes> main2 = joueur2.getMain();
    for (unsigned int uiIndex = 0; uiIndex < main2.size(); ++uiIndex) {
        std::cout << "Carte " << main2[uiIndex].getnumero()
            << " de couleur " << main2[uiIndex].getcouleur() << std::endl;
    }

    return 0;
}
