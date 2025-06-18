#include "PartieExpertPvIA.h"
#include "Affichage.h"
#include <random>
#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>
#include <windows.h>

void PartieExpertPvIA::TourDePartieIA(int tour, std::vector<Borne>& bornes, Joueur* IA, Joueur* adversaire, int numJoueur) {
    TrierMain(IA);
    int choixCarte = (rand() % IA->getMain().size()) + 1;
    int choixBorne = (rand() % 9) + 1;
    while (bornes[choixBorne - 1].getGagnant() != nullptr || bornes[choixBorne - 1].getCarteJ2().size() == 3) {
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

bool PartieExpertPvIA::jouer() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::shuffle(cartes.begin(), cartes.end(), std::default_random_engine(std::rand()));
    DistribuerCartes();
    std::cout << "Début de la partie entre " << joueur1->getNom() << " et l'IA";
    joueur2->setNom("IA");
    bool bPartieFinie = false;
    bool veutRejouer = false;
    int tour = 0;
    while (!bPartieFinie) {
        if (tour != 0) { clearConsole(); }
        SetConsoleOutputCP(CP_UTF8);
        TourDePartie(tour, bornes, joueur1, joueur2, 1);

        bPartieFinie = AfficherVictoire(bornes, joueur1, joueur2);
        if (bPartieFinie) { veutRejouer = FinDePartie(); }
        else {
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