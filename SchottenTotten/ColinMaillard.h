#pragma once
#include "CarteTactique.h"
class ColinMaillard : public CarteTactique {
public:
    int getNumero() const override { return 0; }
    std::string getNom() const override { return "Colin-Maillard"; }
    void appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible) override;
};