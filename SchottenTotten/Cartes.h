#pragma once
#include <string>
using namespace std;

class Cartes
{
private:
    int iCARnuméro;
    std::string sCARcouleur;
public:
    Cartes();
    Cartes(int iCARnuméro, std::string sCARcouleur);
    int getnumero() { return iCARnuméro; }
    std::string getcouleur() { return sCARcouleur; }
    void setnumero(int numero) {iCARnuméro = numero; }
    void setcouleur(std::string& couleur) { sCARcouleur = couleur; }
};

