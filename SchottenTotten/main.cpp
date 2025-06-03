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
#pragma comment(lib, "winmm.lib")

int main() {
    std::cout << "Chargement du jeu ..." << std::endl;
    PlaySound(TEXT("Start_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
    //AfficheBanniereAnim();
    PlaySound(NULL, 0, 0);
    clearConsole();
    PlaySound(TEXT("musique.wav"), NULL, SND_FILENAME | SND_ASYNC);
    SetConsoleOutputCP(CP_UTF8);
    std::string Nom1;
    std::cout << u8"Joueur 1 veuillez entrer votre prénom\n";
    std::cin >> Nom1;
    std::string Nom2;
    std::cout << u8"Joueur 2 veuillez entrer votre prénom\n";
    std::cin >> Nom2;
    Joueur joueur1(Nom1);
    Joueur joueur2(Nom2);
    bool veutRejouer = TRUE;
    while (veutRejouer == TRUE) {
        clearConsole();
        Joueur* joueur1 = new Joueur(Nom1);
        Joueur* joueur2 = new Joueur(Nom2);
        Partie* partie = new Partie(joueur1, joueur2);

        std::cout << "Joueur 1 : " << joueur1->getNom() << std::endl;
        std::cout << "Joueur 2 : " << joueur2->getNom() << std::endl;

        std::vector<Cartes> cartes = partie->getCartes();
        std::cout << "Nombre total de cartes dans la partie : " << cartes.size() << std::endl;

        veutRejouer = partie->jouer();
        delete partie;
    }
    return 0;
}
