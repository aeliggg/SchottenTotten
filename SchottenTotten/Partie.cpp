#include "Partie.h"
#include "Affichage.h"
#include <limits>
Partie::Partie(){
    std::vector<std::string> couleurs = { "rouge", "bleu", "vert", "jaune", "violet", "orange" };

    for (unsigned int uiIndexCouleur = 0; uiIndexCouleur < couleurs.size(); ++uiIndexCouleur) {
        for (unsigned int uiIndexNumero = 1; uiIndexNumero <= 9; ++uiIndexNumero) {
            Cartes carte(uiIndexNumero, couleurs[uiIndexCouleur]);
            ajouterCarte(carte);
        }
    }
    for (int i = 0; i < 9; ++i) {
        Borne borne(i + 1);
        borne.setpartie(this);
        bornes.push_back(borne);
    }
}

Partie::Partie(Joueur* j1, Joueur* j2): joueur1(j1), joueur2(j2) {
    std::vector<std::string> couleurs = { "rouge", "bleu", "vert", "jaune", "violet", "orange" };

    for (unsigned int uiIndexCouleur = 0; uiIndexCouleur < couleurs.size(); ++uiIndexCouleur) {
        for (unsigned int uiIndexNumero = 1; uiIndexNumero <= 9; ++uiIndexNumero) {
            Cartes carte(uiIndexNumero, couleurs[uiIndexCouleur]);
            ajouterCarte(carte);
        }
    }
    for (int i = 0; i < 9; ++i) {
        Borne borne(i + 1);
        borne.setpartie(this);
        bornes.push_back(borne);
    }
}

void Partie::ajouterCarte(const Cartes& carte) {
    cartes.push_back(carte);
}

void Partie::ajouterBorne(const Borne& borne) {
    bornes.push_back(borne);
}


std::vector<Cartes> Partie::getCartes() {
    return cartes;
}

std::vector<Borne> Partie::getBornes() {
    return bornes;
}

Joueur* Partie::getJoueur1() {
    return joueur1;
}

Joueur* Partie::getJoueur2() {
    return joueur2;
}

#include "Partie.h"
#include "Borne.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

void Partie::jouer() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::shuffle(cartes.begin(), cartes.end(), std::default_random_engine(std::rand()));

    for (int i = 0; i < 6; ++i) {
        joueur1->ajouterCarte(cartes.back());
        cartes.pop_back();
        joueur2->ajouterCarte(cartes.back());
        cartes.pop_back();
    }

    std::cout << "Debut de la partie entre " << joueur1->getNom() << " et " << joueur2->getNom() << " !\n";
    for (int tour = 0; tour < 2; ++tour) {
        std::cout << "\n--- Tour " << tour + 1 << " ---\n";
        int Tour;
        std::cout << "\nC'est au tour de "<< joueur1->getNom()<<"\n";
        std::cout << "\nEcrire 1 si vous etes pret a voir la main \n";
        while (!(std::cin >> Tour) || Tour != 1) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entree invalide. Veuillez saisir 1 pour continuer : ";
        }

        std::cout << "\n Voici la main de "<<joueur1->getNom()<<" : \n";
        std::vector<Cartes> main1 = joueur1->getMain();
        std::vector<Cartes> main2 = joueur2->getMain();
        std::sort(main1.begin(), main1.end(), [](const Cartes& a, const Cartes& b) {
            if (a.getcouleur() != b.getcouleur())
                return a.getcouleur() < b.getcouleur(); 
            return a.getnumero() < b.getnumero();       
            });
        for (unsigned int uiIndex = 0; uiIndex < main1.size(); ++uiIndex) {
            AfficheCarte(main1[uiIndex]);
        }
        int choixCarte;
        int choixfrontiere;
        std::cout << joueur1->getNom() << ", entrez l'index de la carte a jouer (1 a 6) : ";
        std::cin >> choixCarte;
        while (std::cin.fail() || choixCarte < 1 || choixCarte > 6) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Erreur dans l'index. Veuillez entrer un nombre entre 1 et 6 : ";
            std::cin >> choixCarte;
        }

        std::cout << joueur1->getNom() << ", entrez l'index de la carte frontiere ou vous voulez placer la carte (1 a 9): ";
        AfficherBornes(bornes, main1, main2);
        std::cout << "\n" << joueur1->getNom() << " joue en haut\n";
        std::cout << "\net " << joueur2->getNom() << " joue en bas\n";
        std::cin >> choixfrontiere;
        while (std::cin.fail() || choixfrontiere < 1 || choixfrontiere > 9) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Erreur dans l'index. Veuillez entrer un nombre entre 1 et 9 : ";
            std::cin >> choixfrontiere;
        }

        bornes[choixfrontiere-1].ajouterCarteJ1(joueur1->getMain()[choixCarte-1]);
        joueur1->ajouterCarte(cartes.back());;

        std::cout << "\n--- Tour " << tour + 1 << " ---\n";
        std::cout << "\n C'est au tour de " << joueur2->getNom() << "\n";
        std::cout << "\n Ecrire 1 si vous etes pret a voir la main \n";
        while (!(std::cin >> Tour) || Tour != 1) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entree invalide. Veuillez saisir 1 pour continuer : ";
        }
        std::cout << "\n Voici la main de " << joueur2->getNom() << " : \n";
        std::sort(main2.begin(), main2.end(), [](const Cartes& a, const Cartes& b) {
            if (a.getcouleur() != b.getcouleur())
                return a.getcouleur() < b.getcouleur();
            return a.getnumero() < b.getnumero();
            });
        for (unsigned int uiIndex = 0; uiIndex < main2.size(); ++uiIndex) {
            AfficheCarte(main2[uiIndex]);
        }
        std::cout << joueur2->getNom() << ", entrez l'index de la carte a jouer (1 a 6) : ";
        std::cin >> choixCarte;
        while (choixCarte > 6 || choixCarte < 1) {
            std::cout << "Erreur dans l'index" << endl;
            std::cout << joueur2->getNom() << ", entrez l'index de la carte a jouer (1 a 6): ";
            std::cin >> choixCarte;
        }
        std::cout << joueur2->getNom() << ", entrez l'index de la borne ou vous voulez placer la carte (1 a 9): ";
        AfficherBornes(bornes, main1, main2);
        std::cout << "\n"<<joueur1->getNom() << " joue en haut\n";
        std::cout << "\net " << joueur2->getNom() << " joue en bas\n";
        std::cin >> choixfrontiere;
        while (choixfrontiere > 9 || choixfrontiere < 1) {
            std::cout << "Erreur dans l'index" << endl;
            std::cout << joueur2->getNom() << ", entrez l'index de la borne ou vous voulez placer la carte (1 a 9):  ";
            std::cin >> choixfrontiere;
        }
        bornes[choixfrontiere-1].ajouterCarteJ2(joueur2->getMain()[choixCarte-1]);
        AfficherBornes(bornes, main1, main2);
    }


}

