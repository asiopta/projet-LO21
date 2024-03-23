#pragma once
#include "game.h"

using namespace std;


/*-------------------------------------LES DEFINITION DES METHODES SONT A METTRE DANS LE .CPP-------------------------------------*/

//______________________________________________________________________________________________________________________________//
//les classes des cartes



//Definitions des methodes pour la classe Carte

//defconstructeur
// MANQUE LE CONSTUCTEUR DE CARTE
//Constructeur par défaut
//La classe Carte n'est de toute manière pas crée tel quelle carte c'est une classe abstraite, cad, tout les objets sont des les classes filles,
//il n'existe aucun objet n'appartenant pas a une fille

//methodes
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

//destructeur
Carte::~Carte(){};

//defintion de la fonction gettype() pour les classes carte polymorphiques

/*-------------------------------------MERVEILLE-------------------------------------*/
Merveille::Merveille(int age, RessourcePrimaire* matiere_primaire, RessourceSecondaire* matiere_secondaire, 
unsigned int pt_victoire, RessourcePrimaire* prod_primaire, RessourceSecondaire* prod_secondaire){
    this->age = age;
    this->pt_victoire = pt_victoire;
    this->materiauxPrimaires=matiere_primaire;
    this->materiauxSecondaires=matiere_secondaire;
    this->productionPrimaire=prod_primaire;
    this->productionSecondaire=prod_secondaire;
    // cout de construction à rajouter/ à calculer
}

Merveille::~Merveille(){};

/*------------------------------Cartes marrons---------------------------------------*/
CarteRessourcePrimaire::CarteRessourcePrimaire(int age, int cout_construction, RessourcePrimaire* prod_primaire){
    this->age = age;
    this->cout_construction = cout_construction;
    //this->production = prod_primaire; //erreur que j'ai pas compris!!
    this->materiauxPrimaires = NULL;
    this->materiauxSecondaires = NULL;
    
}

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

string CarteRessourcePrimaire::gettype() const{
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
 
int getCout(const Carte& carte, const Joueur& joueur, const Joueur& adversaire){
    if(carte.getMateriauxPrimaires()==NULL && carte.getMateriauxSecondaires()==NULL)
        return carte.getPrix();
    else{
        //créer une méthode qui retourne le nombre de cartes produisant une ressource donnée dans la classe joueur
        /*
        petit algo:
        cout = carte.monnaie
        pour chaque ressource nécessaires pour construire la carte:
            si le joueur produit la ressource:
                pass
            sinon:
                nb = cmbien de fois l'adversaire l'a produit //can be 0 or 1 or 2, etc
                cout+= 2+ nb;
        */
        unsigned int res = carte.getPrix();
        //une méthode qui renvoie cmbien de ressourcesPrim (et second) sont produites par une carte
        RessourcePrimaire* tab_prim = carte.getMateriauxPrimaires();
        while(tab_prim!=nullptr){
            

            tab_prim++;
        }
    }
}
 