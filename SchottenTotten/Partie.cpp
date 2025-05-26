#include "Partie.h"

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

    std::cout << "Début de la partie entre " << joueur1->getNom() << " et " << joueur2->getNom() << " !\n";
    for (int tour = 0; tour < 2; ++tour) {
        std::cout << "\n--- Tour " << tour + 1 << " ---\n";
        std::cout << "\n Voici la main de "<<joueur1->getNom()<<" : \n";
        std::vector<Cartes> main1 = joueur1->getMain();
        for (unsigned int uiIndex = 0; uiIndex < main1.size(); ++uiIndex) {
            std::cout << "Carte " << main1[uiIndex].getnumero() << " de couleur " << main1[uiIndex].getcouleur() << std::endl;
        }
        int choixCarte;
        int choixfrontiere;
        std::cout << joueur1->getNom() << ", entrez l'index de la carte a jouer (0 a 5) : ";
        std::cin >> choixCarte;
        while (choixCarte > 5 || choixCarte < 0) {
            std::cout << "Erreur dans l'index" << endl;
            std::cout << joueur1->getNom() << ", entrez l'index de la carte a jouer (0 a 5): ";
            std::cin >> choixCarte;
        }
        std::cout << joueur1->getNom() << ", entrez l'index de la carte frontiere ou vous voulez placer la carte (0 a 8): ";
        std::cin >> choixfrontiere;
        while (choixfrontiere > 8 || choixfrontiere < 0) {
            std::cout << "Erreur dans l'index" << endl;
            std::cout << joueur1->getNom() << ", entrez l'index de la frontiere ou vous voulez placer la carte (0 a 8):  ";
            std::cin >> choixfrontiere;
        }
        bornes[choixfrontiere].ajouterCarteJ1(joueur1->getMain()[choixCarte]);
        joueur1->ajouterCarte(cartes.back());;

        std::cout << "\n--- Tour " << tour + 1 << " ---\n";
        std::cout << "\n Voici la main de " << joueur2->getNom() << " : \n";
        std::vector<Cartes> main2 = joueur2->getMain();
        for (unsigned int uiIndex = 0; uiIndex < main2.size(); ++uiIndex) {
            std::cout << "Carte " << main2[uiIndex].getnumero() << " de couleur " << main2[uiIndex].getcouleur() << std::endl;
        }
        std::cout << joueur2->getNom() << ", entrez l'index de la carte a jouer (0 a 5) : ";
        std::cin >> choixCarte;
        while (choixCarte > 5 || choixCarte < 0) {
            std::cout << "Erreur dans l'index" << endl;
            std::cout << joueur2->getNom() << ", entrez l'index de la carte a jouer (0 a 5): ";
            std::cin >> choixCarte;
        }
        std::cout << joueur2->getNom() << ", entrez l'index de la carte frontiere ou vous voulez placer la carte (0 a 8): ";
        std::cin >> choixfrontiere;
        while (choixfrontiere > 8 || choixfrontiere < 0) {
            std::cout << "Erreur dans l'index" << endl;
            std::cout << joueur2->getNom() << ", entrez l'index de la frontiere ou vous voulez placer la carte (0 a 8):  ";
            std::cin >> choixfrontiere;
        }
        bornes[choixfrontiere].ajouterCarteJ2(joueur2->getMain()[choixCarte]);

        std::cout << "\n=== Résumé des cartes sur les bornes ===\n";
        for (unsigned int i = 0; i < bornes.size(); ++i) {
            std::cout << "\nBorne " << bornes[i].getnumero() << " :\n";

            std::vector<Cartes> cartesJ1 = bornes[i].getCarteJ1();
            std::vector<Cartes> cartesJ2 = bornes[i].getCarteJ2();

            std::cout << "  Cartes de " << joueur1->getNom() << " : ";
            if (cartesJ1.empty()) {
                std::cout << "aucune\n";
            }
            else {
                for (unsigned int j = 0; j < cartesJ1.size(); ++j) {
                    std::cout << "[" << cartesJ1[j].getnumero() << " " << cartesJ1[j].getcouleur() << "] ";
                }
                std::cout << "\n";
            }

            std::cout << "  Cartes de " << joueur2->getNom() << " : ";
            if (cartesJ2.empty()) {
                std::cout << "aucune\n";
            }
            else {
                for (unsigned int j = 0; j < cartesJ2.size(); ++j) {
                    std::cout << "[" << cartesJ2[j].getnumero() << " " << cartesJ2[j].getcouleur() << "] ";
                }
                std::cout << "\n";
            }

    }
    }


}

