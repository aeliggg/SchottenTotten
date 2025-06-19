#pragma once
#include <memory>
#include <string>
#include "CarteClassique.h"


class CarteTactique : public Carte {
public:

    std::string getCouleur() const override { return "tactique"; }
    bool estTactique() const override { return true; }
};


class CarteFactory {
public:
    static std::shared_ptr<Carte> creerCarte(const std::string& type, int numero = 0, const std::string& couleur = "");
};

class Banshee : public CarteTactique {
public:
    int getNumero() const override { return 0; }
    std::string getNom() const override { return "Banshee"; }
    void appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible = nullptr, int idJoueur = 0 ) override;
};


class ChasseurDeTete : public CarteTactique {
public:
    int getNumero() const override { return 0; }
    std::string getNom() const override { return "Chasseur de Tête"; }
    void appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible = nullptr, int idJoueur = 0) override;
};


class ColinMaillard : public CarteTactique {
public:
    int getNumero() const override { return 0; }
    std::string getNom() const override { return "Colin-Maillard"; }
    void appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur = 0 ) override;
};



class CombatDeBoue : public CarteTactique {
public:
    int getNumero() const override { return 0; }
    std::string getNom() const override { return "Combat de Boue"; }
    void appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur = 0) override;
};


class Espion : public CarteTactique {
public:
    int getNumero() const override { return 7; }
    std::string getNom() const override { return "Espion"; }
    void appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur = 0) override;
};


class Joker : public CarteTactique {
public:
    int getNumero() const override { return -1; }
    std::string getNom() const override { return "Joker"; }
    void appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur = 0) override;
};


class PorteBouclier : public CarteTactique {
public:
    int getNumero() const override { return -2; }
    std::string getNom() const override { return "Porte-Bouclier"; }
    void appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur = 0) override;

};

class Strategie : public CarteTactique {
public:
    int getNumero() const override { return 0; }
    std::string getNom() const override { return "Stratège"; }
    void appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur = 0) override;
};

class Traitre : public CarteTactique {
public:
    int getNumero() const override { return 0; }
    std::string getNom() const override { return "Traître"; }
    void appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur = 0) override;
};