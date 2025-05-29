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
        std::cout << std::string(44-(getTailleTexteASCII(texte)/2), ' ') << line << std::endl;
    }
}


void AfficheCarte(const Cartes& carte) {
    switch (CouleurToEnum(carte.getcouleur())) {
    case BLEU:
        std::cout << "\033[34m" << carte.getnumero() << "\033[0m ";
        break;
    case VERT:
        std::cout << "\033[32m" << carte.getnumero() << "\033[0m ";
        break;
    case JAUNE:
        std::cout << "\033[33m" << carte.getnumero() << "\033[0m ";
        break;
    case ROUGE:
        std::cout << "\033[31m" << carte.getnumero() << "\033[0m ";
        break;
    case VIOLET:
        std::cout << "\033[35m" << carte.getnumero() << "\033[0m ";
        break;
    case ORANGE:
        std::cout << "\033[38;5;208m" << carte.getnumero() << "\033[0m ";
        break;
    default:
        std::cout << carte.getnumero() << std::endl;
        break;
    }

}

void AfficherBornes(const std::vector<Borne>& bornes, const std::vector<Cartes>& main1, const std::vector<Cartes>& main2) {
    for (unsigned int uiLigneDeCartes = 0; uiLigneDeCartes < 3; uiLigneDeCartes++) {
        for (unsigned int i = 0; i < bornes.size(); ++i) {
            std::vector<Cartes> cartesJ1 = bornes[i].getCarteJ1();
            if (cartesJ1.size()<=uiLigneDeCartes) {
                std::cout << "    0     ";
            }
            else {
                std::cout << "    ";
                AfficheCarte(cartesJ1[uiLigneDeCartes]);
                std::cout << "    ";
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
                std::cout << "    0     ";
            }
            else {
                std::cout << "    ";
                AfficheCarte(cartesJ2[uiLigneDeCartes]);
                std::cout << "    ";
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