#pragma once
#pragma once
#include "Partie.h"

class PartieExpert : public Partie {
public:
    PartieExpert();
    PartieExpert(Joueur* Joueur1, Joueur* Joueur2);
    virtual bool jouer() override =0;
    void DistribuerCartes() override;
    bool EstRevendiquable(const std::vector<std::shared_ptr<Carte>>& trioDeCarteJ1, const std::vector<std::shared_ptr<Carte>>& Cartesj2, Joueur* J1, Joueur* J2) override;
    virtual void TourDePartie(int tour, std::vector<Borne>& bornes, Joueur* joueur, Joueur* adversaire, int numJoueur) override;
    void VerifieBorneRevendique(int choixBorne) override;
    void VerifieBorneGagnee(int choixBorne) override;
    virtual void TourDePartieIA(int tour, std::vector<Borne>& bornes, Joueur* IA, Joueur* adversaire, int numJoueur) override;
};