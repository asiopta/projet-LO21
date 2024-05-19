#include "Joueur.h"
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include "Plateau.h"



/*-------------------------------------Plateau-------------------------------------*/

Plateau::Plateau(Joueur& joueur1, Joueur& joueur2){
    plateauCartes = new PlateauCartes();
    plateauScience = new PlateauScience();
    plateauMilitaire = new PlateauMilitaire(0, joueur1, joueur2);
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
    delete plateauCartes;
    delete plateauScience;
    delete plateauMilitaire;
}