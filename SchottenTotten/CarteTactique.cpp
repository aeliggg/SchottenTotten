#include "CarteTactique.h"
#include <iostream>
#include <string>
#include "Joueur.h"
#include "Borne.h" // Ajouté pour résoudre le problème
#include <algorithm>
#include "PartieTactique.h"
#include "Affichage.h"

// Implémentation de la fabrique
std::shared_ptr<Carte> CarteFactory::creerCarte(const std::string& type, int numero, const std::string& couleur) {
    if (type == "Banshee") {
        return std::make_shared<Banshee>();
    }
    else if (type == "ChasseurDeTete") {
        return std::make_shared<ChasseurDeTete>();
    }
    else if (type == "ColinMaillard") {
        return std::make_shared<ColinMaillard>();
    }
    else if (type == "CombatDeBoue") {
        return std::make_shared<CombatDeBoue>();
    }
    else if (type == "Espion") {
        return std::make_shared<Espion>();
    }
    else if (type == "Joker") {
        return std::make_shared<Joker>();
    }
    else if (type == "PorteBouclier") {
        return std::make_shared<PorteBouclier>();
    }
    else if (type == "Strategie") {
        return std::make_shared<Strategie>();
    }
    else if (type == "Traitre") {
        return std::make_shared<Traitre>();
    }
    return nullptr;
}

// Exemples d'effets (à compléter selon ta logique)

// Corrected code for Banshee::appliquerEffet
void Banshee::appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur) {
    std::cout << "Effet de Banshee : retirer la dernière carte de l’adversaire sur la borne "
        << cible->getnumero() << std::endl;

    // Si c’est le joueur 1, on retire une carte du joueur 2 (et inversement)
    auto& cartesAdv = (idJoueur == 1) ? cible->getCarteJ2() : cible->getCarteJ1();

    // Convert cartesAdv to a non-const reference
    auto& cartesAdvNonConst = const_cast<std::vector<std::shared_ptr<Carte>>&>(cartesAdv);

    if (!cartesAdvNonConst.empty()) {
        cartesAdvNonConst.pop_back();
        std::cout << "Carte adverse retirée.\n";
    }
    else {
        std::cout << "Aucune carte adverse à retirer.\n";
    }
}
 

void ChasseurDeTete::appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible , int idJoueur ) {
    PartieTactique* partieTactique = dynamic_cast<PartieTactique*>(partie);
    if (!partieTactique) {
        std::cout << "Erreur : partie non tactique.\n";
        return;
    }

    int nbHeros = 0, nbTactiques = 0;

    do {
        std::cout << "Combien de cartes voulez-vous piocher de la pioche HEROS ? ";
        std::cin >> nbHeros;
        std::cout << "Combien de cartes voulez-vous piocher de la pioche TACTIQUE ? ";
        std::cin >> nbTactiques;
        if (nbHeros + nbTactiques != 3) {
            std::cout << "Erreur : le total doit être exactement 3. Réessayez.\n";
        }
    } while (nbHeros + nbTactiques != 3);

    auto cartesHeros = partieTactique->piocherCartesHeros(nbHeros);
    auto cartesTactiques = partieTactique->piocherCartesTactiques(nbTactiques);

    auto& main = joueur->getMain();
    for (auto& c : cartesHeros) main.push_back(c);
    for (auto& c : cartesTactiques) main.push_back(c);

    std::cout << "Vous avez pioché " << cartesHeros.size() << " cartes HEROS et " << cartesTactiques.size() << " cartes TACTIQUE.\n";

    // Choix interactif de 2 cartes à remettre sous la pioche, avec navigation
    std::vector<int> choixIndices;
    for (int i = 0; i < 2; ++i) {
        int choix = AfficheChoixCarteNavigable(joueur, 0) - 1; // 0-based index

        // Eviter la même carte deux fois : on reprompt si déjà choisie
        while (std::find(choixIndices.begin(), choixIndices.end(), choix) != choixIndices.end()) {
            std::cout << "Carte déjà choisie, veuillez en choisir une autre.\n";
            choix = AfficheChoixCarteNavigable(joueur, 0) - 1;
        }
        choixIndices.push_back(choix);
    }

    // Trier indices en décroissant pour suppression propre
    std::sort(choixIndices.begin(), choixIndices.end(), std::greater<int>());

    for (int idx : choixIndices) {
        auto carte = main[idx];
        if (carte->estTactique()) {
            // Carte tactique
            partieTactique->remettreCarteSousPiocheTactique(carte);
            std::cout << "Carte " << carte->getNom() << " remise sous la pioche TACTIQUE.\n";
        }
        else {
            // Carte héros
            partieTactique->remettreCarteSousPiocheHeros(carte);
            std::cout << "Carte " << carte->getNom() << " remise sous la pioche HEROS.\n";
        }
        main.erase(main.begin() + idx);
    }

    std::cout << "Effet Chasseur de Tête terminé.\n";
}



void ColinMaillard::appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur = 0) {
    std::cout << "Effet Colin-Maillard appliqué.\n";
}

void CombatDeBoue::appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur = 0) {
    std::cout << "Effet Combat de Boue appliqué.\n";
}

void Espion::appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur = 0) {
    std::cout << "Choisissez la couleur pour l'Espion : ";
    std::string couleurChoisie;
    std::cin >> couleurChoisie;
    // Ici tu devrais stocker cette couleur dans un attribut (à ajouter dans ta classe)
    std::cout << "Couleur choisie : " << couleurChoisie << std::endl;


    // Ajouter la carte espion à la borne cible (exemple)
    if (cible) {
        // cible->ajouterCarte(joueur, shared_from_this());
        std::cout << "Espion posé sur la borne.\n";
    }
}

void Joker::appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur = 0) {
    std::cout << "Effet Joker appliqué.\n";
}

void PorteBouclier::appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur = 0) {
    std::cout << "Effet Porte-Bouclier appliqué.\n";
}

void Strategie::appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur = 0) {
    std::cout << "Effet Stratège appliqué.\n";
}

void Traitre::appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur = 0) {
    std::cout << "Effet Traître appliqué.\n";
}
