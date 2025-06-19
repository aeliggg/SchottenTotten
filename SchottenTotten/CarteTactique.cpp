#include "CarteTactique.h"
#include <iostream>
#include <string>
#include "Joueur.h"
#include "Borne.h" // Ajouté pour résoudre le problème
#include <algorithm>
#include "PartieTactique.h"
#include "Affichage.h"
#include <tuple>

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
    PartieTactique* partieTactique = dynamic_cast<PartieTactique*>(partie);
    if (!partieTactique) {
        std::cout << "Erreur : cette carte ne peut être jouée que dans une PartieTactique.\n";
        return;
    }

    if (cible->getGagnant() != nullptr) {
        std::cout << "Erreur : la borne est déjà revendiquée, impossible de jouer Banshee ici.\n";
        return;
    }

    std::cout << "Effet de Banshee : choisissez une carte adverse (Clan ou Tactique) sur la borne "
        << cible->getnumero() << " à défausser.\n";

    // Choix du côté adverse
    auto& cartesAdv = (idJoueur == 1) ? const_cast<std::vector<std::shared_ptr<Carte>>&>(cible->getCarteJ2())
        : const_cast<std::vector<std::shared_ptr<Carte>>&>(cible->getCarteJ1());

    if (cartesAdv.empty()) {
        std::cout << "Aucune carte adverse à défausser sur cette borne.\n";
        return;
    }

    // Afficher les cartes adverses disponibles
    std::cout << "Cartes adverses disponibles :\n";
    for (size_t i = 0; i < cartesAdv.size(); ++i) {
        std::cout << i + 1 << ". " << cartesAdv[i]->getNom() << "\n";
    }

    int choix;
    do {
        std::cout << "Choisissez une carte à défausser (1-" << cartesAdv.size() << ") : ";
        std::cin >> choix;
    } while (choix < 1 || choix >(int)cartesAdv.size());

    // Récupérer la carte choisie
    auto carteChoisie = cartesAdv[choix - 1];

    // Retirer la carte de la borne
    cartesAdv.erase(cartesAdv.begin() + (choix - 1));

    // Ajouter la carte à la défausse (face visible à côté de la pioche)
    partieTactique->ajouterADefausse(carteChoisie);

    std::cout << "Carte \"" << carteChoisie->getNom() << "\" défaussée.\n";
    std::cout << "Effet Banshee terminé.\n";
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



void ColinMaillard::appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur) {
    cible->setColinMaillard(true);
    std::cout << "Effet Colin-Maillard activé sur la borne " << cible->getnumero() << std::endl;
}


void CombatDeBoue::appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur) {
    cible->setCombatDeBoue(true);
    std::cout << "Effet Combat de Boue activé sur la borne " << cible->getnumero() << std::endl;
}


void Espion::appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur) {
    cible->setEspion();
    std::cout << "Effet Espion appliqué.\n";
}

void Joker::appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur) {
    std::cout << "Effet Joker appliqué.\n";
}

void PorteBouclier::appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur) {
    cible->setporteBouclier();
    std::cout << "Effet Porte-Bouclier appliqué.\n";
}

void Strategie::appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible, int idJoueur) {
    PartieTactique* partieTactique = dynamic_cast<PartieTactique*>(partie);
    if (!partieTactique) {
        std::cout << "Erreur : cette carte ne peut être jouée que dans une PartieTactique.\n";
        return;
    }

    auto& bornes = partieTactique->getBornes(); // Assure-toi que ça existe
    std::vector<std::tuple<int, int, std::shared_ptr<Carte>>> cartesDispo;

    // Étape 1 : lister les cartes éligibles du joueur sur bornes non revendiquées
    for (size_t i = 0; i < bornes.size(); ++i) {
        if (bornes[i].estRevendiquee()) continue;

        const auto& cartes = (idJoueur == 1) ? bornes[i].getCarteJ1() : bornes[i].getCarteJ2();
        for (size_t j = 0; j < cartes.size(); ++j) {
            auto carte = cartes[j];
            if (carte->estTactique() || !carte->estTactique()) { // Clan ou Tactique
                cartesDispo.emplace_back(i, j, carte);
            }
        }
    }

    if (cartesDispo.empty()) {
        std::cout << "Aucune carte déplaçable trouvée.\n";
        return;
    }

    // Étape 2 : affichage des cartes disponibles
    std::cout << "Cartes disponibles pour déplacement ou défausse :\n";
    for (size_t i = 0; i < cartesDispo.size(); ++i) {
        int borneIndex = std::get<0>(cartesDispo[i]);
        auto carte = std::get<2>(cartesDispo[i]);
        std::cout << i + 1 << ". " << carte->getNom()
                  << " (Borne " << borneIndex + 1 << ")\n";
    }

    int choix;
    do {
        std::cout << "Choisissez une carte (1-" << cartesDispo.size() << ") : ";
        std::cin >> choix;
    } while (choix < 1 || choix > (int)cartesDispo.size());

    int borneSourceIndex = std::get<0>(cartesDispo[choix - 1]);
    int carteIndex = std::get<1>(cartesDispo[choix - 1]);
    auto carteChoisie = std::get<2>(cartesDispo[choix - 1]);

    // Étape 3 : retirer la carte de la borne d’origine
    auto& cartesOrigine = (idJoueur == 1)
        ? const_cast<std::vector<std::shared_ptr<Carte>>&>(bornes[borneSourceIndex].getCarteJ1())
        : const_cast<std::vector<std::shared_ptr<Carte>>&>(bornes[borneSourceIndex].getCarteJ2());
    cartesOrigine.erase(cartesOrigine.begin() + carteIndex);

    // Étape 4 : choix entre déplacement ou défausse
    std::cout << "1. Déplacer vers une autre borne\n";
    std::cout << "2. Défausser la carte\n";
    int action;
    do {
        std::cout << "Votre choix : ";
        std::cin >> action;
    } while (action != 1 && action != 2);

    if (action == 1) {
        // Choisir une autre borne non revendiquée
        std::vector<int> bornesCibles;
        for (size_t i = 0; i < bornes.size(); ++i) {
            if (!bornes[i].estRevendiquee() && i != borneSourceIndex) {
                bornesCibles.push_back(i);
            }
        }

        if (bornesCibles.empty()) {
            std::cout << "Aucune autre borne disponible, carte défaussée.\n";
            partieTactique->ajouterADefausse(carteChoisie);
            return;
        }

        std::cout << "Bornes disponibles pour déplacement :\n";
        for (size_t i = 0; i < bornesCibles.size(); ++i) {
            std::cout << i + 1 << ". Borne " << bornesCibles[i] + 1 << "\n";
        }

        int choixBorne;
        do {
            std::cout << "Choisissez une borne : ";
            std::cin >> choixBorne;
        } while (choixBorne < 1 || choixBorne > (int)bornesCibles.size());

        int borneCibleIndex = bornesCibles[choixBorne - 1];
        if (idJoueur == 1)
            bornes[borneCibleIndex].ajouterCarteJ1(carteChoisie);
        else
            bornes[borneCibleIndex].ajouterCarteJ2(carteChoisie);

        std::cout << "Carte déplacée avec succès.\n";
    } else {
        partieTactique->ajouterADefausse(carteChoisie);
        std::cout << "Carte défaussée.\n";
    }

    std::cout << "Effet Stratège terminé.\n";
}

void Traitre::appliquerEffet(Partie* partie, Joueur* joueur, Borne* /*cible*/, int idJoueur) {
    PartieTactique* partieTactique = dynamic_cast<PartieTactique*>(partie);
    if (!partieTactique) {
        std::cout << "Erreur : cette carte ne peut être jouée que dans une PartieTactique.\n";
        return;
    }

    auto& bornes = partieTactique->getBornes();

    // 1) Trouver les bornes non revendiquées côté adverse avec au moins une carte Clan
    std::vector<std::tuple<int, int, std::shared_ptr<Carte>>> cartesAdversesClans; // (index borne, index carte, carte)
    for (size_t i = 0; i < bornes.size(); ++i) {
        if (bornes[i].getGagnant() != nullptr) continue; // borne revendiquée => skip

        // côté adverse
        const auto& cartesAdverse = (idJoueur == 1) ? bornes[i].getCarteJ2() : bornes[i].getCarteJ1();
        for (size_t j = 0; j < cartesAdverse.size(); ++j) {
            if (!cartesAdverse[j]->estTactique()) { // Clan = pas tactique
                cartesAdversesClans.push_back(std::make_tuple(i, j, cartesAdverse[j]));
            }
        }
    }

    if (cartesAdversesClans.empty()) {
        std::cout << "Aucune carte Clan adverse trouvée sur une borne non revendiquée.\n";
        return;
    }

    // Afficher cartes adverses Clan
    std::cout << "Cartes Clan adverses disponibles :\n";
    for (size_t i = 0; i < cartesAdversesClans.size(); ++i) {
        int borneIdx = std::get<0>(cartesAdversesClans[i]);
        int carteIdx = std::get<1>(cartesAdversesClans[i]);
        std::shared_ptr<Carte> carte = std::get<2>(cartesAdversesClans[i]);

        std::cout << i + 1 << ". " << carte->getNom() << " (Borne " << bornes[borneIdx].getnumero() << ")\n";
    }

    int choixCarte;
    do {
        std::cout << "Choisissez une carte à déplacer (1-" << cartesAdversesClans.size() << ") : ";
        std::cin >> choixCarte;
    } while (choixCarte < 1 || choixCarte >(int)cartesAdversesClans.size());

    int borneSourceIndex = std::get<0>(cartesAdversesClans[choixCarte - 1]);
    int carteIndex = std::get<1>(cartesAdversesClans[choixCarte - 1]);
    std::shared_ptr<Carte> carteChoisie = std::get<2>(cartesAdversesClans[choixCarte - 1]);

    // 2) Trouver les bornes non revendiquées côté joueur pour déplacer la carte
    std::vector<int> bornesJoueurDisponibles;
    for (size_t i = 0; i < bornes.size(); ++i) {
        if (bornes[i].getGagnant() != nullptr) continue; // revendiquée skip
        // côté joueur
        bornesJoueurDisponibles.push_back(i);
    }

    if (bornesJoueurDisponibles.empty()) {
        std::cout << "Aucune borne non revendiquée disponible côté joueur pour déplacer la carte.\n";
        return;
    }

    std::cout << "Bornes disponibles pour placer la carte :\n";
    for (size_t i = 0; i < bornesJoueurDisponibles.size(); ++i) {
        std::cout << i + 1 << ". Borne " << bornes[bornesJoueurDisponibles[i]].getnumero() << "\n";
    }

    int choixBorne;
    do {
        std::cout << "Choisissez une borne (1-" << bornesJoueurDisponibles.size() << ") : ";
        std::cin >> choixBorne;
    } while (choixBorne < 1 || choixBorne >(int)bornesJoueurDisponibles.size());

    int borneCibleIndex = bornesJoueurDisponibles[choixBorne - 1];

    // 3) Retirer la carte de la borne adverse
    auto& cartesSource = (idJoueur == 1)
        ? const_cast<std::vector<std::shared_ptr<Carte>>&>(bornes[borneSourceIndex].getCarteJ2())
        : const_cast<std::vector<std::shared_ptr<Carte>>&>(bornes[borneSourceIndex].getCarteJ1());
    cartesSource.erase(cartesSource.begin() + carteIndex);

    // 4) Ajouter la carte devant la borne du joueur
    if (idJoueur == 1)
        bornes[borneCibleIndex].ajouterCarteJ1(carteChoisie);
    else
        bornes[borneCibleIndex].ajouterCarteJ2(carteChoisie);

    std::cout << "Carte \"" << carteChoisie->getNom() << "\" déplacée avec succès.\n";
    std::cout << "Effet Traître terminé.\n";
}