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


bool Partie::jouer() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::shuffle(cartes.begin(), cartes.end(), std::default_random_engine(std::rand()));

    DistribuerCartes();

    std::cout << u8"Début de la partie entre " << joueur1->getNom() << " et " << joueur2->getNom() << " !\n";
    bool bPartieFinie = 0;
    bool veutRejouer = FALSE;
    int tour = 0;
    while (bPartieFinie == 0){
        if (tour != 0) {
            clearConsole();
        }
        SetConsoleOutputCP(CP_UTF8);
        TourDePartie(tour, bornes, joueur1, joueur2, 1);

        bPartieFinie = AfficherVictoire(bornes, joueur1, joueur2); // AfficherVictoire renvoie 1 dans le cas où la partie est terminée
        if (bPartieFinie) { FinDePartie(); }
        else{ // TOUR DU DEUXIEME JOUEUR
            clearConsole();
            TourDePartie(tour, bornes, joueur2, joueur1, 2);
            
            bPartieFinie = AfficherVictoire(bornes, joueur1, joueur2);
            if (bPartieFinie) {
                veutRejouer = FinDePartie();
            }
        }
        tour++;
    }
    return veutRejouer;
}

bool Partie::jouerIA() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::shuffle(cartes.begin(), cartes.end(), std::default_random_engine(std::rand()));
    DistribuerCartes();
    std::cout << u8"Début de la partie entre " << joueur1->getNom() << " et l'IA";
    joueur2->setNom("IA");
    bool bPartieFinie = 0;
    bool veutRejouer = FALSE;
    int tour = 0;
    while (bPartieFinie == 0) {
        if (tour != 0) {
            clearConsole();
        }
        SetConsoleOutputCP(CP_UTF8);
        TourDePartie(tour, bornes, joueur1, joueur2, 1);

        bPartieFinie = AfficherVictoire(bornes, joueur1, joueur2); // AfficherVictoire renvoie 1 dans le cas où la partie est terminée
        if (bPartieFinie) { FinDePartie(); }
        else { // TOUR DU DEUXIEME JOUEUR
            clearConsole();
            TourDePartieIA(tour, bornes, joueur2, joueur1, 2);

            bPartieFinie = AfficherVictoire(bornes, joueur1, joueur2);
            if (bPartieFinie) {
                veutRejouer = FinDePartie();
            }
        }
        tour++;
    }
    return veutRejouer;
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

bool Partie::EstRevendiquable(const std::vector<Cartes>& cartesJoueur,const std::vector<Cartes>& cartesAdverse,Joueur* J,Joueur* Adverse) {
    if (cartesJoueur.size() != 3) return false; //Un joueur ne peut revendiquer que s'il a déjà posé 3 cartes

    if (cartesAdverse.size() == 3)
        return this->EstGagnant(cartesJoueur, cartesAdverse, J, Adverse, J); //Si adversaire a 3 cartes, comparer directement

    int rangJoueur = this->getRangCombinaison(cartesJoueur); //Rang de la combinaison du joueur
    int sommeJoueur = cartesJoueur[0].getnumero() + cartesJoueur[1].getnumero() + cartesJoueur[2].getnumero(); //Somme des valeurs des cartes du joueur

    std::vector<Cartes> cartesRestantes = this->cartes;//Cartes encore disponibles dans la pioche
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
            std::vector<Cartes> combinaisonComplete = cartesAdverse;
            combinaisonComplete.push_back(cartesRestantes[indexCarteCompl]);

            int rangAdv = this->getRangCombinaison(combinaisonComplete); //Rang adversaire avec carte complétée
            int sommeAdv = combinaisonComplete[0].getnumero() + combinaisonComplete[1].getnumero() + combinaisonComplete[2].getnumero(); //Somme cartes adversaire

            if (rangAdv > rangJoueur) return false; //Adversaire peut battre joueur
            if (rangAdv == rangJoueur && sommeAdv >= sommeJoueur) return false; //Adversaire égal ou meilleur en somme
        }
    }
    else if (nbCartesAdverseManquantes == 2) {
        for (unsigned int indexCarte1 = 0; indexCarte1 < cartesRestantes.size(); ++indexCarte1) { //Boucle carte 1
            for (unsigned int indexCarte2 = indexCarte1 + 1; indexCarte2 < cartesRestantes.size(); ++indexCarte2) { //Boucle carte 2
                std::vector<Cartes> combinaisonComplete = cartesAdverse;
                combinaisonComplete.push_back(cartesRestantes[indexCarte1]);
                combinaisonComplete.push_back(cartesRestantes[indexCarte2]);

                int rangAdv = this->getRangCombinaison(combinaisonComplete); //Rang adversaire
                int sommeAdv = combinaisonComplete[0].getnumero() + combinaisonComplete[1].getnumero() + combinaisonComplete[2].getnumero(); //Somme adversaire

                if (rangAdv > rangJoueur) return false; //Adversaire peut battre
                if (rangAdv == rangJoueur && sommeAdv >= sommeJoueur) return false; //Adversaire égal ou mieux
            }
        }
    }
    else if (nbCartesAdverseManquantes == 3) {
        for (unsigned int indexCarte1 = 0; indexCarte1 < cartesRestantes.size(); ++indexCarte1) { //Boucle carte 1
            for (unsigned int indexCarte2 = indexCarte1 + 1; indexCarte2 < cartesRestantes.size(); ++indexCarte2) { //Boucle carte 2
                for (unsigned int indexCarte3 = indexCarte2 + 1; indexCarte3 < cartesRestantes.size(); ++indexCarte3) { //Boucle carte 3
                    std::vector<Cartes> combinaisonComplete = {
                        cartesRestantes[indexCarte1],
                        cartesRestantes[indexCarte2],
                        cartesRestantes[indexCarte3]
                    };

                    int rangAdv = this->getRangCombinaison(combinaisonComplete); //Rang adversaire
                    int sommeAdv = combinaisonComplete[0].getnumero() + combinaisonComplete[1].getnumero() + combinaisonComplete[2].getnumero(); //Somme adversaire

                    if (rangAdv > rangJoueur) return false; //Adversaire peut battre
                    if (rangAdv == rangJoueur && sommeAdv >= sommeJoueur) return false; //Adversaire égal ou mieux
                }
            }
        }
    }

    return true; //Aucune combinaison adverse ne peut battre ou égaler le joueur
}


void Partie::DistribuerCartes() {
    for (int i = 0; i < 6; ++i) {
        joueur1->ajouterCarte(cartes.back());
        cartes.pop_back();
        joueur2->ajouterCarte(cartes.back());
        cartes.pop_back();
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

void Partie::TourDePartie(int tour, std::vector<Borne>& bornes,Joueur*joueur,Joueur*adversaire,int numJoueur) {
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
    std::vector<Borne> bornesJouables = getBornesJouables();
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

void Partie::TourDePartieIA(int tour, std::vector<Borne>& bornes, Joueur* IA, Joueur* adversaire, int numJoueur) {
    TrierMain(IA);
    int choixCarte = (rand() % IA->getMain().size()) + 1;
    int choixBorne = (rand() % 9) + 1;
    while (bornes[choixBorne - 1].getGagnant() != NULL || bornes[choixBorne - 1].getCarteJ2().size() == 3) {
        choixBorne = (rand() % 9) + 1;
    }
    UpdatePlateauApresCoupJoueur(IA, choixCarte, bornes, choixBorne, numJoueur);
    VerifieBorneGagnee(choixBorne);
    clearConsole();
    if (numJoueur == 1) {
        AffichePlateau(bornes, IA, adversaire);
    }
    else {
        AffichePlateau(bornes, adversaire, IA);
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
