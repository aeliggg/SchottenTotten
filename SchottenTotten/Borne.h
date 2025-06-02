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
	std::vector<Cartes> vBORcartesJ1;
	std::vector<Cartes> vBORcartesJ2;
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
	std::vector<Cartes> getCarteJ1() const;
	std::vector<Cartes> getCarteJ2() const;
	void ajouterCarteJ1(const Cartes& carte);
	void ajouterCarteJ2(const Cartes& carte);
	bool operator<(const Borne& other) const;
};
