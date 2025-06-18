#pragma once
#include "CarteTactique.h"
class Strategie : public CarteTactique {
public:
    int getNumero() const override { return 0; }
    std::string getNom() const override { return "Stratège"; }
    void appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible = nullptr) override;
};