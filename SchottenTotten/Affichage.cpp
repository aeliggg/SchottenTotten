#include "Affichage.h"
#include "Borne.h"
#include "Cartes.h"

CouleurCarte CouleurToEnum(const std::string& couleur) {
    if (couleur == "bleu") return BLEU;
    if (couleur == "vert") return VERT;
    if (couleur == "jaune") return JAUNE;
    if (couleur == "rouge") return ROUGE;
    if (couleur == "violet") return VIOLET;
    if (couleur == "orange") return ORANGE;
    return INCONNU;
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

void AfficherBornes(std::vector<Borne> bornes, std::vector<Cartes> main1, std::vector<Cartes> main2) {
    std::cout << "\n=== Résumé des cartes sur les bornes ===\n";

    for (unsigned int i = 0; i < bornes.size(); ++i) {

        std::vector<Cartes> cartesJ1 = bornes[i].getCarteJ1();
        if (cartesJ1.empty()) {
            std::cout << "    0     ";
        }
        else {
            for (unsigned int j = 0; j < cartesJ1.size(); ++j) {
                std::cout << "     ";
                AfficheCarte(main1[j]);
                std::cout << "     ";
            }
        }
    }
    std::cout << "\n -----------------------------------------------------------------------------------------\n";
    for (unsigned int i = 0; i < bornes.size(); ++i) {

        std::cout << "| Borne " << bornes[i].getnumero() << " ";
    }
    std::cout << "| ";
    std::cout << "\n -----------------------------------------------------------------------------------------\n";

    for (unsigned int i = 0; i < bornes.size(); ++i) {

        std::vector<Cartes> cartesJ2 = bornes[i].getCarteJ2();
        if (cartesJ2.empty()) {
            std::cout << "    0     ";
        }
        else {
            for (unsigned int j = 0; j < cartesJ2.size(); ++j) {
                std::cout << "     ";
                AfficheCarte(main2[j]);
                std::cout << "     ";
            }
        }
    }
}