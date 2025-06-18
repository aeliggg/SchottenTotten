#include "Partie.h"
#include "PartieClassique.h"
#include "Affichage.h"
#include "Borne.h"
#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>
#include <random>
#include <ctime>
#include <windows.h>
#include <codecvt>
#include <locale>
#include <conio.h>
#include <limits>
#include <iomanip>
#include <thread> 

void PartieClassique::TourDePartie(int tour, std::vector<Borne>& bornes, Joueur* joueur, Joueur* adversaire, int numJoueur) {
    std::cout << "\n--- Tour " << tour + 1 << " ---\n";
    if (numJoueur == 1) {
        AffichePlateau(bornes, joueur, adversaire);
    }
    else {
        AffichePlateau(bornes, adversaire, joueur);
    }

    std::cout << "\nC'est au tour de " << joueur->getNom() << "\n";

    AfficherReady();

    TrierMain(joueur);
    int choixCarte = 0;
    choixCarte = AfficheChoixCarteNavigable(joueur, choixCarte);

    int choixBorne = 0;
    std::vector<Borne> bornesJouables = Partie::getBornesJouables();
    choixBorne = AfficheChoixBorneNavigable(joueur, choixBorne, bornesJouables, numJoueur);
    if (bornes[choixBorne - 1].getCarteJ1().size() == 0 && bornes[choixBorne - 1].getCarteJ2().size() == 0) {
        bornes[choixBorne - 1].setFirst(joueur);
    }
    UpdatePlateauApresCoupJoueur(joueur, choixCarte, bornes, choixBorne, numJoueur);
    VerifieBorneGagnee(choixBorne);
    clearConsole();
    if (numJoueur == 1) {
        AffichePlateau(bornes, joueur, adversaire);
    }
    else {
        AffichePlateau(bornes, adversaire, joueur);
    }
    std::vector<Borne> bornesRevendicables = getBornesJouables();
    int choixBorneRevendique = -1;
    while (choixBorneRevendique != 0) {
        choixBorneRevendique = AfficheChoixBorneRevendique(joueur, choixBorneRevendique, bornesRevendicables, numJoueur);
        if (choixBorneRevendique != 0) {
            VerifieBorneRevendique(choixBorneRevendique);
        }
    }
}

bool PartieClassique::EstRevendiquable(const std::vector<Carte>& cartesJoueur, const std::vector<Carte>& cartesAdverse, Joueur* J, Joueur* Adverse) {
    if (cartesJoueur.size() != 3) return false; //Un joueur ne peut revendiquer que s'il a déjà posé 3 cartes

    if (cartesAdverse.size() == 3)
        return this->EstGagnant(cartesJoueur, cartesAdverse, J, Adverse, J); //Si adversaire a 3 cartes, comparer directement

    int rangJoueur = this->getRangCombinaison(cartesJoueur); //Rang de la combinaison du joueur
    int sommeJoueur = cartesJoueur[0].getNumero() + cartesJoueur[1].getNumero() + cartesJoueur[2].getNumero(); //Somme des valeurs des cartes du joueur

    std::vector<Carte> cartesRestantes = this->cartes;//Cartes encore disponibles dans la pioche
    for (int carteJ1 = 0; carteJ1 < joueur1->getMain().size(); carteJ1++) {
        cartesRestantes.push_back(joueur1->getMain()[carteJ1]);
    }
    for (int carteJ2 = 0; carteJ2 < joueur2->getMain().size(); carteJ2++) {
        cartesRestantes.push_back(joueur2->getMain()[carteJ2]);
    }


    unsigned int nbCartesAdverseManquantes = 3 - cartesAdverse.size(); //Cartes que l'adversaire doit encore poser

    if (nbCartesAdverseManquantes == 0)
        return this->EstGagnant(cartesJoueur, cartesAdverse, J, Adverse, J); //Déjà géré, sécurité

    else if (nbCartesAdverseManquantes == 1) {
        for (unsigned int indexCarteCompl = 0; indexCarteCompl < cartesRestantes.size(); ++indexCarteCompl) { //Tester avec chaque carte restante
            std::vector<Carte> combinaisonComplete = cartesAdverse;
            combinaisonComplete.push_back(cartesRestantes[indexCarteCompl]);

            int rangAdv = this->getRangCombinaison(combinaisonComplete); //Rang adversaire avec carte complétée
            int sommeAdv = combinaisonComplete[0].getNumero() + combinaisonComplete[1].getNumero() + combinaisonComplete[2].getNumero(); //Somme cartes adversaire

            if (rangAdv > rangJoueur) return false; //Adversaire peut battre joueur
            if (rangAdv == rangJoueur && sommeAdv >= sommeJoueur) return false; //Adversaire égal ou meilleur en somme
        }
    }
    else if (nbCartesAdverseManquantes == 2) {
        for (unsigned int indexCarte1 = 0; indexCarte1 < cartesRestantes.size(); ++indexCarte1) { //Boucle carte 1
            for (unsigned int indexCarte2 = indexCarte1 + 1; indexCarte2 < cartesRestantes.size(); ++indexCarte2) { //Boucle carte 2
                std::vector<Carte> combinaisonComplete = cartesAdverse;
                combinaisonComplete.push_back(cartesRestantes[indexCarte1]);
                combinaisonComplete.push_back(cartesRestantes[indexCarte2]);

                int rangAdv = this->getRangCombinaison(combinaisonComplete); //Rang adversaire
                int sommeAdv = combinaisonComplete[0].getNumero() + combinaisonComplete[1].getNumero() + combinaisonComplete[2].getNumero(); //Somme adversaire

                if (rangAdv > rangJoueur) return false; //Adversaire peut battre
                if (rangAdv == rangJoueur && sommeAdv >= sommeJoueur) return false; //Adversaire égal ou mieux
            }
        }
    }
    else if (nbCartesAdverseManquantes == 3) {
        for (unsigned int indexCarte1 = 0; indexCarte1 < cartesRestantes.size(); ++indexCarte1) { //Boucle carte 1
            for (unsigned int indexCarte2 = indexCarte1 + 1; indexCarte2 < cartesRestantes.size(); ++indexCarte2) { //Boucle carte 2
                for (unsigned int indexCarte3 = indexCarte2 + 1; indexCarte3 < cartesRestantes.size(); ++indexCarte3) { //Boucle carte 3
                    std::vector<Carte> combinaisonComplete = {
                        cartesRestantes[indexCarte1],
                        cartesRestantes[indexCarte2],
                        cartesRestantes[indexCarte3]
                    };

                    int rangAdv = this->getRangCombinaison(combinaisonComplete); //Rang adversaire
                    int sommeAdv = combinaisonComplete[0].getNumero() + combinaisonComplete[1].getNumero() + combinaisonComplete[2].getNumero(); //Somme adversaire

                    if (rangAdv > rangJoueur) return false; //Adversaire peut battre
                    if (rangAdv == rangJoueur && sommeAdv >= sommeJoueur) return false; //Adversaire égal ou mieux
                }
            }
        }
    }

    return true; //Aucune combinaison adverse ne peut battre ou égaler le joueur
}

void PartieClassique::DistribuerCartes() {
    for (int i = 0; i < 6; ++i) {
        joueur1->ajouterCarte(cartes.back());
        cartes.pop_back();
        joueur2->ajouterCarte(cartes.back());
        cartes.pop_back();
    }
}


