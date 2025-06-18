#pragma once
#include <vector>
#include <memory>
#include "Carte.h"
class Partie;
class Joueur;

class Borne {
private:
    int iBORnuméro;
    Partie* BORpartie = nullptr;
    Joueur* GagnantBorne = nullptr;
    Joueur* FirstPlayer = nullptr;
    std::vector<std::shared_ptr<Carte>> vBORcartesJ1;
    std::vector<std::shared_ptr<Carte>> vBORcartesJ2;
    bool protegee = false;
    bool colinMaillard = false;
    bool combatDeBoue = false;
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
    const std::vector<std::shared_ptr<Carte>>& getCarteJ1() const;
    const std::vector<std::shared_ptr<Carte>>& getCarteJ2() const;
    void ajouterCarteJ1(std::shared_ptr<Carte> carte);
    void ajouterCarteJ2(std::shared_ptr<Carte> carte);
    bool operator<(const Borne& other) const;
    void viderCartes();
    bool estProtegeeParBouclier() const { return protegee; }
    void protegerParBouclier() { protegee = true; }
    void setColinMaillard(bool v) { colinMaillard = v; }
    void setCombatDeBoue(bool v) { combatDeBoue = v; }
    bool isColinMaillard() const { return colinMaillard; }
    bool isCombatDeBoue() const { return combatDeBoue; }
};