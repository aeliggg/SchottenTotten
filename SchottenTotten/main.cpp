#include <iostream>
#include "Cartes.h"
#include "Joueur.h"
#include "Partie.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>
#include "Affichage.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::string Nom1;
    std::cout << u8"Joueur 1 veuillez entrer votre prénom\n";
    std::cin >> Nom1;
    std::string Nom2;
    std::cout << u8"Joueur 2 veuillez entrer votre prénom\n";
    std::cin >> Nom2;
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

#include <iostream>
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>
/*
int main() {
    // Configure la console pour utiliser UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Utilisation de std::wstring pour les caractères Unicode
    std::wstring message = L"Bonjour ✅, voici un emoji dans la console !❎";

    // Conversion de std::wstring en UTF-8 pour l'affichage
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string utf8Message = converter.to_bytes(message);

    std::cout << utf8Message << std::endl;
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
}*/