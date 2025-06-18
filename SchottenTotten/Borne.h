#pragma once
#include <iostream>
#include "Cartes.h"
#include <string>
#include <vector>


class Partie;
class Joueur;
class Borne {
private:
	int iBORnuméro;
	Partie* BORpartie;
	Joueur* GagnantBorne;
	Joueur* FirstPlayer;
	std::vector<Carte> vBORcartesJ1;
	std::vector<Carte> vBORcartesJ2;
public:
	Borne();
	Borne(int numéro);
	int getnumero() const;
	Joueur* getGagnant() const;
	Joueur* getFirst() const;
	void setnumero(int numéro);
	void setpartie(Partie* partie) { BORpartie = partie; }
	void setGagnant(Joueur* joueur) { GagnantBorne = joueur; }
	void setFirst(Joueur* joueur) { FirstPlayer = joueur; }
	std::vector<Carte> getCarteJ1() const;
	std::vector<Carte> getCarteJoueur(Joueur* joueur) const;
	std::vector<Carte> getCarteJ2() const;
	void ajouterCarteJ1(const Carte& carte);
	void ajouterCarteJ2(const Carte& carte);
	bool operator<(const Borne& other) const;
};
