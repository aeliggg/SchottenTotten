#pragma once
#include "Cartes.h"

class CarteClassique : public Carte {
    int numero;
    std::string couleur;
public:
    CarteClassique(int n, const std::string& c) : numero(n), couleur(c) {}
    int getNumero() const override { return numero; }
    std::string getCouleur() const override { return couleur; }
    std::string getNom() const override { return "Classique"; }
    bool estTactique() const override { return false; }
};