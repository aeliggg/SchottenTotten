#include "PartieTactique.h"
#include <algorithm>
#include <iostream>

/*

// Constructeurs
PartieTactique::PartieTactique() : Partie() {}

PartieTactique::PartieTactique(Joueur* j1, Joueur* j2) : Partie(j1, j2) {}

// Distribution des cartes (exemple basique)
void PartieTactique::DistribuerCartes() {
    // Exemple: pioche 7 cartes héros par joueur
    joueur1->setMain(piocherCartesHeros(7));
    joueur2->setMain(piocherCartesHeros(7));
}

// Piocher cartes héros
std::vector<std::shared_ptr<Carte>> PartieTactique::piocherCartesHeros(int nb) {
    std::vector<std::shared_ptr<Carte>> cartes;
    for (int i = 0; i < nb && !piocheHeros.empty(); i++) {
        cartes.push_back(piocheHeros.back());
        piocheHeros.pop_back();
    }
    return cartes;
}

// Piocher cartes tactiques
std::vector<std::shared_ptr<Carte>> PartieTactique::piocherCartesTactiques(int nb) {
    std::vector<std::shared_ptr<Carte>> cartes;
    for (int i = 0; i < nb && !piocheTactiques.empty(); i++) {
        cartes.push_back(piocheTactiques.back());
        piocheTactiques.pop_back();
    }
    return cartes;
}

void PartieTactique::remettreCarteSousPiocheHeros(std::shared_ptr<Carte> carte) {
    piocheHeros.insert(piocheHeros.begin(), carte);
}

void PartieTactique::remettreCarteSousPiocheTactique(std::shared_ptr<Carte> carte) {
    piocheTactiques.insert(piocheTactiques.begin(), carte);
}

void PartieTactique::ajouterADefausse(std::shared_ptr<Carte> carte) {
    defausse.push_back(carte);
}

const std::vector<std::shared_ptr<Carte>>& PartieTactique::getDefausse() const {
    return defausse;
}

// --- Fonctions Combinaisons ---

bool PartieTactique::EstSuite(const std::vector<std::shared_ptr<Carte>>& trio) {
    std::vector<int> valeurs;
    for (auto& c : trio) valeurs.push_back(c->getValeurChoisie());
    std::sort(valeurs.begin(), valeurs.end());
    return (valeurs[1] == valeurs[0] + 1) && (valeurs[2] == valeurs[1] + 1);
}

bool PartieTactique::EstCouleur(const std::vector<std::shared_ptr<Carte>>& trio) {
    Couleur couleur = trio[0]->getCouleurChoisie();
    return std::all_of(trio.begin(), trio.end(), [&](const std::shared_ptr<Carte>& c) {
        return c->getCouleurChoisie() == couleur;
        });
}

bool PartieTactique::EstSuiteCouleur(const std::vector<std::shared_ptr<Carte>>& trio) {
    return EstSuite(trio) && EstCouleur(trio);
}

bool PartieTactique::EstBrelan(const std::vector<std::shared_ptr<Carte>>& trio) {
    int v = trio[0]->getValeurChoisie();
    return std::all_of(trio.begin(), trio.end(), [&](const std::shared_ptr<Carte>& c) {
        return c->getValeurChoisie() == v;
        });
}

int PartieTactique::calculValeurAvecCombinaisons(const std::vector<std::shared_ptr<Carte>>& trio) {
    int somme = 0;
    for (const auto& carte : trio) {
        somme += carte->getValeurChoisie();
    }
    return somme;
}

int PartieTactique::getRangCombinaison(const std::vector<std::shared_ptr<Carte>>& trio) {
    if (EstSuiteCouleur(trio)) return 5;
    if (EstBrelan(trio)) return 4;
    if (EstCouleur(trio)) return 3;
    if (EstSuite(trio)) return 2;
    return 1;
}

bool PartieTactique::EstGagnant(
    const std::vector<std::shared_ptr<Carte>>& trioJ1,
    const std::vector<std::shared_ptr<Carte>>& trioJ2,
    Joueur* J1,
    Joueur* J2,
    Joueur* firstJoueur)
{
    int rangJ1 = getRangCombinaison(trioJ1);
    int rangJ2 = getRangCombinaison(trioJ2);

    if (rangJ1 > rangJ2) return true;
    if (rangJ1 < rangJ2) return false;

    int sommeJ1 = calculValeurAvecCombinaisons(trioJ1);
    int sommeJ2 = calculValeurAvecCombinaisons(trioJ2);

    if (sommeJ1 > sommeJ2) return true;
    if (sommeJ1 < sommeJ2) return false;

    return (firstJoueur == J1);
}

// Vérification revendication Borne avec cartes spéciales
void PartieTactique::VerifieBorneRevendique(int choixBorne) {
    int indexBorne = 0;
    while (bornes[indexBorne].getnumero() != choixBorne) {
        indexBorne++;
    }
    Borne& borne = bornes[indexBorne];
    auto& cartesJ1 = borne.getCarteJ1();
    auto& cartesJ2 = borne.getCarteJ2();

    int valeurJ1 = 0;
    int valeurJ2 = 0;

    // Cas CombatDeBoue : calcule somme simple
    if (borne.isCombatDeBoue()) {
        for (const auto& c : cartesJ1) valeurJ1 += c->getValeurChoisie();
        for (const auto& c : cartesJ2) valeurJ2 += c->getValeurChoisie();
    }
    else {
        valeurJ1 = calculValeurAvecCombinaisons(cartesJ1);
        valeurJ2 = calculValeurAvecCombinaisons(cartesJ2);
    }

    // Conditions de revendication : 3 cartes minimum de chaque côté
    bool j1Peut = cartesJ1.size() == 3;
    bool j2Peut = cartesJ2.size() == 3;

    if (j1Peut && EstGagnant(cartesJ1, cartesJ2, joueur1, joueur2, borne.getFirst())) {
        borne.setGagnant(joueur1);
        joueur1->AjouterBorne(borne);
        std::cout << "\nRevendication par " << joueur1->getNom() << " sur la borne " << borne.getnumero() << " validée !" << std::endl;
    }
    else if (j2Peut && EstGagnant(cartesJ2, cartesJ1, joueur2, joueur1, borne.getFirst())) {
        borne.setGagnant(joueur2);
        joueur2->AjouterBorne(borne);
        std::cout << "\nRevendication par " << joueur2->getNom() << " sur la borne " << borne.getnumero() << " validée !" << std::endl;
    }
    else {
        std::cout << "\nVous ne pouvez pas revendiquer cette borne.\n";
    }
}
void PartieTactique::appliquerValeursChoisies(std::vector<std::shared_ptr<Carte>>& cartes, Joueur* joueur) {
    for (auto& carte : cartes) {
        if (carte->estJoker()) {
            // Joker : le joueur choisit valeur (1-10 par exemple) et couleur
            int valeurChoisie = joueur->choisirValeur(1, 10, "Choisissez la valeur du Joker (1-10) : ");
            Couleur couleurChoisie = joueur->choisirCouleur("Choisissez la couleur du Joker : ");
            carte->setValeur(valeurChoisie);
            carte->setCouleurChoisie(couleurChoisie);
        }
        else if (carte->estPorteBouclier()) {
            // PorteBouclier : valeur entre 1 et 3, couleur
            int valeurChoisie = joueur->choisirValeur(1, 3, "Choisissez la valeur du PorteBouclier (1-3) : ");
            Couleur couleurChoisie = joueur->choisirCouleur("Choisissez la couleur du PorteBouclier : ");
            carte->setValeurChoisie(valeurChoisie);
            carte->setCouleurChoisie(couleurChoisie);
        }
        else if (carte->estEspion()) {
            // Espion : valeur fixe 7, couleur choisie par joueur
            int valeurChoisie = 7;
            Couleur couleurChoisie = joueur->choisirCouleur("Choisissez la couleur de l'Espion : ");
            carte->setValeurChoisie(valeurChoisie);
            carte->setCouleurChoisie(couleurChoisie);
        }
        else {
            // Carte normale, valeur/couleur d'origine
            carte->setValeurChoisie(carte->getValeur());
            carte->setCouleurChoisie(carte->getCouleur());
        }
    }
}
}
*/