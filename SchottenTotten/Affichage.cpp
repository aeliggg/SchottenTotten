#include "Affichage.h"
#include "Borne.h"
#include "Cartes.h"
#include <cstdlib>
#include <sstream>
#include <string>
#include "Figlet.hh" 

CouleurCarte CouleurToEnum(const std::string& couleur) {
    if (couleur == "bleu") return BLEU;
    if (couleur == "vert") return VERT;
    if (couleur == "jaune") return JAUNE;
    if (couleur == "rouge") return ROUGE;
    if (couleur == "violet") return VIOLET;
    if (couleur == "orange") return ORANGE;
    return INCONNU;
}

unsigned int getTailleTexteASCII(const std::string& texte) {
    std::ostringstream oss;
    Figlet::standard.print(texte.c_str(), oss);
    std::istringstream iss(oss.str());
    std::string line;
    unsigned int max_width = 0;
    while (std::getline(iss, line)) {
        if (line.length() > max_width) max_width = line.length();
    }
    return max_width;
}

void AfficheASCII(const std::string& texte) {
    std::ostringstream oss;
    Figlet::standard.print(texte.c_str(), oss);
    std::istringstream iss(oss.str());
    std::string line;
    while (std::getline(iss, line)) {
        std::cout << std::string(45-(getTailleTexteASCII(texte)/2), ' ') << line << std::endl;
    }
}


void AfficheCarte(const Cartes& carte) {
    switch (CouleurToEnum(carte.getcouleur())) {
    case BLEU:
        std::cout << "\033[94m" << carte.getnumero() << "\033[0m ";
        break;
    case VERT:
        std::cout << "\033[32m" << carte.getnumero() << "\033[0m ";
        break;
    case JAUNE:
        std::cout << "\033[38;2;255;255;85m" << carte.getnumero() << "\033[0m ";
        break;
    case ROUGE:
        std::cout << "\033[31m" << carte.getnumero() << "\033[0m ";
        break;
    case VIOLET:
        std::cout << "\033[38;2;199;0;255m" << carte.getnumero() << "\033[0m ";
        break;
    case ORANGE:
        std::cout << "\033[38;5;208m" << carte.getnumero() << "\033[0m ";
        break;
    default:
        std::cout << carte.getnumero() << std::endl;
        break;
    }
}

/*
// Utilisation de std::wstring pour les caractères Unicode
            std::wstring message = L"     ?        ?        ?        ?        ?        ?        ?        ?        ?    ";

            // Conversion de std::wstring en UTF-8 pour l'affichage
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            std::string utf8Message = converter.to_bytes(message);

            std::cout << utf8Message << std::endl;
*/

#include <iostream>
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>

void AfficherBornesRevendiquees(Joueur* joueur) {
    if (joueur->getBorne().size() != 0) {
        std::string check = u8"✅";

        for (unsigned int uiIndex = 0; uiIndex < joueur->getBorne().size(); uiIndex++) {
            if (joueur->getBorne()[uiIndex].getnumero() == 1) {
                std::cout << std::string(5, ' ') << check ;
            }
            else if (joueur->getBorne()[uiIndex].getnumero() != 1 && uiIndex == 0) {
                std::cout << std::string(5 + (joueur->getBorne()[uiIndex].getnumero() - 1) * 10, ' ') << check;
            }
            else if (joueur->getBorne()[uiIndex].getnumero() - joueur->getBorne()[uiIndex - 1].getnumero() == 1) {
                std::cout << std::string(((joueur->getBorne()[uiIndex].getnumero() - joueur->getBorne()[uiIndex - 1].getnumero()) * 8), ' ') << check;
            }
            else {
                std::cout << std::string((joueur->getBorne()[uiIndex].getnumero() - joueur->getBorne()[uiIndex - 1].getnumero() - 1) * 10 + 8, ' ') << check ;
            }
        }
        std::cout << "\n";
    }
}

void AfficherBornes(const std::vector<Borne>& bornes, const std::vector<Cartes>& main1, const std::vector<Cartes>& main2) {
    for (unsigned int uiLigneDeCartes = 0; uiLigneDeCartes < 3; uiLigneDeCartes++) {
        for (unsigned int i = 0; i < bornes.size(); ++i) {
            std::vector<Cartes> cartesJ1 = bornes[i].getCarteJ1();
            if (cartesJ1.size()<=uiLigneDeCartes) {
                std::cout << "     0    ";
            }
            else {
                std::cout << "     ";
                AfficheCarte(cartesJ1[uiLigneDeCartes]);
                std::cout << "   ";
            }
        }
        if (uiLigneDeCartes != 2) {
            std::cout << "\n";
        }
    }
    std::cout << "\n -----------------------------------------------------------------------------------------\n";
    for (unsigned int i = 0; i < bornes.size(); ++i) {
        std::cout << "| Borne " << bornes[i].getnumero() << " ";
    }
    std::cout << "|\n";
    std::cout << " -----------------------------------------------------------------------------------------\n";
    for (unsigned int uiLigneDeCartes = 0; uiLigneDeCartes < 3; uiLigneDeCartes++) {
        for (unsigned int i = 0; i < bornes.size(); ++i) {
            std::vector<Cartes> cartesJ2 = bornes[i].getCarteJ2();
            if (cartesJ2.size()<=uiLigneDeCartes) {
                std::cout << "     0    ";
            }
            else {
                std::cout << "     ";
                AfficheCarte(cartesJ2[uiLigneDeCartes]);
                std::cout << "   ";
            }
        }
        std::cout << "\n";
    }
}


void clearConsole() {
    #if defined(_WIN32)
        system("cls");
    #else
        system("clear");
    #endif
}