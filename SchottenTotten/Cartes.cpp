#include "Cartes.h"

Cartes::Cartes() : iCARnuméro(0), sCARcouleur("inconnue") {}

Cartes::Cartes(int numero, std::string couleur)
    : iCARnuméro(numero), sCARcouleur(couleur) {
}
