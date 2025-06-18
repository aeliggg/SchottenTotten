#pragma once
#include "CarteTactique.h"
class Traitre : public CarteTactique {
public:
    int getNumero() const override { return 0; }
    std::string getNom() const override { return "Traître"; }
    void appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible = nullptr) override;
};