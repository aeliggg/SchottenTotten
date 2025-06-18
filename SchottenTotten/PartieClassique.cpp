#include "PartieClassique.h"
#include "CarteClassique.h"
#include "Affichage.h"
#include "Borne.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <windows.h>
#include <codecvt>
#include <locale>
#include <conio.h>
#include <limits>
#include <iomanip>
#include <thread> 

bool PartieClassique::jouer() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::shuffle(cartes.begin(), cartes.end(), std::default_random_engine(std::rand()));
    DistribuerCartes();

    std::cout << "Début de la partie entre " << joueur1->getNom() << " et " << joueur2->getNom() << " !\n";
    bool bPartieFinie = false;
    bool veutRejouer = false;
    int tour = 0;
    while (!bPartieFinie) {
        if (tour != 0) { clearConsole(); }
        SetConsoleOutputCP(CP_UTF8);
        TourDePartie(tour, bornes, joueur1, joueur2, 1);

        bPartieFinie = AfficherVictoire(bornes, joueur1, joueur2);
        if (bPartieFinie) { veutRejouer = FinDePartie(); }
        else {
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

void PartieClassique::DistribuerCartes() {
    for (int i = 0; i < 6; ++i) {
        joueur1->ajouterCarte(std::move(cartes.back()));
        cartes.pop_back();
        joueur2->ajouterCarte(std::move(cartes.back()));
        cartes.pop_back();
    }
}

bool PartieClassique::EstRevendiquable(const std::vector<std::shared_ptr<Carte>>& cartesJoueur, const std::vector<std::shared_ptr<Carte>>& cartesAdverse, Joueur* J, Joueur* Adverse) {
    if (cartesJoueur.size() != 3) return false;
    if (cartesAdverse.size() == 3)
        return this->EstGagnant(cartesJoueur, cartesAdverse, J, Adverse, J);

    int rangJoueur = this->getRangCombinaison(cartesJoueur);
    int sommeJoueur = cartesJoueur[0]->getNumero() + cartesJoueur[1]->getNumero() + cartesJoueur[2]->getNumero();

    std::vector<std::shared_ptr<Carte>> cartesRestantes;
    for (auto& c : cartes) cartesRestantes.push_back(std::make_unique<CarteClassique>(c->getNumero(), c->getCouleur()));
    for (const auto& c : joueur1->getMain()) cartesRestantes.push_back(std::make_unique<CarteClassique>(c->getNumero(), c->getCouleur()));
    for (const auto& c : joueur2->getMain()) cartesRestantes.push_back(std::make_unique<CarteClassique>(c->getNumero(), c->getCouleur()));

    size_t nbCartesAdverseManquantes = 3 - cartesAdverse.size();

    if (nbCartesAdverseManquantes == 1) {
        for (unsigned int i = 0; i < cartesRestantes.size(); ++i) {
            std::vector<std::shared_ptr<Carte>> combinaisonComplete;
            for (const auto& c : cartesAdverse) combinaisonComplete.push_back(std::make_unique<CarteClassique>(c->getNumero(), c->getCouleur()));
            combinaisonComplete.push_back(std::move(cartesRestantes[i]));
            int rangAdv = this->getRangCombinaison(combinaisonComplete);
            int sommeAdv = combinaisonComplete[0]->getNumero() + combinaisonComplete[1]->getNumero() + combinaisonComplete[2]->getNumero();
            if (rangAdv > rangJoueur) return false;
            if (rangAdv == rangJoueur && sommeAdv >= sommeJoueur) return false;
        }
    }
    // Pour 2 ou 3 cartes manquantes, à implémenter de façon analogue si besoin
    return true;
}

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
    int choixCarte = AfficheChoixCarteNavigable(joueur, 0);

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

void PartieClassique::VerifieBorneRevendique(int choixBorne) {
    int indexBorne = 0;
    while (bornes[indexBorne].getnumero() != choixBorne) {
        indexBorne++;
    }
    auto& cartesJ1 = bornes[indexBorne].getCarteJ1();
    auto& cartesJ2 = bornes[indexBorne].getCarteJ2();
    if (EstRevendiquable(cartesJ1, cartesJ2, joueur1, joueur2) && cartesJ1.size() == 3) {
        bornes[indexBorne].setGagnant(joueur1);
        joueur1->AjouterBorne(bornes[indexBorne]);
        std::cout << "\nRevendication par " << joueur1->getNom() << " sur la borne " << bornes[indexBorne].getnumero() << u8" validée !" << std::endl;
    }
    else if (EstRevendiquable(cartesJ2, cartesJ1, joueur2, joueur1) && cartesJ2.size() == 3) {
        bornes[indexBorne].setGagnant(joueur2);
        joueur2->AjouterBorne(bornes[indexBorne]);
        std::cout << "\nRevendication par " << joueur2->getNom() << " sur la borne " << bornes[indexBorne].getnumero() << u8" validée !" << std::endl;
    }
    else {
        std::cout << "\nVous ne pouvez pas revendiquer cette borne.\n";
    }
}

void PartieClassique::VerifieBorneGagnee(int choixBorne) {
    auto& cartesJ1 = bornes[choixBorne - 1].getCarteJ1();
    auto& cartesJ2 = bornes[choixBorne - 1].getCarteJ2();
    if (EstGagnant(cartesJ1, cartesJ2, joueur1, joueur2, bornes[choixBorne - 1].getFirst())) {
        bornes[choixBorne - 1].setGagnant(joueur1);
        clearConsole();
        joueur1->AjouterBorne(bornes[choixBorne - 1]);
        AfficherBorneGagnee(joueur1, bornes[choixBorne - 1]);
    }
    if (EstGagnant(cartesJ2, cartesJ1, joueur2, joueur1, bornes[choixBorne - 1].getFirst())) {
        bornes[choixBorne - 1].setGagnant(joueur2);
        clearConsole();
        joueur2->AjouterBorne(bornes[choixBorne - 1]);
        AfficherBorneGagnee(joueur2, bornes[choixBorne - 1]);
    }
}

void PartieClassique::TourDePartieIA(int, std::vector<Borne>&, Joueur*, Joueur*, int) {
    // Spécialisé dans PartieClassiquePvIA
}