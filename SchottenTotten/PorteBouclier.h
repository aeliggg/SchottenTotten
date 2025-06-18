#pragma once
#include "CarteTactique.h"
class PorteBouclier : public CarteTactique {
public:
    int getNumero() const override { return -2; } // À choisir lors de la revendication (1,2,3)
    std::string getNom() const override { return "Porte-Bouclier"; }
};