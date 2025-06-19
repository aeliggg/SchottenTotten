#include "PartieExpertPvP.h"
#include "Partie.h"
#include "PartieExpert.h"
#include "Affichage.h"
#include "Borne.h"
#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>
#include <random>
#include <ctime>
#include <windows.h>
#include <codecvt>
#include <locale>
#include <conio.h>
#include <limits>
#include <iomanip>
#include <thread> 

bool PartieExpertPvP::jouer() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::shuffle(cartes.begin(), cartes.end(), std::default_random_engine(std::rand()));

    DistribuerCartes();

    std::cout << u8"Début de la partie entre " << joueur1->getNom() << " et " << joueur2->getNom() << " !\n";
    bool bPartieFinie = 0;
    bool veutRejouer = FALSE;
    int tour = 0;
    while (bPartieFinie == 0) {
        if (tour != 0) {
            clearConsole();
        }
        SetConsoleOutputCP(CP_UTF8);
        TourDePartie(tour, bornes, joueur1, joueur2, 1);

        bPartieFinie = AfficherVictoire(bornes, joueur1, joueur2); // AfficherVictoire renvoie 1 dans le cas où la partie est terminée
        if (bPartieFinie) { 
            veutRejouer=FinDePartie(); 
        }
        else { // TOUR DU DEUXIEME JOUEUR
            clearConsole();
            TourDePartie(tour, bornes, joueur2, joueur1, 2);

            bPartieFinie = AfficherVictoire(bornes, joueur1, joueur2);
            if (bPartieFinie) {
                veutRejouer = FinDePartie();
            }
        }
        tour++;
    }
    return veutRejouer;
}