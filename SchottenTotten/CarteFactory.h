#pragma once
#include <memory>
#include <string>
#include "CarteClassique.h"
#include "Joker.h"
#include "Espion.h"
#include "PorteBouclier.h"
#include "ColinMaillard.h"
#include "CombatDeBoue.h"
#include "ChasseurDeTete.h"
#include "Strategie.h"
#include "Banshee.h"
#include "Traitre.h"

class CarteFactory {
public:
    static std::shared_ptr<Carte> creerCarte(const std::string& type, int numero = 0, const std::string& couleur = "");
};