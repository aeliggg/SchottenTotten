#pragma once
#include <iostream>
#include "Cartes.h"
#include <string>
#include <vector>

// DÉCLARATION ANTICIPÉE DE PARTIE
class Partie;

class Borne {
private:
	int iBORnuméro;
	Partie* BORpartie;
	std::vector<Cartes> vBORcartesJ1;
	std::vector<Cartes> vBORcartesJ2;
public:
	Borne();
	Borne(int numéro);
	int getnumero() const;
	void setnumero(int numéro);
	void setpartie(Partie* partie) { BORpartie = partie; }
	vector<Cartes> getCarteJ1() const;
	vector<Cartes> getCarteJ2() const;
	void ajouterCarteJ1(const Cartes& carte);
	void ajouterCarteJ2(const Cartes& carte);
};
