#pragma once
#include "CarteTactique.h"
class ChasseurDeTete : public CarteTactique {
public:
    int getNumero() const override { return 0; }
    std::string getNom() const override { return "Chasseur de Tête"; }
    void appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible = nullptr) override;
};