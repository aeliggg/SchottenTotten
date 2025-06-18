#pragma once
#include "CarteTactique.h"

class Joker : public CarteTactique {
public:
    int getNumero() const override { return -1; }
    std::string getNom() const override { return "Joker"; }
};