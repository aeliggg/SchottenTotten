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

    // Par exemple, vérifier si une condition tactique est remplie
    bool EstConditionTactiqueRemplie(const std::vector<std::shared_ptr<Carte>>& mainJoueur);

    // Gestion d’un tour tactique
    void TourDePartie(int tour, std::vector<Borne>& bornes, Joueur* joueur, Joueur* adversaire, int numJoueur) override;

    // Vérification des bornes tactiques revendiquées ou gagnées
    void VerifieBorneRevendique(int choixBorne) override;
    void VerifieBorneGagnee(int choixBorne) override;

    // Tour IA pour partie tactique
    //void TourDePartieIA(int tour, std::vector<Borne>& bornes, Joueur* IA, Joueur* adversaire, int numJoueur) override;

    std::vector<std::shared_ptr<Carte>> piocherCartesHeros(int nb);
    std::vector<std::shared_ptr<Carte>> piocherCartesTactiques(int nb);
    void remettreCarteSousPiocheHeros(std::shared_ptr<Carte> carte);
    void remettreCarteSousPiocheTactique(std::shared_ptr<Carte> carte);
private:
    std::vector<std::shared_ptr<Carte>> piocheHeros;
    std::vector<std::shared_ptr<Carte>> piocheTactiques;
};
