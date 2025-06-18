#pragma once
#include "CarteTactique.h"
class Joker : public CarteTactique {
public:
    int getNumero() const override { return -1; } // À choisir lors de la revendication
    std::string getNom() const override { return "Joker"; }
    // Stocke info temporaire (couleur/valeur choisies) si besoin
};