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

    partie.jouer();

    return 0;
}
