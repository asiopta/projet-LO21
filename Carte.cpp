#pragma once
#include "Carte.h"
#include <iostream>
#include <string>




/*-------------------------------------Enumerations-------------------------------------*/

std::ostream& operator<<(std::ostream& f, const RessourcePrimaire& r){
    switch (r){
        case RessourcePrimaire::bois: f<<"bois"; break;
        case RessourcePrimaire::pierre: f<<"pierre"; break;
        case RessourcePrimaire::brique: f<<"brique"; break;
        case RessourcePrimaire::none: f<<"none"; break;
    }
    return f;
}

std::ostream& operator<<(std::ostream& f, const RessourceSecondaire& r){
    switch (r){
        case RessourceSecondaire::verre: f<<"verre"; break;
        case RessourceSecondaire::parchemin: f<<"parchemin"; break;
        case RessourceSecondaire::none: f<<"none"; break;
    }
    return f;
}

std::ostream& operator<<(std::ostream& f, const SymboleChainage& symbole) {
    switch (symbole) {
        case SymboleChainage::none:f << "Pas de symbole Chainage";
        case SymboleChainage::jarre:f << "Jarre"; break;
        case SymboleChainage::toneau:f << "Tonneau"; break;
        case SymboleChainage::masque:f << "Masque"; break;
        case SymboleChainage::temple: f << "Temple"; break;
        case SymboleChainage::soleil: f << "Soleil"; break;
        case SymboleChainage::goute: f << "Goutte"; break;
        case SymboleChainage::lune: f << "Lune"; break;
        case SymboleChainage::pilier: f << "Pilier"; break;
        case SymboleChainage::cible: f << "Cible"; break;
        case SymboleChainage::casque: f << "Casque"; break;
        case SymboleChainage::fer_a_cheval: f << "Fer à Cheval";break;
        case SymboleChainage::epee: f << "Epée"; break;
        case SymboleChainage::tour: f << "Tour"; break;
        case SymboleChainage::lyre: f << "Lyre"; break;
        case SymboleChainage::engrenage: f << "Engrenage"; break;
        case SymboleChainage::livre: f << "Livre"; break;
        case SymboleChainage::lampe: f << "Lampe"; break;
        default:
            f.setstate(std::ios_base::failbit);
    }
    return f;
}

std::ostream& operator<<(std::ostream& f, const SymboleScience& symbole) {
    switch (symbole) {
        case SymboleScience::roue: f << "Roue"; break;
        case SymboleScience::plume: f << "Plume"; break;
        case SymboleScience::pilon: f << "Pilon"; break;
        case SymboleScience::balance: f << "Balance"; break;
        case SymboleScience::globe_terrestre: f << "Globe terrestre"; break;
        case SymboleScience::fil_a_plomb: f << "Fil à plomb"; break;
        case SymboleScience::bateau: f << "Bateau"; break;
        default:
            f.setstate(std::ios_base::failbit);
    }
    return f;
}

std::ostream& operator<<(std::ostream& f, const EffetGuilde& effet) {
    switch (effet) {
        case EffetGuilde::guilde_armateurs: f << "Guilde des Armateurs"; break;
        case EffetGuilde::guilde_batisseurs: f << "Guilde des Bâtisseurs"; break;
        case EffetGuilde::guilde_commercants: f << "Guilde des Commerçants"; break;
        case EffetGuilde::guilde_magistrats: f << "Guilde des Magistrats"; break;
        case EffetGuilde::guilde_tacticiens: f << "Guilde des Tacticiens"; break;
        case EffetGuilde::guilde_scientifiques: f << "Guilde des Scientifiques"; break;
        case EffetGuilde::guilde_usuriers: f << "Guilde des Usuriers"; break;
        default:
            f.setstate(std::ios_base::failbit);
    }
    return f;
}

std::ostream& operator<<(std::ostream& f, const Capacite& capacite) {
    switch (capacite) {
        case Capacite::none: f<<"Pas de capacité"; break;
        case Capacite::rejouer: f << "Rejouer"; break;
        case Capacite::detruire_carte_marron: f << "Détruire une carte marron"; break;
        case Capacite::detruire_carte_grise: f << "Détruire une carte grise"; break;
        case Capacite::jouer_carte_defausse: f << "Jouer une carte de la défausse"; break;
        case Capacite::avancee_militaire: f << "Avancée militaire"; break;
        case Capacite::choisir_jeton_science: f << "Choisir un jeton science"; break;
        case Capacite::ajouter_symbole_science: f << "Ajouter un symbole science"; break;
        default:
            f.setstate(std::ios_base::failbit);
    }
    return f;
}




/*-------------------------------------CARTE-------------------------------------*/
Carte::Carte(){
    cout_construction =0;
    materiaux_construction_primaires = new RessourcePrimaire[Taille_cout_primaire];
    materiaux_construction_secondaires = new RessourceSecondaire[Taille_cout_secondaire];

    for(int i=0; i<Taille_cout_primaire; i++){materiaux_construction_primaires[i]=RessourcePrimaire::none;}
    for(int i=0; i<Taille_cout_secondaire; i++){materiaux_construction_secondaires[i]=RessourceSecondaire::none;}

    accessible = false;
    face_visible = false;
    position = 0;
}

Carte::Carte(std::string n,unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc, bool fv, unsigned int pos){
    cout_construction = cout;
    materiaux_construction_primaires = new RessourcePrimaire[Taille_cout_primaire];
    materiaux_construction_secondaires = new RessourceSecondaire[Taille_cout_secondaire];

            // Allocation dynamique et initialisation des ressources primaires
        materiaux_construction_primaires = new RessourcePrimaire[Taille_cout_primaire];
        int i = 0;
        for (const auto& ressource : pt_primaire) {
            if (i < Taille_cout_primaire) {
                materiaux_construction_primaires[i++] = ressource;
            }
        }

        // Allocation dynamique et initialisation des ressources secondaires
        materiaux_construction_secondaires = new RessourceSecondaire[Taille_cout_secondaire];
        i = 0;
        for (const auto& ressource : pt_secondaire) {
            if (i < Taille_cout_secondaire) {
                materiaux_construction_secondaires[i++] = ressource;
            }
        }

    accessible = acc;
    face_visible = fv;
    position = pos;
}

Carte::Carte(const Carte &c){
    age = c.age;
    nom = c.nom;
    cout_construction = c.cout_construction;
    materiaux_construction_primaires = new RessourcePrimaire[Taille_cout_primaire];
    materiaux_construction_secondaires = new RessourceSecondaire[Taille_cout_secondaire];

    for(int i=0; i<Taille_cout_primaire; i++){materiaux_construction_primaires[i]=c.materiaux_construction_primaires[i];}
    for(int i=0; i<Taille_cout_secondaire; i++){materiaux_construction_secondaires[i]=c.materiaux_construction_secondaires[i];}

    accessible = c.accessible;
    face_visible = c.face_visible;
    position = c.position;

}

void Carte::set_position(unsigned int pos){
    if (pos>20) throw "set_position : erreur cette position n'existe pas dans un plateau normale";
    position=pos;
}

void Carte::set_materiaux_construction_primaire(RessourcePrimaire r){
    for(int i=0; i<Taille_cout_primaire; i++){
        if (materiaux_construction_primaires[i] == RessourcePrimaire::none){
            materiaux_construction_primaires[i] = r;
            break;
        }
        if (i==3){throw "From Carte, set_materiaux_construction_primaire : le tableau de ressource est déjà plein";}
    }
} //cherche un emplacement ressource vide (none) puis le remplace, sort alors du for.
//si on est pas sorti du for, cela veut dire que le tableau etait deja plein et ce n'est pas possible d'ajouter de nouvelles ressources nécéssaires

void Carte::set_materiaux_construction_secondaire(RessourceSecondaire r){
    for(int i=0; i<Taille_cout_secondaire; i++){
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

unsigned int Carte::getQuantiteDeRessourcePrimaire(const RessourcePrimaire& symbole,RessourcePrimaire* Resp) const {
        unsigned int res=0;
        while(Resp != nullptr){
            if(*Resp == symbole) res++;
            Resp++;
        }
        return res;
};

unsigned int Carte::getQuantiteDeRessourceSecondaire(const RessourceSecondaire& symbole,RessourceSecondaire* ResS) const {
    unsigned int res=0;
    while(ResS != nullptr){
        if(*ResS == symbole) res++;
        ResS++;
    }
    return res;
};

unsigned int Carte::getQuantRessPrimNess(RessourcePrimaire rp) const{
    unsigned int res = 0;
    for(int i=0; i<Taille_cout_primaire; i++){
        if (materiaux_construction_primaires[i] == rp) res++;
    }
    return res;
}

unsigned int Carte::getQuantRessSecondNess(RessourceSecondaire rs) const{
    unsigned int res = 0;
    for(int i=0; i<Taille_cout_secondaire; i++){
        if (materiaux_construction_secondaires[i] == rs) res++;
    }
    return res;
}


Carte::~Carte(){
     delete[] materiaux_construction_primaires;
     delete[] materiaux_construction_secondaires;
}

std::ostream& Carte::operator<<(std::ostream& f) const{
    std::cout << "--------Carte--------"<< std::endl;
    std::cout << "Cout construction : " << cout_construction << std::endl;

    std::cout << "materiaux_construction_primaire : ";
    for(int i=0; i<Taille_cout_primaire; i++){
        std::cout << materiaux_construction_primaires[i] << " ";
    }
    std::cout << "materiaux_construction_secondaire : ";
    for(int i=0; i<Taille_cout_secondaire; i++){
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
CarteRessourcePrimaire::CarteRessourcePrimaire(std::string n,unsigned int a, unsigned int cout,std::initializer_list<RessourcePrimaire> prod, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc, bool fv, unsigned int pos)
: Carte(n,a, cout, pt_primaire, pt_secondaire, acc, fv, pos){
    production = new RessourcePrimaire[Taille_prod_primaire]; //alloaction dynamique
    int i = 0;
    for (const auto& prod : prod){
        if (i < Taille_prod_primaire) {
            production[i++] = prod;
        }
    }
}

CarteRessourcePrimaire::CarteRessourcePrimaire()
: Carte(){
    production = new RessourcePrimaire[Taille_prod_primaire]; //alloaction dynamique
    for(int i=0; i<Taille_prod_primaire; i++){production[i]=RessourcePrimaire::none;}
}

//constructeur de recopie
CarteRessourcePrimaire::CarteRessourcePrimaire(const CarteRessourcePrimaire &c)
: Carte(c){
    production = new RessourcePrimaire[Taille_prod_primaire];
    for(int i=0; i<Taille_prod_primaire; i++){production[i]= c.production[i];}
}

//destructeur
CarteRessourcePrimaire::~CarteRessourcePrimaire(){
     delete[] production; // pas besoin de delete les autres tableau, car le destructeur de la class mère Carte va s'appeler et delete pour cette class
}

void CarteRessourcePrimaire::set_production(RessourcePrimaire r){
    for(int i=0; i<Taille_prod_primaire; i++){
        if (production[i] == RessourcePrimaire::none){
            production[i] = r;
            break;
        }
        if (i==1){throw "From CarteRessourcePrimaire, set_production : le tableau de production est déjà plein";}
    }
}

unsigned int CarteRessourcePrimaire::getQuantRessPrimProd(RessourcePrimaire rp) const{
    unsigned int res = 0;
    for(int i=0; i<Taille_prod_primaire; i++){
        if (production[i] == rp) res++;
    }
    return res;
}


/*--------------------------------------------------------------------------*/

/*------------------------------------Carte Ressource Secondaire--------------------------------------*/

CarteRessourceSecondaire::CarteRessourceSecondaire(std::string n,unsigned int a, unsigned int cout,RessourceSecondaire prod, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc, bool fv, unsigned int pos)
: Carte(n,a, cout, pt_primaire, pt_secondaire, acc, fv, pos){
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

unsigned int CarteRessourceSecondaire::getQuantRessSecondProd(RessourceSecondaire rs) const{
    if (production == rs) return 1;
    else return 0;
}


/*--------------------------------------------------------------------------*/

/*------------------------------------Cartes Commerce--------------------------------------*/

CarteCommerce::CarteCommerce()
:Carte(){
    production_primaire = new RessourcePrimaire[Taille_cout_primaire];
    production_secondaire = new RessourceSecondaire[Taille_cout_secondaire];
    for(int i =0; i<Taille_cout_primaire; i++){production_primaire[i]=RessourcePrimaire::none;}
    for(int i =0; i<Taille_cout_secondaire; i++){production_secondaire[i]=RessourceSecondaire::none;}

    capacite = Capacite::none;
    symbole_chainage_entre = SymboleChainage::none;
    symbole_chainage_sortie = SymboleChainage::none;
    choix = false;
    contrepartie = false;
    pt_victoire = 0;
}

CarteCommerce::CarteCommerce(std::initializer_list<RessourcePrimaire> prod_primaire, std::initializer_list<RessourceSecondaire> prod_secondaire, Capacite capa, SymboleChainage symb_entre,SymboleChainage symb_sortie, bool ch, bool cont, unsigned int pt_vict,std::string n,unsigned int a, unsigned int cout,std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc, bool fv, unsigned int pos)
:Carte(n,a, cout, pt_primaire, pt_secondaire, acc, fv, pos){
    production_primaire = new RessourcePrimaire[Taille_prod_primaire];
    production_secondaire = new RessourceSecondaire[Taille_prod_secondaire];

    int i = 0;
    for (const auto& prod : prod_primaire){
        if (i < Taille_prod_primaire) {
            production_primaire[i++] = prod;
        }
    }
    i = 0;
    for (const auto& prod : prod_secondaire){
        if (i < Taille_prod_secondaire) {
            production_secondaire[i++] = prod;
        }
    }

    capacite = capa;
    symbole_chainage_entre = symb_entre;
    symbole_chainage_sortie = symb_sortie;

    choix = ch;
    contrepartie = cont;
    pt_victoire = pt_vict;
}

CarteCommerce::CarteCommerce(const CarteCommerce& c)
:Carte(c){
    production_primaire = new RessourcePrimaire[Taille_prod_primaire];
    production_secondaire = new RessourceSecondaire[Taille_prod_secondaire];
    for(int i =0; i<Taille_prod_primaire; i++){production_primaire[i]=c.production_primaire[i];}
    for(int i =0; i<Taille_prod_secondaire; i++){production_secondaire[i]=c.production_secondaire[i];}

    capacite = c.capacite;
    symbole_chainage_entre = c.symbole_chainage_entre;
    symbole_chainage_sortie = c.symbole_chainage_sortie;
    choix = c.choix;
    contrepartie = c.contrepartie;
    pt_victoire = c.pt_victoire;
}

void CarteCommerce::set_production_primaire(RessourcePrimaire* pt){
    for(int i=0; i<Taille_cout_primaire; i++){production_primaire[i]=pt[i];}
}
void CarteCommerce::set_production_secondaire(RessourceSecondaire* pt){
    for(int i=0; i<Taille_cout_secondaire; i++){production_secondaire[i]=pt[i];}
}

unsigned int CarteCommerce::getQuantRessPrimProd(RessourcePrimaire rp) const{
    unsigned int res = 0;
    for(int i=0; i<Taille_prod_primaire; i++){
        if (production_primaire[i] == rp) res++;
    }
    return res;
}
unsigned int CarteCommerce::getQuantRessSecondProd(RessourceSecondaire rs) const{
    unsigned int res = 0;
    for(int i=0; i<Taille_prod_secondaire; i++){
        if (production_secondaire[i] == rs) res++;
    }
    return res;
}

CarteCommerce::~CarteCommerce(){
    delete[] production_primaire;
    delete[] production_secondaire;
}


/*--------------------------------------------------------------------------*/

/*-------------------------------------CarteScience-------------------------------------*/

CarteScience::CarteScience() : Carte(){
        symbole_chainage_entre = SymboleChainage::none;
        symbole_chainage_sortie = SymboleChainage::none;
        symbole_science = SymboleScience::balance;
        pt_victoire = 0;
        capacite = Capacite::ajouter_symbole_science;
    }
CarteScience::CarteScience(std::string n,unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, SymboleChainage symb_chain_entre, SymboleChainage symb_chain_sortie, SymboleScience symb_science, unsigned int pt_vict)
    :Carte(n,a, cout, pt_primaire, pt_secondaire, false, false, 0){
        symbole_chainage_entre = symb_chain_entre;
        symbole_chainage_sortie = symb_chain_sortie;

        symbole_science = symb_science;
        pt_victoire = pt_vict;
        capacite = Capacite::ajouter_symbole_science;

    }
    //constructeur de recopie
CarteScience::CarteScience(const CarteScience &c)
    :Carte(c){
        symbole_chainage_entre = c.symbole_chainage_entre;
        symbole_chainage_sortie = c.symbole_chainage_sortie;
        symbole_science = c.symbole_science;
        pt_victoire = c.pt_victoire;
        capacite = Capacite::ajouter_symbole_science;
    }

void CarteScience::exec_capacite(Joueur& joueur1) const{
    joueur1.addSymboleScience(symbole_science); //error résolu
}

/*--------------------------------------------------------------------------*/


/*-------------------------------------CartePrestige-------------------------------------*/

CartePrestige::CartePrestige()
    :Carte(){
        symbole_chainage_entre = SymboleChainage::none;
        symbole_chainage_sortie = SymboleChainage::none;
        pt_victoire = 0;
    }
CartePrestige::CartePrestige(std::string n,unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, SymboleChainage symb_chain_entre,SymboleChainage symb_chain_sortie, unsigned int pt_vict)
    :Carte(n,a, cout, pt_primaire, pt_secondaire, false, false, 0){
        symbole_chainage_entre=symb_chain_entre;
        symbole_chainage_sortie=symb_chain_sortie;
        pt_victoire=pt_vict;
    }

CartePrestige::CartePrestige(const CartePrestige& c)
    :Carte(c){
        symbole_chainage_entre=c.symbole_chainage_entre;
        symbole_chainage_sortie=c.symbole_chainage_sortie;
        pt_victoire=c.pt_victoire;
    }

/*--------------------------------------------------------------------------*/


/*-------------------------------------CarteMilitaire-------------------------------------*/

CarteMilitaire::CarteMilitaire()
    :Carte(){
    symbole_chainage_entre = SymboleChainage::none;
    symbole_chainage_sortie = SymboleChainage::none;

    nb_symbole_militaire = 0;
    capacite = Capacite::avancee_militaire;
}
CarteMilitaire::CarteMilitaire(std::string n, unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, SymboleChainage symb_chain_entre, SymboleChainage symb_chain_sortie, unsigned int nb_militaire)
    :Carte(n,a, cout, pt_primaire, pt_secondaire, false, false, 0){
    symbole_chainage_entre=symb_chain_entre;
    symbole_chainage_sortie=symb_chain_sortie;
    nb_symbole_militaire=nb_militaire;
    capacite = Capacite::avancee_militaire;
}

CarteMilitaire::CarteMilitaire(const CarteMilitaire& c)
    :Carte(c){
        symbole_chainage_entre=c.symbole_chainage_entre;
        symbole_chainage_sortie=c.symbole_chainage_sortie;
        nb_symbole_militaire=c.nb_symbole_militaire;
        capacite = c.capacite;
}

void CarteMilitaire::exec_capacite(Joueur& joueur_adverse, PlateauMilitaire& plateau_militaire){ //!error
    plateau_militaire.update_avance(nb_symbole_militaire,joueur_adverse);
}


/*--------------------------------------------------------------------------*/


/*-------------------------------------Carte Guilde-------------------------------------*/

CarteGuilde::CarteGuilde()
:Carte(){
    effet_guilde = EffetGuilde::guilde_armateurs;
}
CarteGuilde::CarteGuilde(std::string n, unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, EffetGuilde effet)
:Carte(n, a, cout, pt_primaire, pt_secondaire, false, false, 0){
    effet_guilde = effet;
}
CarteGuilde::CarteGuilde(const CarteGuilde& c)
:Carte(c){
    effet_guilde = c.effet_guilde;
}

void CarteGuilde::exec_effet_guilde(Joueur& joueur1, Joueur& joueur2) const{
    switch (effet_guilde) {
        case EffetGuilde::guilde_armateurs: exec_guilde_armateurs(joueur1, joueur2); break;
        case EffetGuilde::guilde_batisseurs: exec_guilde_batisseurs(joueur1, joueur2); break;
        case EffetGuilde::guilde_commercants: exec_guilde_commerce(joueur1, joueur2); break;
        case EffetGuilde::guilde_scientifiques: exec_guilde_scientifiques(joueur1, joueur2); break;
        case EffetGuilde::guilde_tacticiens: exec_guilde_tacticiens(joueur1, joueur2); break;
        case EffetGuilde::guilde_magistrats: exec_guilde_magistrats(joueur1, joueur2); break;
        case EffetGuilde::guilde_usuriers: exec_guilde_usuriers(joueur1, joueur2); break;

        default:
            std::cout << "Erreur";
    }
}


void exec_guilde_armateurs(Joueur& joueur1, Joueur& joueur2){
    //le joueur1 recoit un nombre de pièce équivalent au nombre de cartes marron et gris dans la cité qui en possède le plus grand nombre
    unsigned int nbcartej1 =  joueur1.getNbCartesType("RessourcePrimaire")+joueur1.getNbCartesType("RessourceSecondaire");// j'ai corrigé une erreur. t'avais mis RessourcePrimaire 2 fois
    unsigned int nbcartej2 = joueur2.getNbCartesType("RessourcePrimaire")+joueur2.getNbCartesType("RessourceSecondaire");
    joueur1.gagnerArgent(std::max(nbcartej1,nbcartej2));
    //! jsp encore comment ajouter des points de victoire en plus 
    //utilise la méthode: joueur1.gagnerPtVictoire(x);
}


void exec_guilde_batisseurs(Joueur& joueur1, Joueur& joueur2){
    //fin de la partie, le joueur1 recoit 2 points de victoire par carte merveille possédé par le joueur qui en a le plus

}

void exec_guilde_commerce(Joueur& joueur1, Joueur& joueur2){
    unsigned int nbcartej1 =  joueur1.getNbCartesType("Commerce");
    unsigned int nbcartej2 = joueur2.getNbCartesType("Commerce");
    joueur1.gagnerArgent(std::max(nbcartej1,nbcartej2));

    //! jsp encore comment ajouter des points de victoire en plus 
    //utilise la méthode: joueur1.gagnerPtVictoire(x);
}
void exec_guilde_scientifiques(Joueur& joueur1, Joueur& joueur2){
    unsigned int nbcartej1 =  joueur1.getNbCartesType("Science");
    unsigned int nbcartej2 = joueur2.getNbCartesType("Science");
    joueur1.gagnerArgent(std::max(nbcartej1,nbcartej2));

    //! jsp encore comment ajouter des points de victoire en plus 
    //utilise la méthode: joueur1.gagnerPtVictoire(x);
}
void exec_guilde_tacticiens(Joueur& joueur1, Joueur& joueur2){
        unsigned int nbcartej1 =  joueur1.getNbCartesType("Militaire");
    unsigned int nbcartej2 = joueur2.getNbCartesType("Militaire");
    joueur1.gagnerArgent(std::max(nbcartej1,nbcartej2));

    //! jsp encore comment ajouter des points de victoire en plus 
    //utilise la méthode: joueur1.gagnerPtVictoire(x);
}
void exec_guilde_magistrats(Joueur& joueur1, Joueur& joueur2){
        unsigned int nbcartej1 =  joueur1.getNbCartesType("Prestige");
    unsigned int nbcartej2 = joueur2.getNbCartesType("Prestige");
    joueur1.gagnerArgent(std::max(nbcartej1,nbcartej2));
    //! jsp encore comment ajouter des points de victoire en plus 
    //utilise la méthode: joueur1.gagnerPtVictoire(x);
    
}
void exec_guilde_usuriers(Joueur& joueur1, Joueur& joueur2){
    // 1 point de victoire pour le joueur1 par lot de 3 pièces d'or possédé par le joueur le plus riche
}


/*--------------------------------------------------------------------------*/

/*------------------------------------MERVEILLE--------------------------------------*/

Merveille::Merveille()
:Carte(){
    production_primaire = new RessourcePrimaire[Taille_prod_primaire];
    production_secondaire = new RessourceSecondaire[Taille_prod_secondaire];
    capacite = new Capacite[Taille_capacite];

    for(int i=0; i<Taille_prod_primaire; i++){production_primaire[i] = RessourcePrimaire::none;}
    for(int i=0; i<Taille_prod_secondaire; i++){production_secondaire[i] = RessourceSecondaire::none;}
    for(int i=0; i<Taille_capacite; i++){capacite[i] = Capacite::none;}

    pt_victoire = 0;
    avance_militaire = 0;
}
    Merveille::Merveille(std::initializer_list<RessourcePrimaire> prod_primaire, std::initializer_list<RessourceSecondaire> prod_secondaire, std::initializer_list<Capacite> capa, unsigned int pt_vict, unsigned int av_milit,bool choix, std::string n, unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire)
    :Carte(n,a, cout, pt_primaire, pt_secondaire, 1, 1, 0){
        production_primaire = new RessourcePrimaire[Taille_prod_primaire];
        production_secondaire = new RessourceSecondaire[Taille_prod_secondaire];
        capacite = new Capacite[Taille_capacite];
        this->choix = choix;

        int i = 0;
        for (const auto& prod : prod_primaire){
            if (i < Taille_prod_primaire) {
                production_primaire[i++] = prod;
            }
        }
        i = 0;
        for (const auto& prod : prod_secondaire){
            if (i < Taille_prod_secondaire) {
                production_secondaire[i++] = prod;
            }
        }
        i = 0;
        for (const auto& cap : capa){
            if (i < Taille_capacite) {
                capacite[i++] = cap;
            }
        }

        pt_victoire = pt_vict;
        avance_militaire = av_milit;
    }
Merveille::Merveille(const Merveille& c)
    :Carte(c){
    production_primaire = new RessourcePrimaire[Taille_prod_primaire];
    production_secondaire = new RessourceSecondaire[Taille_prod_secondaire];
    capacite = new Capacite[Taille_capacite];

    for(int i=0; i<Taille_prod_primaire; i++){production_primaire[i] = c.production_primaire[i];}
    for(int i=0; i<Taille_cout_secondaire; i++){production_secondaire[i] = c.production_secondaire[i];}
    for(int i=0; i<Taille_capacite; i++){capacite[i] = c.capacite[i];}

    pt_victoire = c.pt_victoire;
    avance_militaire = c.avance_militaire;
}

unsigned int Merveille::getQuantRessPrimProd(RessourcePrimaire rp) const{
    unsigned int res = 0;
    for(int i=0; i<Taille_prod_primaire; i++){
        if (production_primaire[i] == rp) res++;
    }
    return res;
}
unsigned int Merveille::getQuantRessSecondProd(RessourceSecondaire rs) const{
    unsigned int res = 0;
    for(int i=0; i<Taille_prod_secondaire; i++){
        if (production_secondaire[i] == rs) res++;
    }
    return res;
}


void Merveille::addCapacite(Capacite c){
    //ajoute une capacité si la capacité n'est pas déjà présente
    for(int i=0; i<Taille_capacite; i++){
        if (capacite[i] == Capacite::none){
            capacite[i] = c;
            break;
        }
        if(capacite[i] == c){
            std::cout << "La capacité est déjà présente" << std::endl;
            break;
        }
    }
}

void Merveille::exec_capacite(Joueur& joueur1, Joueur& joueur2, PlateauCartes& plateau_carte, PlateauMilitaire& plateau_militaire, PlateauScience& plateau_science) const{
    for(int i=0; i<Taille_capacite; i++){
        switch (capacite[i]) {
            case Capacite::none: break;
            case Capacite::rejouer: this->exec_rejouer(joueur1); break;
            case Capacite::detruire_carte_marron: this->exec_detruire_carte_marron(joueur1, joueur2); break;
            case Capacite::detruire_carte_grise: this->exec_detruire_carte_grise(joueur1, joueur2); break;
            case Capacite::jouer_carte_defausse: this->exec_jouer_carte_defausse(joueur1, plateau_carte); break;
            case Capacite::avancee_militaire: this->exec_avancee_militaire(joueur2, plateau_militaire); break;
            case Capacite::choisir_jeton_science: this->exec_choisir_jeton_science(joueur1, plateau_science); break;
            case Capacite::gagner_monnaie_12: this->exec_gagner_monnaie_12(joueur1); break;
            case Capacite::gagner_monnaie_6: this->exec_gagner_monnaie_6(joueur1); break;
            case Capacite::gagner_monnaie_3: this->exec_gagner_monnaie_3(joueur1); break;
            case Capacite::perdre_monnaie_3: this->exec_perdre_monnaie_3(joueur2); break;
            default:
                std::cout << "Erreur";
        }
    }
}

//TODO : definir les méthodes de la classe joueur : choisirCarteMarronAutreJoueur() -> CarteRessourcePrimaire* const 
//TODO : definir les méthodes de la classe joueur : choisirCarteGriseAutreJoueur() -> CarteRessourceSecondaire* const 
//TODO : definir les méthodes de la classe joueur : choisirCarteDefausse() -> Carte* const
//TODO : definir les méthodes de la classe joueur : choisirJetonScienceParmis3(JetonScience* liste_jeton) -> void



void Merveille::exec_rejouer(Joueur& joueur1) const{
    joueur1.setRejouerTrue(); //! setRejouer est une méthode qui met l'attribut rejouer à True
}
void Merveille::exec_detruire_carte_marron(Joueur& joueur1, Joueur& joueur2) const{

    CarteRessourcePrimaire* carte_choisit = joueur1.choisirCarteMarronAutreJoueur(); //? demander au joueur 1 de choisir une carte marron du joueur 2
    joueur2.retirerCarte(carte_choisit); //!definir retirerCarte
}

void Merveille::exec_detruire_carte_grise(Joueur& joueur1, Joueur& joueur2) const{

    CarteRessourceSecondaire* carte_choisit = joueur1.choisirCarteGriseAutreJoueur(); //? demander au joueur 1 de choisir une carte grise du joueur 2
    joueur2.retirerCarte(carte_choisit); 
}
void Merveille::exec_jouer_carte_defausse(Joueur& joueur1, PlateauCartes& plateau_carte) const{


    Carte* carte_choisit = joueur1.choisirCarteDefausse(); //? demander au joueur de choisir une carte de la defause 
    joueur1.construireCarte(*carte_choisit); 


}

void Merveille::exec_choisir_jeton_science(Joueur& joueur1, PlateauScience& plateau_science) const{
    JetonScience* liste_jeton = plateau_science.tirer_jeton_out_game();
    joueur1.choisirJetonScienceParmis3(liste_jeton);
}

void Merveille::exec_gagner_monnaie_12(Joueur& joueur1) const{joueur1.gagnerArgent(12);}
void Merveille::exec_gagner_monnaie_6(Joueur& joueur1) const{joueur1.gagnerArgent(6);}
void Merveille::exec_gagner_monnaie_3(Joueur& joueur1) const{joueur1.gagnerArgent(3);}
void Merveille::exec_perdre_monnaie_3(Joueur& joueur2) const{joueur2.gagnerArgent(-3);}

void Merveille::exec_avancee_militaire(Joueur& joueur2, PlateauMilitaire& plateau_militaire) const{
    plateau_militaire.update_avance(avance_militaire,joueur2);
}


Merveille::~Merveille(){
    delete[] production_primaire;
    delete[] production_secondaire;
    delete[] capacite;
}

/*--------------------------------------------------------------------------*/





