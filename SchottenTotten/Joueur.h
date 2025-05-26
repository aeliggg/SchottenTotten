#pragma once
#include <string>
#include <vector>
#include "Cartes.h"

class Joueur
{
private:
    std::string sJOUnom;
    std::vector<Cartes> vJOUCartesMain;

public:
    Joueur();
    Joueur(const std::string& sNom);

    std::string getNom() const;
    void setNom(const std::string& nouveauNom);
    void ajouterCarte(const Cartes& carte);
    void retirerCarte(int index);
    std::vector<Cartes> getMain() const;
};
