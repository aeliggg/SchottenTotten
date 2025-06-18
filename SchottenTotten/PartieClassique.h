#pragma once
#include "Partie.h"

class PartieClassique : public Partie {
public:
    PartieClassique();
    PartieClassique(Joueur* Joueur1, Joueur* Joueur2);
    bool jouer() override;
    void DistribuerCartes() override;
    bool EstRevendiquable(const std::vector<std::unique_ptr<Carte>>& trioDeCarteJ1, const std::vector<std::unique_ptr<Carte>>& Cartesj2, Joueur* J1, Joueur* J2) override;
    void TourDePartie(int tour, std::vector<Borne>& bornes, Joueur* joueur, Joueur* adversaire, int numJoueur) override;
    void VerifieBorneRevendique(int choixBorne) override;
    void VerifieBorneGagnee(int choixBorne) override;
    void TourDePartieIA(int tour, std::vector<Borne>& bornes, Joueur* IA, Joueur* adversaire, int numJoueur) override;
};