#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Carte.h"
#include "Joueur.h"
#include "Borne.h"

class Partie
{
protected:
    std::vector<std::unique_ptr<Carte>> cartes; // Pioche polymorphe
    std::vector<Borne> bornes;
    Joueur* joueur1;
    Joueur* joueur2;

public:
    Partie();
    Partie(Joueur* j1, Joueur* j2);
    virtual ~Partie();

    void ajouterCarte(std::unique_ptr<Carte> carte);
    std::vector<std::unique_ptr<Carte>>& getCartes();

    void ajouterBorne(const Borne& borne);
    std::vector<Borne>& getBornes();
    std::vector<Borne> getBornesJouables();

    Joueur* getJoueur1();
    Joueur* getJoueur2();

    virtual bool jouer();
    bool EstSuite(const std::vector<std::unique_ptr<Carte>>& trioDeCarte);
    bool EstCouleur(const std::vector<std::unique_ptr<Carte>>& trioDeCarte);
    bool EstSuiteCouleur(const std::vector<std::unique_ptr<Carte>>& trioDeCarte);
    bool EstBrelan(const std::vector<std::unique_ptr<Carte>>& trioDeCarte);
    int getRangCombinaison(const std::vector<std::unique_ptr<Carte>>& trio);
    virtual bool EstGagnant(const std::vector<std::unique_ptr<Carte>>& trioDeCarteJ1, const std::vector<std::unique_ptr<Carte>>& trioDeCartej2, Joueur* J1, Joueur* J2, Joueur* First);
    virtual void DistribuerCartes();
    virtual void VerifieBorneGagnee(int choixBorne);
    virtual void VerifieBorneRevendique(int choixRev);
    bool FinDePartie();
    virtual bool EstRevendiquable(const std::vector<std::unique_ptr<Carte>>& trioDeCarteJ1, const std::vector<std::unique_ptr<Carte>>& Cartesj2, Joueur* J1, Joueur* J2);
    void UpdatePlateauApresCoupJoueur(Joueur* joueur, int choixCarte, std::vector<Borne>& bornes, int choixBorne, int numJoueur);
    virtual void TourDePartieIA(int tour, std::vector<Borne>& bornes, Joueur* joueur, Joueur* IA, int numJoueur);
    virtual void TourDePartie(int tour, std::vector<Borne>& bornes, Joueur* joueur, Joueur* adversaire, int numJoueur);
};