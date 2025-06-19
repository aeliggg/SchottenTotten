#pragma once
#include "Partie.h"
#include <vector>
#include <memory>

class PartieTactique : public Partie {
public:
    PartieTactique();
    PartieTactique(Joueur* joueur1, Joueur* joueur2);

    bool jouer() override;
    void DistribuerCartes() override;

    // Vérifie les conditions spécifiques à la version tactique
    bool EstConditionTactiqueRemplie(const std::vector<std::shared_ptr<Carte>>& mainJoueur);

    void TourDePartie(int tour, std::vector<Borne>& bornes, Joueur* joueur, Joueur* adversaire, int numJoueur) override;
    void VerifieBorneRevendique(int choixBorne) override;
    void VerifieBorneGagnee(int choixBorne) override;

    // Piocher/remettre des cartes
    std::vector<std::shared_ptr<Carte>> piocherCartesHeros(int nb);
    std::vector<std::shared_ptr<Carte>> piocherCartesTactiques(int nb);
    void remettreCarteSousPiocheHeros(std::shared_ptr<Carte> carte);
    void remettreCarteSousPiocheTactique(std::shared_ptr<Carte> carte);

    // ✅ Gérer la défausse
    void ajouterADefausse(std::shared_ptr<Carte> carte);
    const std::vector<std::shared_ptr<Carte>>& getDefausse() const;

private:
    std::vector<std::shared_ptr<Carte>> piocheHeros;
    std::vector<std::shared_ptr<Carte>> piocheTactiques;
    std::vector<std::shared_ptr<Carte>> defausse; // ✅ Défausse
};
