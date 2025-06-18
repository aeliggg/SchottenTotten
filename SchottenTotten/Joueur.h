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
    std::vector<Carte> vJOUCartesMain;
    std::vector<Borne> BorneGagnee;

public:
    Joueur();
    Joueur(const std::string& sNom);
    ~Joueur() = default;
    std::vector<Borne> getBorne() { return BorneGagnee; }
    void setBorne(std::vector<Borne> NewBorne) {BorneGagnee=NewBorne ; }
    void setMain(const std::vector<Carte>& nouvelleMain); 
    void AjouterBorne(Borne NewNbBorne);
    std::string getNom() const;
    void setNom(const std::string& nouveauNom);
    void ajouterCarte(const Carte& carte);
    void retirerCarte(const Carte& carte);
    const std::vector<Carte>& getMain() const;
    bool EstGagnant();
};
