#pragma once

#include "Cartes.h"
#include "Borne.h"
#include "Joueur.h"
#include <iostream>
#include <string>
#include <vector>

enum CouleurCarte {
    BLEU,
    VERT,
    JAUNE,
    ROUGE,
    VIOLET,
    ORANGE,
    INCONNU
};


void AfficheBanniereAnim();
void AfficherBornesRevendiqueesPlusAJ(Joueur* joueur);
void AfficherBornesRevendiquees(Joueur* joueur);
void AfficheASCII(const std::string& texte);
void AffichePlateau(const std::vector<Borne>& bornes, Joueur* joueur1, Joueur* joueur2);
CouleurCarte CouleurToEnum(const std::string& couleur);
void AfficheCarte(const Cartes& carte);
int AfficheChoixCarte(Joueur* joueur, int choixCarte);
int AfficheChoixBorne(Joueur* joueur, int choixBorne, std::vector<Borne> bornes, int numJoueur);
void AfficherBornes(const std::vector<Borne>& bornes, const std::vector<Cartes>& main1, const std::vector<Cartes>& main2);
void AfficherBornesPlusAJ(const std::vector<Borne>& bornes, const std::vector<Cartes>& main1, const std::vector<Cartes>& main2);
int AfficherReady(int ready);
std::vector<Cartes> AfficherMain(Joueur* joueur);
void AfficherBorneGagnee(Joueur* joueur1, Borne borne);
bool AfficherVictoire(std::vector<Borne> bornes, Joueur* joueur1, Joueur* joueur2);
void clearConsole();
