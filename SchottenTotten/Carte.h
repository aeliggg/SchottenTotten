#pragma once
#include <string>

class Partie;
class Joueur;
class Borne;

class Carte {
public:
    virtual ~Carte() = default;
    virtual int getNumero() const = 0;
    virtual std::string getCouleur() const = 0;
    virtual std::string getNom() const = 0;
    virtual bool estTactique() const = 0;
    virtual void appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible = nullptr, int idJoueur = 0) = 0;
};