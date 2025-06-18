#include "CombatDeBoue.h"
#include "Borne.h"
void CombatDeBoue::appliquerEffet(Partie* partie, Joueur* joueur, Borne* cible) {
    if (cible) cible->setCombatDeBoue(true);
}