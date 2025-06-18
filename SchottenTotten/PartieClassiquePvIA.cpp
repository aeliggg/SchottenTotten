#include "Partie.h"
#include "PartieClassique.h"
#include "PartieClassiquePvIA.h"
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



void PartieClassiquePvIA::TourDePartieIA(int tour, std::vector<Borne>& bornes, Joueur* IA, Joueur* adversaire, int numJoueur) {
    TrierMain(IA);
    int choixCarte = (rand() % IA->getMain().size()) + 1;
    int choixBorne = (rand() % 9) + 1;
    while (bornes[choixBorne - 1].getGagnant() != NULL || bornes[choixBorne - 1].getCarteJ2().size() == 3) {
        choixBorne = (rand() % 9) + 1;
    }
    UpdatePlateauApresCoupJoueur(IA, choixCarte, bornes, choixBorne, numJoueur);
    VerifieBorneGagnee(choixBorne);
    clearConsole();
    if (numJoueur == 1) {
        AffichePlateau(bornes, IA, adversaire);
    }
    else {
        AffichePlateau(bornes, adversaire, IA);
    }
}


bool PartieClassiquePvIA::jouer() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::shuffle(cartes.begin(), cartes.end(), std::default_random_engine(std::rand()));
    DistribuerCartes();
    std::cout << u8"Début de la partie entre " << joueur1->getNom() << " et l'IA";
    joueur2->setNom("IA");
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
        if (bPartieFinie) { FinDePartie(); }
        else { // TOUR DU DEUXIEME JOUEUR
            clearConsole();
            TourDePartieIA(tour, bornes, joueur2, joueur1, 2);

            bPartieFinie = AfficherVictoire(bornes, joueur1, joueur2);
            if (bPartieFinie) {
                veutRejouer = FinDePartie();
            }
        }
        tour++;
    }
    return veutRejouer;
}
