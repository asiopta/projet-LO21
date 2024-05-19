#include "Joueur.h"
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include "controleur.h"



/*-------------------------------------Plateau-------------------------------------*/

Plateau::Plateau(Joueur& joueur1, Joueur& joueur2){
    plateau_cartes = new PlateauCartes();
    plateau_science = new PlateauScience();
    plateau_militaire = new PlateauMilitaire(0, joueur1, joueur2);
}

bool Plateau::changerAge(){
    if (age < 3){
        this->getPlateauCartes()->addAge();
        age++;
        return true;
    }
    else {return false;}
}


Plateau::~Plateau(){
    delete plateau_cartes;
    delete plateau_science;
    delete plateau_militaire;
}