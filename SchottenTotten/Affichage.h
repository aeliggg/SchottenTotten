#pragma once

#include "Carte.h"
#include "Borne.h"
#include "Joueur.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

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
void AfficheCarte(const Carte* carte);
int AfficheChoixCarte(Joueur* joueur, int choixCarte);
int AfficheChoixCarteNavigable(Joueur* joueur, int choixCarte);
int AfficheChoixBorne(Joueur* joueur, int choixBorne, std::vector<Borne> bornes, int numJoueur);
int AfficheChoixBorneNavigable(Joueur* joueur, int choixBorne, const std::vector<Borne>& bornes, int numJoueur);
int AfficheChoixBorneRevendique(Joueur* joueur, int choixBorneRevendique, std::vector<Borne> bornes, int numJoueur);
void AfficherBornes(const std::vector<Borne>& bornes, const std::vector<std::unique_ptr<Carte>>& main1, const std::vector<std::unique_ptr<Carte>>& main2);
void AfficherBornesPlusAJ(const std::vector<Borne>& bornes, const std::vector<std::unique_ptr<Carte>>& main1, const std::vector<std::unique_ptr<Carte>>& main2);
void AfficherReady();
void TrierMain(Joueur* joueur);
void AfficherBorneGagnee(Joueur* joueur1, Borne borne);
bool AfficherVictoire(std::vector<Borne> bornes, Joueur* joueur1, Joueur* joueur2);
void clearConsole();