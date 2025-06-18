#pragma once
#include "Carte.h"

class CarteTactique : public Carte {
public:
    std::string getCouleur() const override { return "tactique"; }
    bool estTactique() const override { return true; }
};