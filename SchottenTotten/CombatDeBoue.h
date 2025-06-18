#pragma once
#include "CarteTactique.h"
class CombatDeBoue : public CarteTactique {
public:
    int getNumero() const override { return 0; }
    std::string getNom() const override { return "Combat de Boue"; }
    void appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible) override;
};