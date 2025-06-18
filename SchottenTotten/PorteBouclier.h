#pragma once
#include "CarteTactique.h"

class PorteBouclier : public CarteTactique {
public:
    int getNumero() const override { return -2; }
    std::string getNom() const override { return "Porte-Bouclier"; }
};