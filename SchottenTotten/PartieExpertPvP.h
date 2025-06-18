#pragma once
#include "PartieExpert.h"
class PartieExpertPvP : public PartieExpert {
public:
    PartieExpertPvP() : PartieExpert() {}
    PartieExpertPvP(Joueur* J1, Joueur* J2) : PartieExpert(J1, J2) {}
    bool jouer() override;
};