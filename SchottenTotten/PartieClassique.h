#pragma once
#include "Partie.h"

class PartieClassique : public Partie {
public:
	PartieClassique();
	PartieClassique(Joueur* Joueur1, Joueur* Joueur2);
	virtual bool jouer() override;
	void DistribuerCartes() override;
	bool EstRevendiquable(const std::vector<Cartes>& trioDeCarteJ1, const std::vector<Cartes>& Cartesj2, Joueur* J1, Joueur* J2) override;
	void TourDePartie(int tour, std::vector<Borne>& bornes, Joueur* joueur, Joueur* adversaire, int numJoueur) override;
	virtual void TourDePartieIA(int tour, std::vector<Borne>& bornes, Joueur* IA, Joueur* adversaire, int numJoueur) override;
}