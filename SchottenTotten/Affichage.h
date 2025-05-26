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
void AfficherBornes(std::vector<Borne> bornes, std::vector<Cartes> main1, std::vector<Cartes> main2);