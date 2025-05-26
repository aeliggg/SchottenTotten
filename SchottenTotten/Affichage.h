#pragma once

#include "Cartes.h"
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