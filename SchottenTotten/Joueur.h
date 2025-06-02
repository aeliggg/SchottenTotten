#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "Cartes.h"
#include "Borne.h"

class Joueur
{
private:
    std::string sJOUnom;
    std::vector<Cartes> vJOUCartesMain;
    std::vector<Borne> BorneGagnee;

public:
    Joueur();
    Joueur(const std::string& sNom);
    vector<Borne> getBorne() { return BorneGagnee; }
    void setBorne(vector<Borne> NewBorne) {BorneGagnee=NewBorne ; }
    void setMain(const std::vector<Cartes>& nouvelleMain); 
    void AjouterBorne(Borne NewNbBorne);
    std::string getNom() const;
    void setNom(const std::string& nouveauNom);
    void ajouterCarte(const Cartes& carte);
    void retirerCarte(const Cartes& carte);
    const std::vector<Cartes>& getMain() const;
    bool EstGagnant();
};
