#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Carte.h"
#include "Borne.h"

class Joueur {
private:
    std::string sJOUnom;
    std::vector<std::shared_ptr<Carte>> vJOUCartesMain;
    std::vector<Borne> BorneGagnee;

public:
    Joueur();
    Joueur(const std::string& sNom);
    ~Joueur() = default;
    std::vector<Borne> getBorne();
    void setBorne(std::vector<Borne> NewBorne);
    void setMain(std::vector<std::shared_ptr<Carte>> nouvelleMain);
    void AjouterBorne(Borne NewNbBorne);
    std::string getNom() const;
    void setNom(const std::string& nouveauNom);
    void ajouterCarte(std::shared_ptr<Carte> carte);
    void retirerCarte(const Carte& carte);
    std::vector<std::shared_ptr<Carte>>& getMain();
    bool EstGagnant();
};