#pragma once
#include "CarteTactique.h"
class Espion : public CarteTactique {
public:
    int getNumero() const override { return 7; }
    std::string getNom() const override { return "Espion"; }
    // Couleur à choisir lors de la revendication
};