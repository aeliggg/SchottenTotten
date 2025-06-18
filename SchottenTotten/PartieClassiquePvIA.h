#pragma once
#include "PartieClassique.h"
class PartieClassiquePvIA : public PartieClassique {
public:
    bool jouer() override;
    void TourDePartieIA(int tour, std::vector<Borne>& bornes, Joueur* IA, Joueur* adversaire, int numJoueur) override;
};