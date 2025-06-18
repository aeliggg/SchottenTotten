#include "Partie.h"
#include "CarteFactory.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>

void Partie::ajouterCarte(std::unique_ptr<Carte> carte) {
    cartes.push_back(std::move(carte));
}

std::vector<std::unique_ptr<Carte>>& Partie::getCartes() {
    return cartes;
}

void Partie::ajouterBorne(const Borne& borne) {
    bornes.push_back(borne);
}

std::vector<Borne>& Partie::getBornes() {
    return bornes;
}

std::vector<Borne> Partie::getBornesJouables() {
    std::vector<Borne> res;
    for (auto& b : bornes) {
        if (b.getGagnant() == nullptr) res.push_back(b);
    }
    return res;
}

Joueur* Partie::getJoueur1() { return joueur1; }
Joueur* Partie::getJoueur2() { return joueur2; }

bool Partie::EstCouleur(const std::vector<std::unique_ptr<Carte>>& trioDeCarte) {
    if (trioDeCarte.size() != 3) return false;
    return (trioDeCarte[0]->getCouleur() == trioDeCarte[1]->getCouleur()
        && trioDeCarte[1]->getCouleur() == trioDeCarte[2]->getCouleur());
}

bool Partie::EstSuite(const std::vector<std::unique_ptr<Carte>>& trioDeCarte) {
    if (trioDeCarte.size() != 3) return false;
    std::vector<int> numeros = {
        trioDeCarte[0]->getNumero(),
        trioDeCarte[1]->getNumero(),
        trioDeCarte[2]->getNumero()
    };
    std::sort(numeros.begin(), numeros.end());
    return (numeros[1] == numeros[0] + 1 && numeros[2] == numeros[1] + 1);
}

bool Partie::EstSuiteCouleur(const std::vector<std::unique_ptr<Carte>>& trioDeCarte) {
    if (trioDeCarte.size() != 3) return false;
    std::vector<int> numeros = {
        trioDeCarte[0]->getNumero(),
        trioDeCarte[1]->getNumero(),
        trioDeCarte[2]->getNumero()
    };
    std::sort(numeros.begin(), numeros.end());
    return (numeros[1] == numeros[0] + 1 && numeros[2] == numeros[1] + 1
        && trioDeCarte[0]->getCouleur() == trioDeCarte[1]->getCouleur()
        && trioDeCarte[1]->getCouleur() == trioDeCarte[2]->getCouleur());
}

bool Partie::EstBrelan(const std::vector<std::unique_ptr<Carte>>& trioDeCarte) {
    if (trioDeCarte.size() != 3) return false;
    return (trioDeCarte[0]->getNumero() == trioDeCarte[1]->getNumero()
        && trioDeCarte[1]->getNumero() == trioDeCarte[2]->getNumero());
}

int Partie::getRangCombinaison(const std::vector<std::unique_ptr<Carte>>& trio) {
    if (EstSuiteCouleur(trio)) return 5;
    if (EstBrelan(trio)) return 4;
    if (EstCouleur(trio)) return 3;
    if (EstSuite(trio)) return 2;
    return 1;
}

bool Partie::EstGagnant(const std::vector<std::unique_ptr<Carte>>& trioDeCarteJ1, const std::vector<std::unique_ptr<Carte>>& trioDeCarteJ2, Joueur* J1, Joueur* J2, Joueur* First) {
    if (trioDeCarteJ1.size() == 3 && trioDeCarteJ2.size() == 3) {
        int rangJ1 = getRangCombinaison(trioDeCarteJ1);
        int rangJ2 = getRangCombinaison(trioDeCarteJ2);

        if (rangJ1 > rangJ2) return true;
        if (rangJ1 < rangJ2) return false;
        int sommeJ1 = trioDeCarteJ1[0]->getNumero() + trioDeCarteJ1[1]->getNumero() + trioDeCarteJ1[2]->getNumero();
        int sommeJ2 = trioDeCarteJ2[0]->getNumero() + trioDeCarteJ2[1]->getNumero() + trioDeCarteJ2[2]->getNumero();

        if (sommeJ1 > sommeJ2) return true;
        if (sommeJ1 < sommeJ2) return false;
        if (sommeJ1 == sommeJ2) {
            if (J1 == First) return true;
            else return false;
        }
    }
    else {
        std::cout << "\n Il y'a seulement " << trioDeCarteJ1.size() << " cartes sur la borne pour " << J1->getNom() << " et "
            << trioDeCarteJ2.size() << " pour " << J2->getNom() << std::endl;
    }
    return false;
}

void Partie::DistribuerCartes() {
    for (int i = 0; i < 6; ++i) {
        joueur1->ajouterCarte(std::move(cartes.back()));
        cartes.pop_back();
        joueur2->ajouterCarte(std::move(cartes.back()));
        cartes.pop_back();
    }
}

void Partie::VerifieBorneRevendique(int /*choixBorne*/) {
    // À spécialiser dans PartieClassique et ses dérivés
}

void Partie::VerifieBorneGagnee(int /*choixBorne*/) {
    // À spécialiser dans PartieClassique et ses dérivés
}

bool Partie::FinDePartie() {
    // Rends à false par défaut (à spécialiser si besoin)
    return false;
}

bool Partie::EstRevendiquable(const std::vector<std::unique_ptr<Carte>>& /*cartesJoueur*/, const std::vector<std::unique_ptr<Carte>>& /*cartesAdverse*/, Joueur* /*J*/, Joueur* /*Adverse*/) {
    // À spécialiser dans PartieClassique et ses dérivés
    return false;
}

void Partie::UpdatePlateauApresCoupJoueur(Joueur* joueur, int choixCarte, std::vector<Borne>& bornes, int choixBorne, int numJoueur) {
    auto& main = joueur->getMain();
    std::unique_ptr<Carte> carteChoisie = std::move(main[choixCarte - 1]);
    main.erase(main.begin() + (choixCarte - 1));
    if (numJoueur == 1) {
        bornes[choixBorne - 1].ajouterCarteJ1(std::move(carteChoisie));
    }
    else {
        bornes[choixBorne - 1].ajouterCarteJ2(std::move(carteChoisie));
    }
    if (!cartes.empty()) {
        joueur->ajouterCarte(std::move(cartes.back()));
        cartes.pop_back();
    }
}

void Partie::TourDePartieIA(int, std::vector<Borne>&, Joueur*, Joueur*, int) {
    // À spécialiser dans PartieClassiquePvIA
}

void Partie::TourDePartie(int, std::vector<Borne>&, Joueur*, Joueur*, int) {
    // À spécialiser dans PartieClassique et ses dérivés
}