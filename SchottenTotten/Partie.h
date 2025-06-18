#pragma once
#include <string>
#include <vector>
#include "Cartes.h"
#include "Joueur.h"
#include "Borne.h"


class Partie
{
protected:
    std::vector<Cartes> cartes;
    std::vector<Borne> bornes;
    Joueur* joueur1;
    Joueur* joueur2;

public:
    Partie();
    Partie(Joueur* j1, Joueur* j2);
    ~Partie();
    void ajouterCarte(const Cartes& carte) { cartes.push_back(carte); };
    std::vector<Cartes> getCartes() { return cartes; };
    void ajouterBorne(const Borne& borne) { bornes.push_back(borne); };
    std::vector<Borne> getBornes() { return bornes; };
    std::vector<Borne> getBornesJouables();
    Joueur* getJoueur1() { return joueur1; };
    Joueur* getJoueur2() { return joueur2; };
    virtual bool jouer();
    bool EstSuite(std::vector<Cartes> trioDeCarte);
    bool EstCouleur(std::vector<Cartes> trioDeCarte);
    bool EstSuiteCouleur(std::vector<Cartes> trioDeCarte);
    bool EstBrelan(std::vector<Cartes> trioDeCarte);
    int getRangCombinaison(std::vector<Cartes> trio);
    virtual bool EstGagnant(std::vector<Cartes> trioDeCarteJ1, std::vector<Cartes> trioDeCartej2, Joueur* J1, Joueur* J2,Joueur* First);
    virtual void DistribuerCartes();
    virtual void VerifieBorneGagnee(int choixBorne);
    virtual void VerifieBorneRevendique(int choixRev);
    bool FinDePartie();
    virtual bool EstRevendiquable(const std::vector<Cartes>& trioDeCarteJ1, const std::vector<Cartes>& Cartesj2, Joueur* J1, Joueur* J2);
    void UpdatePlateauApresCoupJoueur(Joueur* joueur, int choixCarte, std::vector<Borne>& bornes, int choixBorne, int numJoueur);
    virtual void TourDePartieIA(int tour, std::vector<Borne>& bornes, Joueur* joueur, Joueur* IA, int numJoueur);
    virtual void TourDePartie(int tour, std::vector<Borne>& bornes, Joueur* joueur, Joueur* adversaire, int numJoueur);
};
