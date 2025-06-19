#pragma once
#include "Partie.h"
#include <vector>
#include <memory>
/*
class PartieTactique : public Partie {
public:
    PartieTactique();
    PartieTactique(Joueur* joueur1, Joueur* joueur2);

    bool jouer() override;
    void DistribuerCartes() override;

    void TourDePartie(int tour, std::vector<Borne>& bornes, Joueur* joueur, Joueur* adversaire, int numJoueur) override;
    void VerifieBorneRevendique(int choixBorne) override;
    void VerifieBorneGagnee(int choixBorne) override;

    // Piocher/remettre des cartes
    std::vector<std::shared_ptr<Carte>> piocherCartesHeros(int nb);
    std::vector<std::shared_ptr<Carte>> piocherCartesTactiques(int nb);
    void remettreCarteSousPiocheHeros(std::shared_ptr<Carte> carte);
    void remettreCarteSousPiocheTactique(std::shared_ptr<Carte> carte);

    // Gestion de la défausse
    void ajouterADefausse(std::shared_ptr<Carte> carte);
    const std::vector<std::shared_ptr<Carte>>& getDefausse() const;

    // Appliquer les valeurs choisies pour les cartes spéciales
    void appliquerValeursChoisies(std::vector<std::shared_ptr<Carte>>& cartes, Joueur* joueur);

    // Fonctions de combinaison
    bool EstSuite(const std::vector<std::shared_ptr<Carte>>& trio);
    bool EstCouleur(const std::vector<std::shared_ptr<Carte>>& trio);
    bool EstSuiteCouleur(const std::vector<std::shared_ptr<Carte>>& trio);
    bool EstBrelan(const std::vector<std::shared_ptr<Carte>>& trio);
    int calculValeurAvecCombinaisons(const std::vector<std::shared_ptr<Carte>>& trio);
    int getRangCombinaison(const std::vector<std::shared_ptr<Carte>>& trio);

    // Détermine le gagnant d'une borne
    bool EstGagnant(const std::vector<std::shared_ptr<Carte>>& trioJ1,
        const std::vector<std::shared_ptr<Carte>>& trioJ2,
        Joueur* J1, Joueur* J2,
        Joueur* firstJoueur);

private:
    std::vector<std::shared_ptr<Carte>> piocheHeros;
    std::vector<std::shared_ptr<Carte>> piocheTactiques;
    std::vector<std::shared_ptr<Carte>> defausse;
};
*/