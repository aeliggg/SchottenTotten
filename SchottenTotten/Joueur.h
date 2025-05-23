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
    Joueur(std::string& sNom);

    std::string getNom();
    void setNom(std::string& nouveauNom);
    void ajouterCarte(Cartes& carte);
    void retirerCarte(int index);
    std::vector<Cartes> getMain();
};
