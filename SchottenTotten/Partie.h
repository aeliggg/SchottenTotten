#pragma once
#include <string>
#include <vector>
#include "Cartes.h"
#include "Joueur.h"
#include "Borne.h"

class Partie
{
private:
    std::vector<Cartes> cartes;
    std::vector<Borne> bornes;
    Joueur* joueur1;
    Joueur* joueur2;

public:
    Partie();
    Partie(Joueur* j1, Joueur* j2);
    void ajouterCarte(const Cartes& carte);
    std::vector<Cartes> getCartes();
    void ajouterBorne(const Borne& borne);
    std::vector<Borne> getBornes();
    Joueur* getJoueur1();
    Joueur* getJoueur2();
    void jouer();
};
