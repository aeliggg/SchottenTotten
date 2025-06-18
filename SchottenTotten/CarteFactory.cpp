#include "CarteFactory.h"

std::shared_ptr<Carte> CarteFactory::creerCarte(const std::string& type, int numero, const std::string& couleur) {
    if (type == "classique")      return std::make_shared<CarteClassique>(numero, couleur);
    if (type == "joker")          return std::make_shared<Joker>();
    if (type == "espion")         return std::make_shared<Espion>();
    if (type == "portebouclier")  return std::make_shared<PorteBouclier>();
    if (type == "colinmaillard")  return std::make_shared<ColinMaillard>();
    if (type == "combatdeboue")   return std::make_shared<CombatDeBoue>();
    if (type == "chasseurdetete") return std::make_shared<ChasseurDeTete>();
    if (type == "strategie")      return std::make_shared<Strategie>();
    if (type == "banshee")        return std::make_shared<Banshee>();
    if (type == "traitre")        return std::make_shared<Traitre>();
    return nullptr;
}
