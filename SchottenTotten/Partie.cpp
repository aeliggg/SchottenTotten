#include "Partie.h"
#include "Affichage.h"
#include <limits>
#include <iomanip>   // Pour std::setw
#include <thread>    // Pour sleep_for
#include <chrono>
#include "Borne.h"
#include <iostream>
#include <functional>
#include <algorithm>
#include <random>
#include <ctime>
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>
#include <conio.h>


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

Partie::~Partie() {
    delete joueur1;
    delete joueur2;
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

bool Partie::EstGagnant(std::vector<Cartes> trioDeCarteJ1, std::vector<Cartes> trioDeCarteJ2, Joueur* J1, Joueur* J2,Joueur* First){
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
        else if (sommeJ1 == sommeJ2) {
            if (J1 == First) {
                return true;
            }
            else {
                return false;
            }
        }
    }
    else {
        cout << "\n Il y'a seulement " << trioDeCarteJ1.size() << " cartes sur la borne pour "<<J1->getNom()<<" et " << trioDeCarteJ2.size() << " pour "<<J2->getNom() << endl;
    }
}


void Partie::VerifieBorneRevendique(int choixBorne) {
    int indexBorne = 0;
    while (bornes[indexBorne].getnumero() != choixBorne) {
        indexBorne++;
    }
    if (EstRevendiquable(bornes[indexBorne].getCarteJ1(), bornes[indexBorne].getCarteJ2(), joueur1, joueur2)&& bornes[indexBorne].getCarteJ1().size() == 3) {
        bornes[indexBorne].setGagnant(joueur1);
        //clearConsole();
        joueur1->AjouterBorne(bornes[indexBorne]);
        //AfficherBorneGagnee(joueur1, bornes[indexBorne]);
        std::cout << "\nRevendication par " << joueur1->getNom() << " sur la borne " << bornes[indexBorne].getnumero() << u8"validée !" << std::endl;
    }
    else if (EstRevendiquable(bornes[indexBorne].getCarteJ2(), bornes[indexBorne].getCarteJ1(), joueur2, joueur1)&& bornes[indexBorne].getCarteJ2().size() == 3) {
        bornes[indexBorne].setGagnant(joueur2);
        //clearConsole();
        joueur2->AjouterBorne(bornes[indexBorne]);
        //AfficherBorneGagnee(joueur2, bornes[indexBorne]);
        std::cout << "\nRevendication par " << joueur2->getNom() << " sur la borne " << bornes[indexBorne].getnumero() << u8" validée !" << std::endl;
    }
    else {
        std::cout << "\nVous ne pouvez pas revendiquer cette borne.\n";
    }
}

void Partie::VerifieBorneGagnee(int choixBorne) {
    if (EstGagnant(bornes[choixBorne - 1].getCarteJ1(), bornes[choixBorne - 1].getCarteJ2(), joueur1, joueur2,bornes[choixBorne-1].getFirst())) {
        bornes[choixBorne - 1].setGagnant(joueur1);
        clearConsole();
        joueur1->AjouterBorne(bornes[choixBorne - 1]);
        AfficherBorneGagnee(joueur1, bornes[choixBorne - 1]);
    }
    if (EstGagnant(bornes[choixBorne - 1].getCarteJ2(), bornes[choixBorne - 1].getCarteJ1(), joueur2, joueur1, bornes[choixBorne - 1].getFirst())) {
        bornes[choixBorne - 1].setGagnant(joueur2);
        clearConsole();
        joueur2->AjouterBorne(bornes[choixBorne - 1]);
        AfficherBorneGagnee(joueur2, bornes[choixBorne - 1]);
    }
}

bool Partie::FinDePartie() {
    int choixUtilisateur = 0;
    std::vector<std::string> choix = { "Rejouer","Menu" };
    while (true) {
        std::cout << "\rQue souhaitez vous faire ? ";
        for (int i = 0; i < 2; ++i) {
            if (i == choixUtilisateur)
                std::cout << "[" << choix[i] << "]";
            else
                std::cout << " " << choix[i] << " ";
        }
        std::cout << u8" (Flèches gauche/droite, Entrée pour valider)   " << std::flush;

        int key = _getch();
        if (key == 224) { // Touche spéciale (flèche)
            key = _getch();
            if (key == 75 || key == 77) { // Flèche gauche ou droite
                choixUtilisateur = (choixUtilisateur + 1) % 2;
            }
            
        }
        else if (key == 13) {
            if (choixUtilisateur == 0) {
                return TRUE;
            }
            else if (choixUtilisateur == 1) {
                return FALSE;
            }
        }
    }
}

void Partie::UpdatePlateauApresCoupJoueur(Joueur* joueur, int choixCarte, std::vector<Borne>& bornes, int choixBorne, int numJoueur) {
    std::vector<Cartes> main = joueur->getMain();
    Cartes carteChoisie = main[choixCarte - 1];
    if (numJoueur == 1) {
        bornes[choixBorne - 1].ajouterCarteJ1(carteChoisie);
    }
    else {
        bornes[choixBorne - 1].ajouterCarteJ2(carteChoisie);
    }
    joueur->retirerCarte(carteChoisie);

    if (!cartes.empty()) {
        joueur->ajouterCarte(cartes.back());
        cartes.pop_back();
    }
}

std::vector<Borne> Partie::getBornesJouables() {
    std::vector<Borne> res = {};
    for (int iBorne = 0; iBorne < bornes.size() ; iBorne++) {
        if (bornes[iBorne].getGagnant() == nullptr) {
            res.push_back(bornes[iBorne]);
        }
    }
    return res;
}
