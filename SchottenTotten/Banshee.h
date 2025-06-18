#pragma once
#include "CarteTactique.h"
class Banshee : public CarteTactique {
public:
    int getNumero() const override { return 0; }
    std::string getNom() const override { return "Banshee"; }
    void appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible = nullptr) override;
};