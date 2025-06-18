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

void AfficherBorneGagnee(Joueur* joueur1, Borne borne) {
    std::string message = "Borne " + std::to_string(borne.getnumero()) + " :";
    AfficheASCII(message);
    AfficheASCII(joueur1->getNom());

    std::this_thread::sleep_for(std::chrono::seconds(3));
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

// Autres fonctions à migrer sur le même modèle... 
// Notamment AfficherBornesPlusAJ, AfficherBornes, TrierMain, AfficherReady, etc.
// Utiliser const std::vector<std::shared_ptr<Carte>>& pour les mains, et accès via .get()


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