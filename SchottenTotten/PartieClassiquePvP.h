#pragma once
#include "PartieClassique.h"
class PartieClassiquePvP : public PartieClassique {
public:
    PartieClassiquePvP() : PartieClassique() {}
    PartieClassiquePvP(Joueur* J1, Joueur* J2) : PartieClassique(J1, J2) {}
    bool jouer() override;
};