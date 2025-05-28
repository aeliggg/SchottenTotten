#pragma once

#include "Cartes.h"
#include "Borne.h"
#include <iostream>
#include <string>

enum CouleurCarte {
    BLEU,
    VERT,
    JAUNE,
    ROUGE,
    VIOLET,
    ORANGE,
    INCONNU
};

CouleurCarte CouleurToEnum(const std::string& couleur);
void AfficheCarte(const Cartes& carte);
void AfficherBornes(const std::vector<Borne>& bornes, const std::vector<Cartes>& main1, const std::vector<Cartes>& main2);
void clearConsole();
