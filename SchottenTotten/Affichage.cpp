#include "Affichage.h"
#include "Borne.h"
#include "Carte.h"
#include <algorithm>
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

void AfficheASCIIPlusAJ(const std::string& texte) {
    std::vector<std::string> aideDeJeuHeader = {
        "\033[33m-----------------------\033[0m",
        "\033[33m|\033[0m     Aide de jeu     \033[33m|\033[0m",
        "\033[33m-----------------------\033[0m",
        "\033[33m-----------------------\033[0m",
      u8"\033[33m|\033[0mSuite colorée : \033[94m3 4 5\033[33m|\033[0m",
        "\033[33m-----------------------\033[0m"
    };
    int iLigneAideAffichee = 0;

    std::ostringstream oss;
    Figlet::standard.print(texte.c_str(), oss);
    std::istringstream iss(oss.str());
    std::string line;
    while (std::getline(iss, line)) {
        if (getTailleTexteASCII(texte) % 2 == 0) {
            std::cout << std::string(45 - (getTailleTexteASCII(texte) / 2), ' ') << "\033[31m" << line << std::string(49 - (getTailleTexteASCII(texte) / 2), ' ') << aideDeJeuHeader[iLigneAideAffichee] << std::endl;
        }
        else {
            std::cout << std::string(45 - (getTailleTexteASCII(texte) / 2), ' ') << "\033[31m" << line << std::string(48 - (getTailleTexteASCII(texte) / 2), ' ') << aideDeJeuHeader[iLigneAideAffichee] << std::endl;
        }
        if (iLigneAideAffichee < 5) {
            iLigneAideAffichee++;
        }
    }
}

void AfficheASCII(const std::string& texte) {
    std::ostringstream oss;
    Figlet::standard.print(texte.c_str(), oss);
    std::istringstream iss(oss.str());
    std::string line;
    while (std::getline(iss, line)) {
        std::cout << std::string(45 - (getTailleTexteASCII(texte) / 2), ' ') << "\033[36m" << line << "\033[0m" << std::endl;
    }
}

void AffichePlateau(const std::vector<Borne>& bornes, Joueur* joueur1, Joueur* joueur2) {
    AfficheASCIIPlusAJ(joueur1->getNom());
    AfficherBornesRevendiqueesPlusAJ(joueur1);
    AfficherBornesPlusAJ(bornes, joueur1->getMain(), joueur2->getMain());
    AfficherBornesRevendiquees(joueur2);
    AfficheASCII(joueur2->getNom());
}

void AfficheCarte(const std::shared_ptr<Carte>& carte) {
    if (!carte) {
        std::cout << " ";
        return;
    }

    switch (CouleurToEnum(carte->getCouleur())) {
    case BLEU:
        std::cout << "\033[94m" << carte->getNumero() << "\033[0m";
        break;
    case VERT:
        std::cout << "\033[32m" << carte->getNumero() << "\033[0m";
        break;
    case JAUNE:
        std::cout << "\033[38;2;255;255;85m" << carte->getNumero() << "\033[0m";
        break;
    case ROUGE:
        std::cout << "\033[31m" << carte->getNumero() << "\033[0m";
        break;
    case VIOLET:
        std::cout << "\033[38;2;199;0;255m" << carte->getNumero() << "\033[0m";
        break;
    case ORANGE:
        std::cout << "\033[38;5;208m" << carte->getNumero() << "\033[0m";
        break;
    default:
        std::cout << carte->getNumero();
        break;
    }
}


int AfficheChoixCarteNavigable(Joueur* joueur, int choixCarte) {
    int nbCartes = joueur->getMain().size();
    if (nbCartes == 0) {
        std::cout << "Vous n'avez aucune carte en main." << std::endl;
        return -1;
    }
    // S'assurer que l'index initial est correct
    if (choixCarte < 0 || choixCarte >= nbCartes) {
        choixCarte = 0;
    }

    while (true) {
        // Affichage dynamique
        std::cout << "\r" << joueur->getNom() << u8", choisissez une carte à jouer parmi : ";
        for (int i = 0; i < nbCartes; ++i) {
            if (i == choixCarte) {
                std::cout << "[";
                AfficheCarte(joueur->getMain()[i]);
                std::cout << "]";
            }
            else {
                std::cout << " ";
                AfficheCarte(joueur->getMain()[i]);
                std::cout << " ";
            }
        }
        std::cout << u8" (Flèches gauche/droite, Entrée pour valider)   " << std::flush;

        int key = _getch();
        if (key == 224) { // Touche spéciale (flèche)
            key = _getch();
            if (key == 75) { // Flèche gauche
                choixCarte = (choixCarte - 1 + nbCartes) % nbCartes;
            }
            else if (key == 77) { // Flèche droite
                choixCarte = (choixCarte + 1) % nbCartes;
            }
        }
        else if (key == 13) { // Entrée
            break;
        }
    }
    std::cout << std::endl;
    // On retourne l'index (1-based) pour correspondre à l'affichage utilisateur
    return choixCarte + 1;
}

// Ajoute un paramètre const Borne& borneActuelle
int AfficheChoixBorneNavigable(Joueur* joueur, int choixBorne, const std::vector<Borne>& bornesLibres, int numJoueur) {
    int nbBornesLibres = bornesLibres.size();
    if (nbBornesLibres == 0) {
        std::cout << "Aucune borne disponible." << std::endl;
        return -1;
    }

    choixBorne = bornesLibres.size() / 2;
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
            if (key == 75) { // gauche
                choixBorne = (choixBorne - 1 + nbBornesLibres) % nbBornesLibres;
            }
            else if (key == 77) { // droite
                choixBorne = (choixBorne + 1) % nbBornesLibres;
            }
        }
        else if (key == 13) { // entrée
            const Borne& selectedBorne = bornesLibres[choixBorne];
            int limiteCartes = selectedBorne.isCombatDeBoue() ? 4 : 3;

            if (numJoueur == 1) {
                if (selectedBorne.getCarteJ1().size() < limiteCartes) {
                    break;
                }
                else {
                    std::cout << u8"\n\033[31mVous avez déjà " << limiteCartes << " cartes sur cette borne, veuillez en choisir une autre\033[0m\n";
                }
            }
            else {
                if (selectedBorne.getCarteJ2().size() < limiteCartes) {
                    break;
                }
                else {
                    std::cout << u8"\n\033[31mErreur : Vous avez déjà " << limiteCartes << " cartes sur cette borne, veuillez en choisir une autre\033[0m\n";
                }
            }
        }
    }
    std::cout << std::endl;
    return bornesLibres[choixBorne].getnumero();
}


int AfficheChoixBorneRevendique(Joueur* joueur, int choixBorneRevendique, std::vector<Borne> bornes, int numJoueur) {
    std::vector<std::string> ListeChoix = { "Non","Oui" };
    int choixOuiNon = 0;
    while (true) {
        // Affichage dynamique
        std::cout << "\r" << joueur->getNom() << u8", voulez-vous revendiquer une borne ? ";
        for (int i = 0; i < 2; ++i) {
            if (i == choixOuiNon) {
                std::cout << "[" << ListeChoix[i] << "]";
            }
            else {
                std::cout << " " << ListeChoix[i] << " ";
            }
        }
        std::cout << u8" (Flèches gauche/droite, Entrée pour valider)   " << std::flush;

        int key = _getch();
        if (key == 224) { // Touche spéciale (flèche)
            key = _getch();
            if (key == 75 || key == 77) { // Flèche 
                choixOuiNon = (choixOuiNon + 1) % 2;
            }
        }
        else if (key == 13) { // Entrée
            if (choixOuiNon == 0) {
                return 0;
            }
            else {
                break;
            }
        }
    }

    int choixBorne = 0;
    while (true) {
        std::cout << "\r" << joueur->getNom() << u8", quelle borne voulez vous revendiquer ? ";
        for (int i = 0; i < bornes.size(); ++i) {
            if (i == choixBorne) {
                std::cout << "[" << bornes[i].getnumero() << "]";
            }
            else {
                std::cout << " " << bornes[i].getnumero() << " ";
            }
        }
        if (choixBorne == bornes.size()) {
            std::cout << "[X]";
        }
        else {
            std::cout << " X ";
        }
        std::cout << u8" (X pour annuler / Flèches pour naviguer)" << std::flush;

        int key = _getch();
        if (key == 224) { // Touche spéciale (flèche)
            key = _getch();
            if (key == 75) { // Flèche gauche
                choixBorne = (choixBorne + bornes.size()) % (bornes.size() + 1);
            }
            else if (key == 77) { // Flèche droite
                choixBorne = (choixBorne + 1) % (bornes.size() + 1);
            }
        }
        else if (key == 13) { // Entrée
            choixBorne++;
            if (choixBorne > bornes.size()) {
                return 0;
            }
            if (numJoueur == 1) {
                if (bornes[choixBorne - 1].getGagnant() == NULL && bornes[choixBorne - 1].getCarteJ1().size() == 3) {
                    return bornes[choixBorne - 1].getnumero();
                }
                else if (bornes[choixBorne - 1].getGagnant() == NULL) {
                    std::cout << u8"\n\033[31mErreur : \033[0mVous ne pouvez pas revendiquer la borne " << bornes[choixBorne - 1].getnumero() << u8" car vous n'avez pas assez de cartes sur la borne.\n";
                }
                else {
                    std::cout << u8"\n\033[31mErreur : \033[0mLa borne " << bornes[choixBorne - 1].getnumero() << u8" a déjà un gagnant.\n";
                }
            }
            if (numJoueur == 2) {
                if (bornes[choixBorne - 1].getGagnant() == NULL && bornes[choixBorne - 1].getCarteJ2().size() == 3) {
                    return bornes[choixBorne - 1].getnumero();
                }
                else if (bornes[choixBorne - 1].getGagnant() == NULL) {
                    std::cout << u8"\n\033[31mErreur : \033[0mVous ne pouvez pas revendiquer la borne " << bornes[choixBorne - 1].getnumero() << u8" car vous n'avez pas assez de cartes sur la borne.\n";
                }
                else {
                    std::cout << u8"\n\033[31mErreur : \033[0mLa borne " << bornes[choixBorne - 1].getnumero() << u8" a déjà un gagnant. \n";
                }
            }
        }
    }
}

void AfficherBornesRevendiqueesPlusAJ(Joueur* joueur) {
    std::string aideDeJeuBrelan = "\033[33m|\033[0m    Brelan : \033[32m6 \033[94m6 \033[31m6   \033[33m|\033[0m";
    int numeroDerniereBornePossedee = 0;
    if (joueur->getBorne().size() != 0) {
        std::string check = u8"✅";

        for (unsigned int uiIndex = 0; uiIndex < joueur->getBorne().size(); uiIndex++) {
            if (joueur->getBorne()[uiIndex].getnumero() == 1) {
                std::cout << std::string(5, ' ') << check;
            }
            else if (joueur->getBorne()[uiIndex].getnumero() != 1 && uiIndex == 0) {
                std::cout << std::string(5 + (joueur->getBorne()[uiIndex].getnumero() - 1) * 10, ' ') << check;
            }
            else if (joueur->getBorne()[uiIndex].getnumero() - joueur->getBorne()[uiIndex - 1].getnumero() == 1) {
                std::cout << std::string(((joueur->getBorne()[uiIndex].getnumero() - joueur->getBorne()[uiIndex - 1].getnumero()) * 8), ' ') << check;
            }
            else {
                std::cout << std::string((joueur->getBorne()[uiIndex].getnumero() - joueur->getBorne()[uiIndex - 1].getnumero() - 1) * 10 + 8, ' ') << check;
            }
            numeroDerniereBornePossedee = joueur->getBorne()[uiIndex].getnumero();
        }
        std::cout << std::string(7 + (9 - numeroDerniereBornePossedee) * 10, ' ') << aideDeJeuBrelan;
    }
    else {
        std::cout << std::string(94, ' ') << aideDeJeuBrelan;
    }
    std::cout << "\n";
}

void AfficherBornesRevendiquees(Joueur* joueur) {
    if (joueur->getBorne().size() != 0) {
        std::string check = u8"✅";

        for (unsigned int uiIndex = 0; uiIndex < joueur->getBorne().size(); uiIndex++) {
            if (joueur->getBorne()[uiIndex].getnumero() == 1) {
                std::cout << std::string(5, ' ') << check;
            }
            else if (joueur->getBorne()[uiIndex].getnumero() != 1 && uiIndex == 0) {
                std::cout << std::string(5 + (joueur->getBorne()[uiIndex].getnumero() - 1) * 10, ' ') << check;
            }
            else if (joueur->getBorne()[uiIndex].getnumero() - joueur->getBorne()[uiIndex - 1].getnumero() == 1) {
                std::cout << std::string(((joueur->getBorne()[uiIndex].getnumero() - joueur->getBorne()[uiIndex - 1].getnumero()) * 8), ' ') << check;
            }
            else {
                std::cout << std::string((joueur->getBorne()[uiIndex].getnumero() - joueur->getBorne()[uiIndex - 1].getnumero() - 1) * 10 + 8, ' ') << check;
            }
        }
        std::cout << "\n";
    }
}
//TO DO
void AfficherBornesPlusAJ(const std::vector<Borne>& bornes,const std::vector<std::shared_ptr<Carte>>& main1,const std::vector<std::shared_ptr<Carte>>& main2)
{
    std::vector<std::string> aideDeJeuSuite = {
        "\033[33m-----------------------\033[0m",
        "\033[33m|\033[0m   Couleur : \033[38;2;199;0;255m1 3 6   \033[33m|\033[0m",
        "\033[33m-----------------------\033[0m",
        "\033[33m|\033[0m    Suite : \033[38;5;208m2 \033[32m3 \033[38;2;199;0;255m4    \033[33m|\033[0m",
        "\033[33m-----------------------\033[0m",
        "\033[33m|\033[0m    Somme : \033[38;5;208m3 \033[94m7 \033[38;2;199;0;255m9    \033[33m|\033[0m",
        "\033[33m-----------------------\033[0m"
    };

    int iLigneAideAffichee = 0;

    // Affichage cartes joueur 1 (3 lignes)
    for (unsigned int uiLigneDeCartes = 0; uiLigneDeCartes < 3; uiLigneDeCartes++) {
        for (unsigned int i = 0; i < bornes.size(); ++i) {
            const std::vector<std::shared_ptr<Carte>>& cartesJ1 = bornes[i].getCarteJ1();
            if (cartesJ1.size() <= uiLigneDeCartes) {
                std::cout << "     0    ";  // pas de carte => afficher 0
            }
            else {
                std::cout << "     ";
                AfficheCarte(cartesJ1[uiLigneDeCartes]);
                std::cout << "    ";
            }
        }
        // Affiche ligne aide de jeu
        if (iLigneAideAffichee < (int)aideDeJeuSuite.size()) {
            std::cout << std::string(4, ' ') << aideDeJeuSuite[iLigneAideAffichee++];
        }
        std::cout << "\n";
    }

    // Ligne séparatrice
    std::cout << " -----------------------------------------------------------------------------------------"
        << std::string(4, ' ') << (iLigneAideAffichee < (int)aideDeJeuSuite.size() ? aideDeJeuSuite[iLigneAideAffichee++] : "")
        << std::endl;

    // Affichage numéro des bornes
    for (unsigned int i = 0; i < bornes.size(); ++i) {
        std::cout << "| Borne " << bornes[i].getnumero() << " ";
    }
    std::cout << "|" << std::string(3, ' ');
    if (iLigneAideAffichee < (int)aideDeJeuSuite.size()) {
        std::cout << aideDeJeuSuite[iLigneAideAffichee++];
    }
    std::cout << std::endl;

    // Ligne séparatrice
    std::cout << " -----------------------------------------------------------------------------------------"
        << std::string(4, ' ') << (iLigneAideAffichee < (int)aideDeJeuSuite.size() ? aideDeJeuSuite[iLigneAideAffichee++] : "")
        << std::endl;

    // Affichage cartes joueur 2 (3 lignes)
    for (unsigned int uiLigneDeCartes = 0; uiLigneDeCartes < 3; uiLigneDeCartes++) {
        for (unsigned int i = 0; i < bornes.size(); ++i) {
            const std::vector<std::shared_ptr<Carte>>& cartesJ2 = bornes[i].getCarteJ2();
            if (cartesJ2.size() <= uiLigneDeCartes) {
                std::cout << "     0    ";  // pas de carte => afficher 0
            }
            else {
                std::cout << "     ";
                AfficheCarte(cartesJ2[uiLigneDeCartes]);
                std::cout << "    ";
            }
        }
        if (iLigneAideAffichee < (int)aideDeJeuSuite.size()) {
            std::cout << std::string(4, ' ') << aideDeJeuSuite[iLigneAideAffichee++];
        }
        std::cout << "\n";
    }
}


void AfficherReady() {
    std::cout << u8"\nAppuyez sur Entrée si vous êtes prêt à voir votre main : ";
    int key;
    while (true) {
        key = _getch();
        if (key == 13) { // 13 = Entrée
            break;
        }
        else {
            std::cout << u8"\nEntrée invalide. Appuyez sur Entrée pour continuer : ";
        }
    }
}

void TrierMain(Joueur* joueur) {
    auto& main = joueur->getMain();  // référence modifiable à vector<shared_ptr<Carte>>
    std::sort(
        main.begin(), main.end(),
        [](const std::shared_ptr<Carte>& a, const std::shared_ptr<Carte>& b) {
            if (a->getCouleur() != b->getCouleur())
                return a->getCouleur() < b->getCouleur();
            return a->getNumero() < b->getNumero();
        }
    );
}

void AfficherBorneGagnee(Joueur* joueur1, Borne borne) {
    std::string message = "Borne " + std::to_string(borne.getnumero()) + " :";
    AfficheASCII(message);
    AfficheASCII(joueur1->getNom());

    std::this_thread::sleep_for(std::chrono::seconds(3));
}

bool AfficherVictoire(std::vector<Borne> bornes, Joueur* joueur1, Joueur* joueur2) {
    bool bFinDePartie = 0;
    if (joueur1->getBorne().size() == 5) {
        clearConsole();
        AffichePlateau(bornes, joueur1, joueur2);
        std::cout << u8"\nLa partie est gagnée par 👑 " << joueur1->getNom() << u8" 👑 qui a revendiqué 5 bornes !" << std::endl;
        bFinDePartie = 1;
    }
    else if (joueur2->getBorne().size() == 5) {
        clearConsole();
        AffichePlateau(bornes, joueur1, joueur2);
        std::cout << u8"\nLa partie est gagnée par 👑 " << joueur2->getNom() << u8" 👑 qui a revendiqué 5 bornes !" << std::endl;
        bFinDePartie = 1;
    }
    else if (joueur2->EstGagnant()) {
        clearConsole();
        AffichePlateau(bornes, joueur1, joueur2);
        std::cout << u8"\nLa partie est gagnée par 👑 " << joueur2->getNom() << u8" 👑 qui a revendiqué 3 bornes côte à côte !" << std::endl;
        bFinDePartie = 1;
    }
    else if (joueur1->EstGagnant()) {
        clearConsole();
        AffichePlateau(bornes, joueur1, joueur2);
        std::cout << u8"\nLa partie est gagnée par 👑 " << joueur1->getNom() << u8" 👑 qui a revendiqué 3 bornes côte à côte !" << std::endl;
        bFinDePartie = 1;
    }

    return bFinDePartie;
}



void AfficheBanniereAnim() {
    SetConsoleOutputCP(CP_UTF8);

    std::vector<std::wstring> lignes = {
        L"  ██████  ██░ ██  ▒█████  ▄▄▄█████▓▄▄▄█████▓▓█████  ███▄    █ ▄▄▄█████▓ ▒█████  ▄▄▄█████▓▄▄▄█████▓▓█████  ███▄    █ ",
        L"▒██    ▒ ▓██░ ██▒▒██▒  ██▒▓  ██▒ ▓▒▓  ██▒ ▓▒▓█   ▀  ██ ▀█   █ ▓  ██▒ ▓▒▒██▒  ██▒▓  ██▒ ▓▒▓  ██▒ ▓▒▓█   ▀  ██ ▀█   █ ",
        L"░ ▓██▄   ▒██▀▀██░▒██░  ██▒▒ ▓██░ ▒░▒ ▓██░ ▒░▒███   ▓██  ▀█ ██▒▒ ▓██░ ▒░▒██░  ██▒▒ ▓██░ ▒░▒ ▓██░ ▒░▒███   ▓██  ▀█ ██▒",
        L"  ▒   ██▒░▓█ ░██ ▒██   ██░░ ▓██▓ ░ ░ ▓██▓ ░ ▒▓█  ▄ ▓██▒  ▐▌██▒░ ▓██▓ ░ ▒██   ██░░ ▓██▓ ░ ░ ▓██▓ ░ ▒▓█  ▄ ▓██▒  ▐▌██▒",
        L"▒██████▒▒░▓█▒░██▓░ ████▓▒░  ▒██▒ ░   ▒██▒ ░ ░▒████▒▒██░   ▓██░  ▒██▒ ░ ░ ████▓▒░  ▒██▒ ░   ▒██▒ ░ ░▒████▒▒██░   ▓██░",
        L"▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░ ▒░▒░▒░   ▒ ░░     ▒ ░░   ░░ ▒░ ░░ ▒░   ▒ ▒   ▒ ░░   ░ ▒░▒░▒░   ▒ ░░     ▒ ░░   ░░ ▒░ ░░ ▒░   ▒ ▒ ",
        L"░ ░▒  ░ ░ ▒ ░▒░ ░  ░ ▒ ▒░     ░        ░     ░ ░  ░░ ░░   ░ ▒░    ░      ░ ▒ ▒░     ░        ░     ░ ░  ░░ ░░   ░ ▒░",
        L"░  ░  ░   ░  ░░ ░░ ░ ░ ▒    ░        ░         ░      ░   ░ ░   ░      ░ ░ ░ ▒    ░        ░         ░      ░   ░ ░ ",
        L"      ░   ░  ░  ░    ░ ░                       ░  ░         ░              ░ ░                       ░  ░         ░ "
    };

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    int nb_lignes = static_cast<int>(lignes.size());
    std::vector<int> lens;
    int max_len = 0;
    for (size_t i = 0; i < lignes.size(); ++i) {
        lens.push_back(static_cast<int>(lignes[i].length()));
        if (lignes[i].length() > max_len) max_len = static_cast<int>(lignes[i].length());
    }

    std::vector<std::vector<bool> > rouge(nb_lignes, std::vector<bool>(max_len, false));
    std::vector<std::pair<int, int> > ordre;

    for (int r = 0; r < nb_lignes; ++r) {
        if (r % 2 == 0) {
            for (int c = 0; c < lens[r]; ++c)
                ordre.push_back(std::make_pair(r, c));
        }
        else {
            for (int c = lens[r] - 1; c >= 0; --c)
                ordre.push_back(std::make_pair(r, c));
        }
    }

    // Affiche toute la bannière en blanc une seule fois
    for (size_t i = 0; i < lignes.size(); ++i) {
        std::cout << converter.to_bytes(lignes[i]) << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(700));

    // Animation : mise à jour uniquement de la ligne modifiée
    for (size_t i = 0; i < ordre.size(); ++i) {
        int r = ordre[i].first;
        int c = ordre[i].second;
        rouge[r][c] = true;

        // Remonte le curseur sur la ligne à modifier
        if (nb_lignes - r > 0)
            std::cout << "\033[" << (nb_lignes - r) << "A";

        // Réaffiche la ligne courante avec les cases rouges
        for (int col = 0; col < lens[r]; ++col) {
            if (rouge[r][col])
                std::cout << "\033[31m" << converter.to_bytes(std::wstring(1, lignes[r][col])) << "\033[0m";
            else
                std::cout << converter.to_bytes(std::wstring(1, lignes[r][col]));
        }
        std::cout << std::endl;

        // Redescend le curseur à la fin
        if (nb_lignes - r - 1 > 0)
            std::cout << "\033[" << (nb_lignes - r - 1) << "B";

        std::this_thread::sleep_for(std::chrono::milliseconds(0));
    }

    // À la fin, tout en rouge
    if (nb_lignes > 0)
        std::cout << "\033[" << nb_lignes << "A";
    for (size_t i = 0; i < lignes.size(); ++i) {
        std::cout << "\033[31m" << converter.to_bytes(lignes[i]) << "\033[0m" << std::endl;
    }
}

void clearConsole() {
#if defined(_WIN32)
    system("cls");
#else
    system("clear");
#endif
}