#pragma once
#include <string>
#include <vector>
#include "Cartes.h"
#include "Joueur.h"

class Partie
{
private:
    std::vector<Cartes> cartes;
    Joueur* joueur1;
    Joueur* joueur2;

public:
    Partie();
    Partie(Joueur* j1, Joueur* j2);
    void ajouterCarte(const Cartes& carte);
    std::vector<Cartes> getCartes();
    Joueur* getJoueur1();
    Joueur* getJoueur2();
    void jouer();
};
