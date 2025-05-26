#pragma once
#include <iostream>
#include "Cartes.h"
#include <string>
#include <vector>
class Borne {
private:
	int iBORnuméro;
	std::vector<Cartes> vBORcartesJ1;
	std::vector<Cartes> vBORcartesJ2;
public:
	Borne();
	Borne(int numéro);
	int getnumero();
	void setnumero(int numéro);
	vector<Cartes> getCarteJ1();
	vector<Cartes> getCarteJ2();
	void ajouterCarteJ1(const Cartes& carte);
	void ajouterCarteJ2(const Cartes& carte);
};
