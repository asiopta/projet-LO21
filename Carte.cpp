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
        if (i==1){throw "From Carte, set_materiaux_construction_secondaire : le tableau de ressource est déjà plein";}
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

std::ostream& Carte::operator<<(std::ostream& f) const{
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
        if (i==1){throw "From CarteRessourcePrimaire, set_production : le tableau de production est déjà plein";}
    }
}

/*--------------------------------------------------------------------------*/

/*------------------------------------Carte Ressource Secondaire--------------------------------------*/

CarteRessourceSecondaire::CarteRessourceSecondaire(unsigned int cout,RessourceSecondaire prod, RessourcePrimaire* pt_primaire, RessourceSecondaire* pt_secondaire, bool acc, bool fv, unsigned int pos)
: Carte(cout, pt_primaire, pt_secondaire, acc, fv, pos){
    production=prod;
}

CarteRessourceSecondaire::CarteRessourceSecondaire()
: Carte(){
    production=RessourceSecondaire::none;
}

//constructeur de recopie 
CarteRessourceSecondaire::CarteRessourceSecondaire(const CarteRessourceSecondaire &c)
: Carte(c){
    production= c.production;
}


void CarteRessourceSecondaire::set_production(RessourceSecondaire r){
    if (production == RessourceSecondaire::none){
        production = r;
    }
    else {throw "From CarteRessourceSecondaire, set_production : la production est renseignée";}
}



/*--------------------------------------------------------------------------*/

/*------------------------------------Cartes Commerce--------------------------------------*/

CarteCommerce::CarteCommerce()
:Carte(){
    production_primaire = new RessourcePrimaire[3];
    production_secondaire = new RessourceSecondaire[2];
    for(int i =0; i<3; i++){production_primaire[i]=RessourcePrimaire::none;}
    for(int i =0; i<2; i++){production_secondaire[i]=RessourceSecondaire::none;}

    capacite = Capacite::none;
    symbole = SymboleChainage::none;
    choix = false;
    contrepartie = false;
    pt_victoire = 0;
}

CarteCommerce::CarteCommerce(RessourcePrimaire* prod_primaire, RessourceSecondaire*prod_secondaire, Capacite capa, SymboleChainage symb, bool ch, bool cont, unsigned int pt_vict, unsigned int cout,RessourcePrimaire* pt_primaire, RessourceSecondaire* pt_secondaire, bool acc, bool fv, unsigned int pos)
:Carte(cout, pt_primaire, pt_secondaire, acc, fv, pos){
    production_primaire = new RessourcePrimaire[3];
    production_secondaire = new RessourceSecondaire[2];
    for(int i =0; i<3; i++){production_primaire[i]=prod_primaire[i];}
    for(int i =0; i<2; i++){production_secondaire[i]=prod_secondaire[i];}

    capacite = capa;
    symbole = symb;
    choix = ch;
    contrepartie = cont;
    pt_victoire = pt_vict;
}

CarteCommerce::CarteCommerce(const CarteCommerce& c)
:Carte(c){
    production_primaire = new RessourcePrimaire[3];
    production_secondaire = new RessourceSecondaire[2];
    for(int i =0; i<3; i++){production_primaire[i]=c.production_primaire[i];}
    for(int i =0; i<2; i++){production_secondaire[i]=c.production_secondaire[i];}

    capacite = c.capacite;
    symbole = c.symbole;
    choix = c.choix;
    contrepartie = c.contrepartie;
    pt_victoire = c.pt_victoire;
}

void CarteCommerce::set_production_primaire(RessourcePrimaire* pt){
    for(int i=0; i<3; i++){production_primaire[i]=pt[i];}
}
void CarteCommerce::set_production_secondaire(RessourceSecondaire* pt){
    for(int i=0; i<2; i++){production_secondaire[i]=pt[i];}
}

CarteCommerce::~CarteCommerce(){
    delete[] production_primaire;
    delete[] production_secondaire;
}


/*--------------------------------------------------------------------------*/

/*-------------------------------------CarteScience-------------------------------------*/

CarteScience::CarteScience() : Carte(){
        symbole_chainage = SymboleChainage::none;
        symbole_science = SymboleScience::balance;
        pt_victoire = 0;
        capacite = Capacite::ajouter_symbole_science;
    }
CarteScience::CarteScience(unsigned int cout, RessourcePrimaire* pt_primaire, RessourceSecondaire* pt_secondaire, bool acc, bool fv, unsigned int pos, SymboleChainage& symb_chain, SymboleScience& symb_science, unsigned int pt_vict)
    :Carte(cout, pt_primaire, pt_secondaire, acc, fv, pos){
        symbole_chainage = symb_chain;
        symbole_science = symb_science;
        pt_victoire = pt_vict;
        capacite = Capacite::ajouter_symbole_science;

    }
    //constructeur de recopie 
CarteScience::CarteScience(const CarteScience &c)
    :Carte(c){
        symbole_chainage = c.symbole_chainage;
        symbole_science = c.symbole_science;
        pt_victoire = c.pt_victoire;
        capacite = Capacite::ajouter_symbole_science;
    }

/*--------------------------------------------------------------------------*/


/*-------------------------------------CartePrestige-------------------------------------*/

CartePrestige::CartePrestige()
    :Carte(){
        symbole_chainage = SymboleChainage::none;
        pt_victoire = 0;
    }
CartePrestige::CartePrestige(unsigned int cout, RessourcePrimaire* pt_primaire, RessourceSecondaire* pt_secondaire, bool acc, bool fv, unsigned int pos, SymboleChainage& symb_chain, unsigned int pt_vict)
    :Carte(cout, pt_primaire, pt_secondaire, acc, fv, pos){
        symbole_chainage=symb_chain;
        pt_victoire=pt_vict;
    }

CartePrestige::CartePrestige(const CartePrestige& c)
    :Carte(c){
        symbole_chainage=c.symbole_chainage;
        pt_victoire=c.pt_victoire;
    }

/*--------------------------------------------------------------------------*/


/*-------------------------------------CarteMilitaire-------------------------------------*/

CarteMilitaire::CarteMilitaire()
    :Carte(){
    symbole_chainage = SymboleChainage::none;
    nb_symbole_militaire = 0;
    capacite = Capacite::avancee_militaire;
}
CarteMilitaire::CarteMilitaire(unsigned int cout, RessourcePrimaire* pt_primaire, RessourceSecondaire* pt_secondaire, bool acc, bool fv, unsigned int pos, SymboleChainage& symb_chain, unsigned int nb_militaire)
    :Carte(cout, pt_primaire, pt_secondaire, acc, fv, pos){
    symbole_chainage=symb_chain;
    nb_symbole_militaire=nb_militaire;
    capacite = Capacite::avancee_militaire;
}

CarteMilitaire::CarteMilitaire(const CarteMilitaire& c)
    :Carte(c){
        symbole_chainage=c.symbole_chainage;
        nb_symbole_militaire=c.nb_symbole_militaire;
        capacite = c.capacite;
}

/*--------------------------------------------------------------------------*/
