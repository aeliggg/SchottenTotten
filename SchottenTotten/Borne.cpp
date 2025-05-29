
#include "Borne.h"
#include "Partie.h"
Borne::Borne() : iBORnuméro(0) {}

Borne::Borne(int numéro) : iBORnuméro(numéro) {}

int Borne::getnumero() const {
    return iBORnuméro;
}

Joueur* Borne::getGagnant() const {
    return GagnantBorne; 
}

void Borne::setnumero(int numéro) {
    iBORnuméro = numéro;
}

std::vector<Cartes> Borne::getCarteJ1() const{
    return vBORcartesJ1;
}

std::vector<Cartes> Borne::getCarteJ2() const{
    return vBORcartesJ2;
}


void Borne::ajouterCarteJ1(const Cartes& carte) {
    if (vBORcartesJ1.size() < 3) {
        vBORcartesJ1.push_back(carte);
        BORpartie->getJoueur1()->retirerCarte(carte);
    }
    else {
        std::cout<<" deja 3 cartes sur la borne"<<std::endl;
    }
}

void Borne::ajouterCarteJ2(const Cartes& carte) {
    if (vBORcartesJ2.size() < 3) {
        vBORcartesJ2.push_back(carte);
        BORpartie->getJoueur2()->retirerCarte(carte);
    }
    else {
        std::cout << " deja 3 cartes sur la borne" << std::endl;
    }
}
