#include "Partie.h"
#include "Affichage.h"
#include <limits>
#include <iomanip>   // Pour std::setw
#include <thread>    // Pour sleep_for
#include <chrono>
#include "Borne.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>



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

void Partie::jouer() {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::shuffle(cartes.begin(), cartes.end(), std::default_random_engine(std::rand()));

    for (int i = 0; i < 6; ++i) {
        joueur1->ajouterCarte(cartes.back());
        cartes.pop_back();
        joueur2->ajouterCarte(cartes.back());
        cartes.pop_back();
    }

    std::cout << u8"Début de la partie entre " << joueur1->getNom() << " et " << joueur2->getNom() << " !\n";

    for (int tour = 0; tour < 27; ++tour) {
        if (tour != 0) {
            clearConsole();
        }
        std::cout << "\n--- Tour " << tour + 1 << " ---\n";
        {
            SetConsoleOutputCP(CP_UTF8);
            AfficheASCII(joueur1->getNom());
            AfficherBornesRevendiquees(joueur1);
            AfficherBornes(bornes, joueur1->getMain(), joueur2->getMain());
            AfficherBornesRevendiquees(joueur2);
            AfficheASCII(joueur2->getNom());

            std::cout << "\nC'est au tour de " << joueur1->getNom() << "\n";
 
            int ready = 0;
            ready = AfficherReady(ready);

            std::vector<Cartes> mainJ1 = AfficherMain(joueur1);

            int choixCarte;
            std::cout << joueur1->getNom() << u8", entrez l'index de la carte à jouer (1 à " << mainJ1.size() << ") : ";
            while (!(std::cin >> choixCarte) || choixCarte < 1 || choixCarte >(int)mainJ1.size()) {
                std::cin.clear();
                std::string dummy;
                std::getline(std::cin, dummy);
                std::cout << "Erreur. Veuillez entrer un nombre entre 1 et " << mainJ1.size() << " : ";
            }

            int choixBorne;
            std::cout << joueur1->getNom() << u8", entrez l'index de la borne où placer la carte (1 à 9) : ";

            while (true) {
                while (!(std::cin >> choixBorne) || choixBorne < 1 || choixBorne > 9) {
                    std::cin.clear();
                    std::string dummy;
                    std::getline(std::cin, dummy);
                    std::cout << "Erreur. Veuillez entrer un nombre entre 1 et 9 : ";
                }

                if (bornes[choixBorne - 1].getCarteJ1().size() < 3) {
                    break;
                }
                else {
                    std::cout << u8"Erreur : La borne " << choixBorne << " a déjà 3 cartes. Choisissez une autre borne : ";
                }
            }
            Cartes carteChoisie = mainJ1[choixCarte - 1];
            bornes[choixBorne - 1].ajouterCarteJ1(carteChoisie);
            joueur1->retirerCarte(carteChoisie);

            if (!cartes.empty()) {
                joueur1->ajouterCarte(cartes.back());
                cartes.pop_back();
            }


            if (EstGagnant(bornes[choixBorne - 1].getCarteJ1(), bornes[choixBorne - 1].getCarteJ2(), joueur1, joueur2)) {

                bornes[choixBorne - 1].setGagnant(joueur1);
                clearConsole();
                joueur1->AjouterBorne(bornes[choixBorne - 1]);
                std::string message = "Borne" + std::to_string(bornes[choixBorne - 1].getnumero()) + " :";
                AfficheASCII(message);
                AfficheASCII(joueur1->getNom());

                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
            if (EstGagnant(bornes[choixBorne - 1].getCarteJ2(), bornes[choixBorne - 1].getCarteJ1(), joueur2, joueur1)) {
                bornes[choixBorne - 1].setGagnant(joueur2);
                clearConsole();
                joueur2->AjouterBorne(bornes[choixBorne - 1]);
                std::string message = "Borne" + std::to_string(bornes[choixBorne - 1].getnumero()) + " :";
                AfficheASCII(message);
                AfficheASCII(joueur2->getNom());
                
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
            AfficherVictoire(joueur1, joueur2);
        }
        {
            clearConsole();
            std::cout << "\n--- Tour " << tour + 1 << " ---\n";
            AfficheASCII(joueur1->getNom());
            AfficherBornesRevendiquees(joueur1);
            AfficherBornes(bornes, joueur1->getMain(), joueur2->getMain());
            AfficherBornesRevendiquees(joueur2);       
            AfficheASCII(joueur2->getNom());

            std::cout << "\nC'est au tour de " << joueur2->getNom() << "\n";
            
            int ready = 0;
            ready = AfficherReady(ready);

            std::vector<Cartes> mainJ2 = AfficherMain(joueur2);
            int choixCarte;
            std::cout << joueur2->getNom() << u8", entrez l'index de la carte à jouer (1 à " << mainJ2.size() << ") : ";
            while (!(std::cin >> choixCarte) || choixCarte < 1 || choixCarte >(int)mainJ2.size()) {
                std::cin.clear();
                std::string dummy;
                std::getline(std::cin, dummy);
                std::cout << "Erreur. Veuillez entrer un nombre entre 1 et " << mainJ2.size() << " : ";
            }
            int choixBorne;
            std::cout << joueur2->getNom() << u8", entrez l'index de la borne où placer la carte (1 à 9) : ";

            while (true) {
                while (!(std::cin >> choixBorne) || choixBorne < 1 || choixBorne > 9) {
                    std::cin.clear();
                    std::string dummy;
                    std::getline(std::cin, dummy);
                    std::cout << "Erreur. Veuillez entrer un nombre entre 1 et 9 : ";
                }

                if (bornes[choixBorne - 1].getCarteJ2().size() < 3) {
                    break;
                }
                else {
                    std::cout << u8"Erreur : La borne " << choixBorne << " a déjà 3 cartes. Choisissez une autre borne : ";
                }
            }
            Cartes carteChoisie = mainJ2[choixCarte - 1];
            bornes[choixBorne - 1].ajouterCarteJ2(carteChoisie);
            joueur2->retirerCarte(carteChoisie);

            if (!cartes.empty()) {
                joueur2->ajouterCarte(cartes.back());
                cartes.pop_back();
            }

            if (EstGagnant(bornes[choixBorne - 1].getCarteJ1(), bornes[choixBorne - 1].getCarteJ2(), joueur1, joueur2)) {
                bornes[choixBorne - 1].setGagnant(joueur1);
                clearConsole();
                joueur1->AjouterBorne(bornes[choixBorne - 1]);
                std::string message = "Borne " + std::to_string(bornes[choixBorne - 1].getnumero()) + " :";
                AfficheASCII(message);
                AfficheASCII(joueur1->getNom());
                
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
            if (EstGagnant(bornes[choixBorne - 1].getCarteJ2(), bornes[choixBorne - 1].getCarteJ1(), joueur2, joueur1)) {
                bornes[choixBorne - 1].setGagnant(joueur2);
                clearConsole();
                joueur2->AjouterBorne(bornes[choixBorne - 1]);
                std::string message = "Borne " + std::to_string(bornes[choixBorne - 1].getnumero()) + " :";
                AfficheASCII(message);
                AfficheASCII(joueur2->getNom());
                
                std::this_thread::sleep_for(std::chrono::seconds(3)); 
            }
            AfficherVictoire(joueur1, joueur2);
        }

        AfficherBornes(bornes, joueur1->getMain(), joueur2->getMain());
    }
}



    bool Partie::EstCouleur(std::vector<Cartes> trioDeCarte) {
        if (trioDeCarte.size() != 3) {
            return false;
        }
        return (trioDeCarte[0].getcouleur() == trioDeCarte[1].getcouleur() && trioDeCarte[1].getcouleur() == trioDeCarte[2].getcouleur());
    }

    bool Partie::EstSuite(std::vector<Cartes> trioDeCarte) {
        if (trioDeCarte.size() != 3) return false;
        std::vector<int> numeros = {
            trioDeCarte[0].getnumero(),
            trioDeCarte[1].getnumero(),
            trioDeCarte[2].getnumero()
        };
        std::sort(numeros.begin(), numeros.end());
        return (numeros[1] == numeros[0] + 1 && numeros[2] == numeros[1] + 1);
    }

    bool Partie::EstSuiteCouleur(std::vector<Cartes> trioDeCarte) {
        if (trioDeCarte.size() != 3) return false;
        std::vector<int> numeros = {
            trioDeCarte[0].getnumero(),
            trioDeCarte[1].getnumero(),
            trioDeCarte[2].getnumero()
        };
        std::sort(numeros.begin(), numeros.end());
        return (numeros[1] == numeros[0] + 1 && numeros[2] == numeros[1] + 1 && trioDeCarte[0].getcouleur() == trioDeCarte[1].getcouleur() && trioDeCarte[1].getcouleur() == trioDeCarte[2].getcouleur());
    }

    bool Partie::EstBrelan(std::vector<Cartes> trioDeCarte) {
        if (trioDeCarte.size() != 3) return false;
        std::vector<int> numeros = {
        trioDeCarte[0].getnumero(),
        trioDeCarte[1].getnumero(),
        trioDeCarte[2].getnumero()
        };
        return (numeros[0] == numeros[1] &&  numeros[1] == numeros[2]);
    }

    int Partie::getRangCombinaison(std::vector<Cartes> trio) {
        if (EstSuiteCouleur(trio)) return 5;
        if (EstBrelan(trio)) return 4;
        if (EstCouleur(trio)) return 3;
        if (EstSuite(trio)) return 2;
        return 1;
    }

    bool Partie::EstGagnant(std::vector<Cartes> trioDeCarteJ1, std::vector<Cartes> trioDeCarteJ2, Joueur* J1, Joueur* J2){
        if (trioDeCarteJ1.size() == 3 && trioDeCarteJ2.size()==3) {
            int rangJ1 = getRangCombinaison(trioDeCarteJ1);
            int rangJ2 = getRangCombinaison(trioDeCarteJ2);

            if (rangJ1 > rangJ2) {
                return true;
            }
            else if (rangJ1 < rangJ2) {
                return false;
            }
            int sommeJ1 = trioDeCarteJ1[0].getnumero() + trioDeCarteJ1[1].getnumero() + trioDeCarteJ1[2].getnumero();
            int sommeJ2 = trioDeCarteJ2[0].getnumero() + trioDeCarteJ2[1].getnumero() + trioDeCarteJ2[2].getnumero();

            if (sommeJ1 > sommeJ2) {
                return true;
            }
            else if (sommeJ1 < sommeJ2) {
                return false;
            }
            return false;
        }
        else {
            cout << "\n Il y'a seulement " << trioDeCarteJ1.size() << " cartes sur la borne pour "<<J1->getNom()<<" et " << trioDeCarteJ2.size() << " pour "<<J2->getNom() << endl;
        }
    }


    

