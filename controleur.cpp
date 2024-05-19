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

Plateau::~Plateau(){
    delete plateau_cartes;
    delete plateau_science;
    delete plateau_militaire;
}
bool Controleur::gagne(Joueur& joueur){
    bool victoireMilitaire = plateau.getPlateauMilitaire()->gagneMilitairement(joueur);
    bool victoireScience = 0 ;
    return victoireMilitaire || victoireScience;
}


bool Controleur::jeuEstFinie(){
    return plateau.isEtatFinal() || gagne(joueur1) || gagne(joueur2);
}

