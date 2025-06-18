#pragma once
#include "PartieClassique.h"
class PartieClassiquePvIA : public PartieClassique {
public:
    PartieClassiquePvIA() : PartieClassique() {}
    PartieClassiquePvIA(Joueur* J1, Joueur* J2) : PartieClassique(J1, J2) {}
    bool jouer() override;
    void TourDePartieIA(int tour, std::vector<Borne>& bornes, Joueur* IA, Joueur* adversaire, int numJoueur) override;
};