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
    void ajouterCarte(const Cartes& carte) { cartes.push_back(carte); };
    std::vector<Cartes> getCartes() { return cartes; };
    void ajouterBorne(const Borne& borne) { bornes.push_back(borne); };
    std::vector<Borne> getBornes() { return bornes; };
    Joueur* getJoueur1() { return joueur1; };
    Joueur* getJoueur2() { return joueur2; };
    void jouer();
    bool EstSuite(std::vector<Cartes> trioDeCarte);
    bool EstCouleur(std::vector<Cartes> trioDeCarte);
    bool EstSuiteCouleur(std::vector<Cartes> trioDeCarte);
    bool EstBrelan(std::vector<Cartes> trioDeCarte);
    int getRangCombinaison(std::vector<Cartes> trio);
    bool EstGagnant(std::vector<Cartes> trioDeCarteJ1, std::vector<Cartes> trioDeCartej2, Joueur* J1, Joueur* J2);
    void DistribuerCartes();
    void VerifieBorneGagnee(int choixBorne);
    void FinDePartie();
    void UpdateBoardApresChoixCarte(Joueur* joueur, int choixCarte, std::vector<Borne> bornes, int choixBorne, int numJoueur);
};
