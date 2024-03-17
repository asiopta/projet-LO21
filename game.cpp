#pragma once
#include "game.h"

using namespace std;


/*-------------------------------------LES DEFINITION DES METHODES SONT A METTRE DANS LE .CPP-------------------------------------*/

//______________________________________________________________________________________________________________________________//
//les classes des cartes



//Definitions des methodes pour la classe Carte

//defconstructeur

void Carte::setAge(int newAge) {
    if (newAge >= 1 && newAge <= 3) {
        age = newAge;
    } else {
        cout<< "Error: Age must be 1, 2, or 3." << endl;
    }
}

int Carte::getAge() const {
    return age;
}



//defintion de la fonction gettype() pour les classes carte polymorphiques

string CarteCommerce::gettype() const {
    return "CarteCommerce";
}

string CarteGuilde::gettype() const {
    return "CarteGuilde";
}

string CarteMilitaire::gettype() const {
    return "CarteMilitaire";
}

string CartePrestige::gettype() const {
    return "CartePrestige";
}

string CarteRessourcePrimaire::gettype() const {
    return "CarteRessourcePrimaire";
}

string CarteRessourceSecondaire::gettype() const {
    return "CarteRessourceSecondaire";
}
string CarteScience::gettype() const {
    return "CarteScience";
}

string Merveille::gettype() const {
    return "Merveille";
}
