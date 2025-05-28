#pragma once
#include <string>
#include <vector>
#include "Cartes.h"

class Joueur
{
private:
    std::string sJOUnom;
    std::vector<Cartes> vJOUCartesMain;
    int nbBorne;

public:
    Joueur();
    Joueur(const std::string& sNom);
    int getBorne() { return nbBorne; }
    void setBorne(int NewNbBorne) { nbBorne = NewNbBorne; }
    std::string getNom() const;
    void setNom(const std::string& nouveauNom);
    void ajouterCarte(const Cartes& carte);
    void retirerCarte(const Cartes& carte);
    const std::vector<Cartes>& getMain() const;
};
