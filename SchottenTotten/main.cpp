#include <iostream>
#include "Carte.h"
#include "Joueur.h"
#include "Partie.h"
#include "PartieClassique.h"
#include "PartieClassiquePvP.h"
#include "PartieClassiquePvIA.h"
#include "PartieExpert.h"
#include "PartieExpertPvP.h"
#include "PartieExpertPvIA.h"
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>
#include "Affichage.h"
#include <mmsystem.h>
#include <conio.h>
#pragma comment(lib, "winmm.lib")

Partie* CreationPartie(int choixVariable, int choixMode, Joueur* Joueur1, Joueur* Joueur2) {
    Partie* partie = nullptr;
    if (choixVariable == 1) { //Si on a choisi la variable classique
        if (choixMode == 1) {
            partie = new PartieClassiquePvP(Joueur1, Joueur2);
        }
        else {
            partie = new PartieClassiquePvIA(Joueur1, Joueur2);
        }
    }
    else if (choixVariable == 2) { //Variable expert
        if (choixMode == 1) {
            partie = new PartieExpertPvP(Joueur1, Joueur2);
        }
        else {
            partie = new PartieExpertPvIA(Joueur1, Joueur2);
        }
    }
    else {
        if (choixMode == 1) {
            //partie = new PartieTactiquePvP(Joueur1, Joueur2);
        }
        else {
            //partie = new PartieTactiquePvIA(Joueur1, Joueur2);
        }
    }

    return partie;
}

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

int AfficheChoixVariableJeuNavigable() {
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
    int choixVariable = AfficheChoixVariableJeuNavigable();
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


        std::cout << "Joueur 1 : " << joueur1->getNom() << std::endl;
        std::cout << "Joueur 2 : " << joueur2->getNom() << std::endl;
        Partie* partie = CreationPartie(choixVariable, choixMode,joueur1,joueur2);
        partie->jouer();
    }
    return 0;
}
