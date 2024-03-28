#pragma once
#include "Carte.h"


/*-------------------------------------CARTE-------------------------------------*/
Carte::Carte(){
    cout_construction =0;
    materiaux_construction_primaires = new RessourcePrimaire[4];
    materiaux_construction_secondaires = new RessourceSecondaire[2];

    for(int i=0; i<4; i++){materiaux_construction_primaires[i]=RessourcePrimaire::none;}
    for(int i=0; i<2; i++){materiaux_construction_secondaires[i]=RessourceSecondaire::none;}

    accessible = false;
    face_visible = false;
    position = 0;
}

Carte::Carte(unsigned int cout, RessourcePrimaire* pt_primaire, RessourceSecondaire* pt_secondaire, bool acc, bool fv, unsigned int pos){
    cout_construction = cout;
    materiaux_construction_primaires = new RessourcePrimaire[4];
    materiaux_construction_secondaires = new RessourceSecondaire[2];

    for(int i=0; i<4; i++){materiaux_construction_primaires[i]=pt_primaire[i];}
    for(int i=0; i<2; i++){materiaux_construction_secondaires[i]=pt_secondaire[i];}

    accessible = acc;
    face_visible = fv;
    position = pos;
}

Carte::Carte(const Carte &c){
    cout_construction = c.cout_construction;
    materiaux_construction_primaires = new RessourcePrimaire[4];
    materiaux_construction_secondaires = new RessourceSecondaire[2];

    for(int i=0; i<4; i++){materiaux_construction_primaires[i]=c.materiaux_construction_primaires[i];}
    for(int i=0; i<2; i++){materiaux_construction_secondaires[i]=c.materiaux_construction_secondaires[i];}

    accessible = c.accessible;
    face_visible = c.face_visible;
    position = c.position;
    
}

void Carte::set_position(unsigned int pos){
    if (pos>20) throw "set_position : erreur cette position n'existe pas dans un plateau normale";
    position=pos;
}

void Carte::set_materiaux_construction_primaire(RessourcePrimaire r){
    for(int i=0; i<4; i++){
        if (materiaux_construction_primaires[i] == RessourcePrimaire::none){
            materiaux_construction_primaires[i] = r;
            break;
        }
        if (i==3){throw "From Carte, set_materiaux_construction_primaire : le tableau de ressource est déjà plein";}
    }
} //cherche un emplacement ressource vide (none) puis le remplace, sort alors du for. 
//si on est pas sorti du for, cela veut dire que le tableau etait deja plein et ce n'est pas possible d'ajouter de nouvelles ressources nécéssaires

void Carte::set_materiaux_construction_secondaire(RessourceSecondaire r){
    for(int i=0; i<2; i++){
        if (materiaux_construction_secondaires[i] == RessourceSecondaire::none){
            materiaux_construction_secondaires[i] = r;
            break;
        }
        if (i==3){throw "From Carte, set_materiaux_construction_secondaire : le tableau de ressource est déjà plein";}
    }
} //cherche un emplacement ressource vide (none) puis le remplace, sort alors du for. 
//si on est pas sorti du for, cela veut dire que le tableau etait deja plein et ce n'est pas possible d'ajouter de nouvelles ressources nécéssaires
void Carte::set_accessible(){
    if (not(est_accessible())) accessible = true;
    else std::cout<< "rend_carte_accessible : La carte est déjà accessible." << std::endl;
}

void Carte::set_face_visible(){
    if (not(est_facevisible())) face_visible = true;
    else std::cout<< "rend_carte_accessible : La carte est déjà face visible." << std::endl;
}

Carte::~Carte(){
     delete[] materiaux_construction_primaires;
     delete[] materiaux_construction_secondaires;
}

std::ostream& Carte::operator<<(std::ostream f) const{
    std::cout << "--------Carte--------"<< std::endl;
    std::cout << "Cout construction : " << cout_construction << std::endl; 

    std::cout << "materiaux_construction_primaire : ";
    for(int i=0; i<4; i++){ 
        std::cout << materiaux_construction_primaires[i] << " ";
    }
    std::cout << "materiaux_construction_secondaire : ";
    for(int i=0; i<2; i++){
        std::cout << materiaux_construction_secondaires[i] << " ";
    }

    std::cout << "accessible : "<< accessible << std::endl; 
    std::cout << "face_visible" << face_visible << std::endl; 
    std::cout << "position" << position << std::endl; 
    
    RessourcePrimaire* materiaux_construction_primaires;
    RessourceSecondaire* materiaux_construction_secondaires;
    return f;

}

/*--------------------------------------------------------------------------*/


/*-------------------------------------CarteRessourcePrimaire-------------------------------------*/

//constructeur 
CarteRessourcePrimaire::CarteRessourcePrimaire(unsigned int cout,RessourcePrimaire* prod, RessourcePrimaire* pt_primaire, RessourceSecondaire* pt_secondaire, bool acc, bool fv, unsigned int pos)
: Carte(cout, pt_primaire, pt_secondaire, acc, fv, pos){
    production = new RessourcePrimaire[2]; //alloaction dynamique
    for(int i=0; i<2; i++){production[i]=prod[i];} //assigner les bonnes valeurs
}

CarteRessourcePrimaire::CarteRessourcePrimaire()
: Carte(){
    production = new RessourcePrimaire[2]; //alloaction dynamique
    for(int i=0; i<2; i++){production[i]=RessourcePrimaire::none;}
}

//constructeur de recopie 
CarteRessourcePrimaire::CarteRessourcePrimaire(const CarteRessourcePrimaire &c)
: Carte(c){
    production = new RessourcePrimaire[2];
    for(int i=0; i<2; i++){production[i]= c.production[i];}
}

//destructeur
CarteRessourcePrimaire::~CarteRessourcePrimaire(){
     delete[] production; // pas besoin de delete les autres tableau, car le destructeur de la class mère Carte va s'appeler et delete pour cette class
}

void CarteRessourcePrimaire::set_production(RessourcePrimaire r){
    for(int i=0; i<2; i++){
        if (production[i] == RessourcePrimaire::none){
            production[i] = r;
            break;
        }
        if (i==3){throw "From CarteRessourcePrimaire, set_production : le tableau de production est déjà plein";}
    }
}

/*--------------------------------------------------------------------------*/

/*------------------------------------Carte Ressource Secondaire--------------------------------------*/

