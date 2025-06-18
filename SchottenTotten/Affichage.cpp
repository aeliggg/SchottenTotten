#include "Affichage.h"
#include "Borne.h"
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
#include <conio.h>

// Utilitaire couleur
CouleurCarte CouleurToEnum(const std::string& couleur) {
    if (couleur == "bleu") return BLEU;
    if (couleur == "vert") return VERT;
    if (couleur == "jaune") return JAUNE;
    if (couleur == "rouge") return ROUGE;
    if (couleur == "violet") return VIOLET;
    if (couleur == "orange") return ORANGE;
    return INCONNU;
}

// Affichage d'une carte shared_ptr
void AfficheCarte(const Carte* carte) {
    if (!carte) { std::cout << " "; return; }
    switch (CouleurToEnum(carte->getCouleur())) {
    case BLEU:   std::cout << "\033[94m" << carte->getNumero() << "\033[0m"; break;
    case VERT:   std::cout << "\033[32m" << carte->getNumero() << "\033[0m"; break;
    case JAUNE:  std::cout << "\033[38;2;255;255;85m" << carte->getNumero() << "\033[0m"; break;
    case ROUGE:  std::cout << "\033[31m" << carte->getNumero() << "\033[0m"; break;
    case VIOLET: std::cout << "\033[38;2;199;0;255m" << carte->getNumero() << "\033[0m"; break;
    case ORANGE: std::cout << "\033[38;5;208m" << carte->getNumero() << "\033[0m"; break;
    default:     std::cout << carte->getNumero();
    }
}

// Affichage ASCII (inchangé)
void AfficheASCII(const std::string& texte) {
    std::ostringstream oss;
    Figlet::standard.print(texte.c_str(), oss);
    std::istringstream iss(oss.str());
    std::string line;
    while (std::getline(iss, line)) {
        std::cout << std::string(45 - (line.size() / 2), ' ') << "\033[36m" << line << "\033[0m" << std::endl;
    }
}

void AffichePlateau(const std::vector<Borne>& bornes, Joueur* joueur1, Joueur* joueur2) {
    AfficheASCII(joueur1->getNom());
    AfficherBornesRevendiqueesPlusAJ(joueur1);
    AfficherBornesPlusAJ(bornes, joueur1->getMain(), joueur2->getMain());
    AfficherBornesRevendiquees(joueur2);
    AfficheASCII(joueur2->getNom());
}

int AfficheChoixCarteNavigable(Joueur* joueur, int choixCarte) {
    int nbCartes = joueur->getMain().size();
    if (nbCartes == 0) {
        std::cout << "Vous n'avez aucune carte en main." << std::endl;
        return -1;
    }
    if (choixCarte < 0 || choixCarte >= nbCartes) choixCarte = 0;
    while (true) {
        std::cout << "\r" << joueur->getNom() << u8", choisissez une carte à jouer parmi : ";
        for (int i = 0; i < nbCartes; ++i) {
            if (i == choixCarte) std::cout << "[";
            else std::cout << " ";
            AfficheCarte(joueur->getMain()[i].get());
            if (i == choixCarte) std::cout << "]";
            else std::cout << " ";
        }
        std::cout << u8" (Flèches gauche/droite, Entrée pour valider)   " << std::flush;
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 75)      choixCarte = (choixCarte - 1 + nbCartes) % nbCartes;
            else if (key == 77) choixCarte = (choixCarte + 1) % nbCartes;
        }
        else if (key == 13) break;
    }
    std::cout << std::endl;
    return choixCarte + 1;
}

int AfficheChoixBorneNavigable(Joueur* joueur, int choixBorne, const std::vector<Borne>& bornesLibres, int numJoueur) {
    int nbBornesLibres = bornesLibres.size();
    if (nbBornesLibres == 0) {
        std::cout << "Aucune borne disponible." << std::endl;
        return -1;
    }
    choixBorne = nbBornesLibres / 2;
    while (true) {
        std::cout << "\r" << joueur->getNom() << ", veuillez choisir une borne parmi : ";
        for (int i = 0; i < nbBornesLibres; ++i) {
            if (i == choixBorne)
                std::cout << "[" << bornesLibres[i].getnumero() << "]";
            else
                std::cout << " " << bornesLibres[i].getnumero() << " ";
        }
        std::cout << u8" (Flèches gauche/droite, Entrée pour valider)   " << std::flush;
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 75)      choixBorne = (choixBorne - 1 + nbBornesLibres) % nbBornesLibres;
            else if (key == 77) choixBorne = (choixBorne + 1) % nbBornesLibres;
        }
        else if (key == 13) {
            if (numJoueur == 1) {
                if (bornesLibres[choixBorne].getCarteJ1().size() < 3) break;
                else std::cout << u8"\n\033[31mVous avez déjà 3 cartes sur cette borne, veuillez en choisir une autre\033[0m\n";
            }
            else {
                if (bornesLibres[choixBorne].getCarteJ2().size() < 3) break;
                else std::cout << u8"\n\033[31mErreur : Vous avez déjà 3 cartes sur cette borne, veuillez en choisir une autre\033[0m\n";
            }
        }
    }
    std::cout << std::endl;
    return bornesLibres[choixBorne].getnumero();
}

// Autres fonctions à migrer sur le même modèle... 
// Notamment AfficherBornesPlusAJ, AfficherBornes, TrierMain, AfficherReady, etc.
// Utiliser const std::vector<std::shared_ptr<Carte>>& pour les mains, et accès via .get()

// Exemple : AfficherBornesPlusAJ (affichage simplifié)
void AfficherBornesPlusAJ(const std::vector<Borne>& bornes, const std::vector<std::shared_ptr<Carte>>& main1, const std::vector<std::shared_ptr<Carte>>& main2) {
    // Affiche 3 lignes pour chaque main
    for (unsigned int uiLigneDeCartes = 0; uiLigneDeCartes < 3; uiLigneDeCartes++) {
        for (unsigned int i = 0; i < bornes.size(); ++i) {
            const auto& cartesJ1 = bornes[i].getCarteJ1();
            if (cartesJ1.size() <= uiLigneDeCartes) std::cout << "     0    ";
            else { std::cout << "     "; AfficheCarte(cartesJ1[uiLigneDeCartes].get()); std::cout << "    "; }
        }
        std::cout << "\n";
    }
    // Affichage bornes
    for (unsigned int i = 0; i < bornes.size(); ++i) {
        std::cout << "| Borne " << bornes[i].getnumero() << " ";
    }
    std::cout << "|" << std::endl;
    for (unsigned int uiLigneDeCartes = 0; uiLigneDeCartes < 3; uiLigneDeCartes++) {
        for (unsigned int i = 0; i < bornes.size(); ++i) {
            const auto& cartesJ2 = bornes[i].getCarteJ2();
            if (cartesJ2.size() <= uiLigneDeCartes) std::cout << "     0    ";
            else { std::cout << "     "; AfficheCarte(cartesJ2[uiLigneDeCartes].get()); std::cout << "    "; }
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

// ... Migrer les autres fonctions sur le même modèle si besoin