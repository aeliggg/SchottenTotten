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
        std::cout << std::string(45-(getTailleTexteASCII(texte)/2), ' ') << "\033[36m" << line << "\033[0m" << endl;
    }
}

void AffichePlateau(const std::vector<Borne>& bornes,Joueur*joueur1, Joueur*joueur2 ) {
    AfficheASCIIPlusAJ(joueur1->getNom());
    AfficherBornesRevendiqueesPlusAJ(joueur1);
    AfficherBornesPlusAJ(bornes, joueur1->getMain(), joueur2->getMain());
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

int AfficheChoixCarte(Joueur* joueur, int choixCarte) {
    std::cout << joueur->getNom() << u8", entrez l'index de la carte à jouer (1 à " << joueur->getMain().size() << ") : ";
    while (!(std::cin >> choixCarte) || choixCarte < 1 || choixCarte >(int)joueur->getMain().size()) {
        std::cin.clear();
        std::string dummy;
        std::getline(std::cin, dummy);
        std::cout << "Erreur. Veuillez entrer un nombre entre 1 et " << joueur->getMain().size() << " : ";
    }
    return choixCarte;
}


int AfficheChoixBorne(Joueur* joueur, int choixBorne, std::vector<Borne> bornes, int numJoueur) {
    std::cout << joueur->getNom() << u8", entrez l'index de la borne où placer la carte (1 à 9) : ";

    while (true) {
        while (!(std::cin >> choixBorne) || choixBorne < 1 || choixBorne > 9) {
            std::cin.clear();
            std::string dummy;
            std::getline(std::cin, dummy);
            std::cout << "Erreur. Veuillez entrer un nombre entre 1 et 9 : ";
        }
        if (numJoueur == 1) {
            if (bornes[choixBorne - 1].getCarteJ1().size() < 3) {
                break;
            }
            else {
                std::cout << u8"Erreur : La borne " << choixBorne << u8" a déjà 3 cartes. Choisissez une autre borne : ";
            }
        }
        else {
            if (bornes[choixBorne - 1].getCarteJ2().size() < 3) {
                break;
            }
            else {
                std::cout << u8"Erreur : La borne " << choixBorne << u8" a déjà 3 cartes. Choisissez une autre borne : ";
            }
        }
    }
    return choixBorne;
}

void AfficherBornesRevendiqueesPlusAJ(Joueur* joueur) {
    std::string aideDeJeuBrelan = "\033[33m|\033[0m    Brelan : \033[32m6 \033[94m6 \033[31m6   \033[33m|\033[0m";
    int numeroDerniereBornePossedee = 0;
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
            numeroDerniereBornePossedee = joueur->getBorne()[uiIndex].getnumero();
        }
        std::cout << std::string(7 + (9-numeroDerniereBornePossedee)*10, ' ') << aideDeJeuBrelan;
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

void AfficherBornesPlusAJ(const std::vector<Borne>& bornes, const std::vector<Cartes>& main1, const std::vector<Cartes>& main2) {
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


    for (unsigned int uiLigneDeCartes = 0; uiLigneDeCartes < 3; uiLigneDeCartes++) {
        for (unsigned int i = 0; i < bornes.size(); ++i) {
            std::vector<Cartes> cartesJ1 = bornes[i].getCarteJ1();
            if (cartesJ1.size() <= uiLigneDeCartes) {
                std::cout << "     0    ";
            }
            else {
                std::cout << "     ";
                AfficheCarte(cartesJ1[uiLigneDeCartes]);
                std::cout << "   ";
            }
        }
        std::cout << std::string(4, ' ') << aideDeJeuSuite[iLigneAideAffichee++];
        if (uiLigneDeCartes != 2) {
            std::cout << "\n";
        }
    }
    std::cout << "\n -----------------------------------------------------------------------------------------" << std::string(4, ' ') << aideDeJeuSuite[iLigneAideAffichee++] << std::endl;
    for (unsigned int i = 0; i < bornes.size(); ++i) {
        std::cout << "| Borne " << bornes[i].getnumero() << " ";
    }
    std::cout << "|" << std::string(3, ' ') << aideDeJeuSuite[iLigneAideAffichee++] << std::endl;
    std::cout << " -----------------------------------------------------------------------------------------" << std::string(4, ' ') << aideDeJeuSuite[iLigneAideAffichee++] << std::endl;
    for (unsigned int uiLigneDeCartes = 0; uiLigneDeCartes < 3; uiLigneDeCartes++) {
        for (unsigned int i = 0; i < bornes.size(); ++i) {
            std::vector<Cartes> cartesJ2 = bornes[i].getCarteJ2();
            if (cartesJ2.size() <= uiLigneDeCartes) {
                std::cout << "     0    ";
            }
            else {
                std::cout << "     ";
                AfficheCarte(cartesJ2[uiLigneDeCartes]);
                std::cout << "   ";
            }
        }
        if (iLigneAideAffichee < 7) {
            std::cout << std::string(4, ' ') << aideDeJeuSuite[iLigneAideAffichee++];
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

bool AfficherVictoire(std::vector<Borne> bornes, Joueur* joueur1, Joueur* joueur2) {
    bool bFinDePartie = 0;
    if (joueur1->getBorne().size() == 5) {
        clearConsole();
        AffichePlateau(bornes,joueur1,joueur2);
        std::cout << u8"\nLa partie est gagnée par 👑 " << joueur1->getNom() << u8" 👑 qui a revendiqué 5 bornes !" << endl;
        bFinDePartie=1;
    }
    else if (joueur2->getBorne().size() == 5) {
        clearConsole();
        AffichePlateau(bornes, joueur1, joueur2);
        std::cout << u8"\nLa partie est gagnée par 👑 " << joueur2->getNom() << u8" 👑 qui a revendiqué 5 bornes !" << endl;
        bFinDePartie = 1;
    }
    else if (joueur2->EstGagnant()) {
        clearConsole();
        AffichePlateau(bornes, joueur1, joueur2);
        std::cout << u8"\nLa partie est gagnée par 👑 " << joueur2->getNom() << u8" 👑 qui a revendiqué 3 bornes côte à côte !" << endl;
        bFinDePartie = 1;
    }
    else if (joueur1->EstGagnant()) {
        clearConsole();
        AffichePlateau(bornes, joueur1, joueur2);
        std::cout << u8"\nLa partie est gagnée par 👑 " << joueur1->getNom() << u8" 👑 qui a revendiqué 3 bornes côte à côte !" << endl;
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