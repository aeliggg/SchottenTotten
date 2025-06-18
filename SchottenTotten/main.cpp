#include <iostream>
#include "Cartes.h"
#include "Joueur.h"
#include "Partie.h"
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>
#include "Affichage.h"
#include <mmsystem.h>
#include <conio.h>
#pragma comment(lib, "winmm.lib")

// === Choix du mode de jeu avec flèches HAUT / BAS ===
int AfficheChoixModeJeuNavigable() {
    int choix = 0; // 0 = PvP, 1 = PvIA
    const std::string modes[3] = { "Joueur vs Joueur", "Joueur vs IA"};
    while (true) {
        clearConsole();
        std::cout << "=== Choisissez le mode de jeu ===\n\n";

        for (int i = 0; i < 2; ++i) {
            if (i == choix) {
                std::cout << " > [" << modes[i] << "]\n";
            }
            else {
                std::cout << "   " << modes[i] << "\n";
            }
        }

        std::cout << u8"\nUtilisez les flèches HAUT/BAS pour naviguer, Entrée pour valider." << std::endl;

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) { // Flèche HAUT
                choix = (choix - 1 + 2) % 2;
            }
            else if (key == 80) { // Flèche BAS
                choix = (choix + 1) % 2;
            }
        }
        else if (key == 13) {
            return choix + 1; // 1 = PvP, 2 = PvIA
        }
    }
}

int AfficheChoixTypeJeuNavigable() {
    int choix = 0; // Index du mode sélectionné (0 à 2)
    const int nbModes = 3;
    const std::string modes[nbModes] = { "Normal", "Expert", "Tactique" };

    while (true) {
        clearConsole();
        std::cout << "=== Choisissez le mode de jeu ===\n\n";

        for (int i = 0; i < nbModes; ++i) {
            if (i == choix) {
                std::cout << " > [" << modes[i] << "]\n";
            }
            else {
                std::cout << "   " << modes[i] << "\n";
            }
        }

        std::cout << u8"\nUtilisez les flèches HAUT/BAS pour naviguer, Entrée pour valider." << std::endl;

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) { // Flèche HAUT
                choix = (choix - 1 + nbModes) % nbModes;
            }
            else if (key == 80) { // Flèche BAS
                choix = (choix + 1) % nbModes;
            }
        }
        else if (key == 13) { // Entrée
            return choix + 1; // 1 = Normal, 2 = Expert, 3 = Tactique
        }
    }
}

int main() {
    std::cout << "Chargement du jeu ..." << std::endl;
    PlaySound(TEXT("Start_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
    //AfficheBanniereAnim();
    PlaySound(NULL, 0, 0);
    clearConsole();
    PlaySound(TEXT("musique.wav"), NULL, SND_FILENAME | SND_ASYNC);
    SetConsoleOutputCP(CP_UTF8);

    std::cout << u8"=== Bienvenue dans le jeu des Bornes ===\n\n";
    int choixMode = AfficheChoixModeJeuNavigable();
    int choixType = AfficheChoixTypeJeuNavigable();
    std::string Nom1, Nom2;
    std::cout << u8"\nJoueur 1, veuillez entrer votre prénom : ";
    std::cin >> Nom1;

    if (choixMode == 1) { // PvP
        std::cout << u8"Joueur 2, veuillez entrer votre prénom : ";
        std::cin >> Nom2;
    }
    else {
        Nom2 = "IA";
    }

    bool veutRejouer = true;
    while (veutRejouer) {
        clearConsole();

        Joueur* joueur1 = new Joueur(Nom1);
        Joueur* joueur2 = new Joueur(Nom2);
        Partie* partie = new Partie(joueur1, joueur2);

        std::cout << "Joueur 1 : " << joueur1->getNom() << std::endl;
        std::cout << "Joueur 2 : " << joueur2->getNom() << std::endl;

        std::vector<Cartes> cartes = partie->getCartes();
        std::cout << "Nombre total de cartes dans la partie : " << cartes.size() << std::endl;

        if (choixMode == 1 && choixType==1) {
            veutRejouer = partie->jouer(); // mode normal
        }
        else if (choixMode == 2 && choixType == 1){
            veutRejouer = partie->jouerIA(); // mode IA
        }
        delete partie;
        delete joueur1;
        delete joueur2;
    }

    return 0;
}
