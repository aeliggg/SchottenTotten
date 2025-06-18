#pragma once
#include "PartieExpert.h"
class PartieExpertPvIA : public PartieExpert {
public:
    PartieExpertPvIA() : PartieExpert() {}
    PartieExpertPvIA(Joueur* J1, Joueur* J2) : PartieExpert(J1, J2) {}
    bool jouer() override;
    void TourDePartieIA(int tour, std::vector<Borne>& bornes, Joueur* IA, Joueur* adversaire, int numJoueur) override;
};
