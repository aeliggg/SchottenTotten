#include "CarteFactory.h"

std::unique_ptr<Carte> CarteFactory::creerCarte(const std::string& type, int numero, const std::string& couleur) {
    if (type == "classique")      return std::make_unique<CarteClassique>(numero, couleur);
    if (type == "joker")          return std::make_unique<Joker>();
    if (type == "espion")         return std::make_unique<Espion>();
    if (type == "portebouclier")  return std::make_unique<PorteBouclier>();
    if (type == "colinmaillard")  return std::make_unique<ColinMaillard>();
    if (type == "combatdeboue")   return std::make_unique<CombatDeBoue>();
    if (type == "chasseurdetete") return std::make_unique<ChasseurDeTete>();
    if (type == "strategie")      return std::make_unique<Strategie>();
    if (type == "banshee")        return std::make_unique<Banshee>();
    if (type == "traitre")        return std::make_unique<Traitre>();
    return nullptr;
}