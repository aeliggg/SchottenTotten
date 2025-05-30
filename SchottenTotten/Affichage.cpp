#include "Affichage.h"
#include "Borne.h"
#include "Cartes.h"
#include <cstdlib>
#include <sstream>
#include <string>
#include "Figlet.hh"
#include <iostream>
#include <windows.h>
#include <codecvt>
#include <locale>
#include <thread>
#include <chrono>

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

void AffichePlateau(const std::vector<Borne>& bornes,Joueur*joueur1, Joueur*joueur2 ) {
    AfficheASCII(joueur1->getNom());
    AfficherBornesRevendiquees(joueur1);
    AfficherBornes(bornes, joueur1->getMain(), joueur2->getMain());
    AfficherBornesRevendiquees(joueur2);
    AfficheASCII(joueur2->getNom());
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

int AfficherReady(int ready) {
    std::cout << u8"\nÉcrire 1 si vous êtes prêt à voir votre main : ";
    while (!(std::cin >> ready) || ready != 1) {
        std::cin.clear();
        std::string dummy;
        std::getline(std::cin, dummy);
        std::cout << u8"\nEntrée invalide. Veuillez saisir 1 pour continuer : ";
    }
    return ready;
}

std::vector<Cartes> AfficherMain(Joueur* joueur){
    std::vector<Cartes> main = joueur->getMain();
    
    std::sort(main.begin(), main.end(), [](const Cartes& a, const Cartes& b) {  //Range les cartes par couleurs et par numero
        if (a.getcouleur() != b.getcouleur())
            return a.getcouleur() < b.getcouleur();
        return a.getnumero() < b.getnumero();
        });
    
    std::cout << "\nVoici la main de " << joueur->getNom() << " : \n";
    for (size_t i = 0; i < main.size(); ++i) {
        AfficheCarte(main[i]);
    }
    return main;
}

void AfficherBorneGagnee(Joueur* joueur1, Borne borne) {
    std::string message = "Borne " + std::to_string(borne.getnumero()) + " :";
    AfficheASCII(message);
    AfficheASCII(joueur1->getNom());

    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void AfficherVictoire(Joueur* joueur1, Joueur* joueur2) {
    if (joueur1->getBorne().size() == 5) {
        cout << "\nLa partie est gagnée par " << joueur1->getNom() << endl;
        return;
    }
    if (joueur2->getBorne().size() == 5) {
        cout << "\nLa partie est gagnée par " << joueur2->getNom() << endl;
        return;
    }
    if (joueur2->EstGagnant()) {
        cout << "\nLa partie est gagnée par " << joueur2->getNom() << endl;
        return;
    }
    if (joueur1->EstGagnant()) {
        cout << "\nLa partie est gagnée par " << joueur1->getNom() << endl;
        return;
    }
}

void clearConsole() {
    #if defined(_WIN32)
        system("cls");
    #else
        system("clear");
    #endif
}