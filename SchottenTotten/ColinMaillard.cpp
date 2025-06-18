#include "ColinMaillard.h"
#include "Borne.h"
void ColinMaillard::appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible) {
    if (cible) cible->setColinMaillard(true);
}