#include "Joueur.h"
#include "Carte.h"
#include <string.h>
#include <string>


/*--------------------classe Ressource--------------*/
void Joueur::ajouterRessource(RessourcePrimaire rp){
    switch (rp){
        case RessourcePrimaire::bois: ressources.bois++; break;
        case RessourcePrimaire::pierre: ressources.pierre++; break;
        case RessourcePrimaire::brique: ressources.brique++; break;
        case RessourcePrimaire::none: break;
    }
}

void Joueur::ajouterRessource(RessourceSecondaire rs){
    switch (rs){
        case RessourceSecondaire::verre: ressources.verre++; break;
        case RessourceSecondaire::parchemin: ressources.parchemin++; break;
        case RessourceSecondaire::none: break;
    }
}

void Joueur::retirerRessource(RessourcePrimaire rp){
    switch (rp){
        case RessourcePrimaire::bois: if(ressources.bois != 0){ressources.bois--;} break;
        case RessourcePrimaire::pierre: if(ressources.pierre != 0){ ressources.pierre--;} break;
        case RessourcePrimaire::brique: if(ressources.brique != 0){ressources.brique--;} break;
        case RessourcePrimaire::none: break;
    }
}

void Joueur::retirerRessource(RessourceSecondaire rs){
    switch (rs){
        case RessourceSecondaire::verre: if(ressources.verre!= 0){ressources.verre--;} break;
        case RessourceSecondaire::parchemin: if(ressources.parchemin!=0){ressources.parchemin--;} break;
        case RessourceSecondaire::none: break;
    }
}


void Joueur::setRessource(RessourcePrimaire rp, unsigned int quantite){
    if(quantite>=0){
        switch (rp){
            case RessourcePrimaire::bois: ressources.bois= quantite; break;
            case RessourcePrimaire::pierre: ressources.pierre = quantite; break;
            case RessourcePrimaire::brique: ressources.brique = quantite; break;
            case RessourcePrimaire::none: break;
        }
    }
    else{
        SetException("erreur: quantite de ressource négative");
    }
}

void Joueur::setRessource(RessourceSecondaire rs, unsigned int quantite){
        if(quantite>=0){
        switch (rs){
            case RessourceSecondaire::verre: ressources.verre = quantite; break;
            case RessourceSecondaire::parchemin: ressources.parchemin = quantite; break;
            case RessourceSecondaire::none: break;
        }
    }
    else{
        SetException("erreur: quantite de ressource négative");
    }
}

/*---------classe CapaciteJetons------------------------*/
void Joueur::addCapaciteJeton(CapaciteScience& jeton){
    switch (jeton)
    {
    case CapaciteScience::architecture: capacites.architecture = true; break;
    case CapaciteScience::economie: capacites.economie = true; break;
    case CapaciteScience::maconnerie: capacites.maconnerie = true; break;
    case CapaciteScience::mathematique: capacites.mathematiques = true; break;
    case CapaciteScience::strategie: capacites.strategie = true; break;
    case CapaciteScience::theologie: capacites.theologie = true; break;
    case CapaciteScience::urbanisme: capacites.urbanisme = true; break;
    
    default:break;
    }
}

void Joueur::construireJeton(CapaciteScience& jeton){
    switch (jeton)
    {
    case CapaciteScience::loi: symboles_science.autre = true; break;
    case CapaciteScience::agriculture:
        gagnerArgent(6);
        gagnerPtVictoire(4);
        break;
    case CapaciteScience::philosophie:
        gagnerPtVictoire(7);
        break;
    default: addCapaciteJeton(jeton); break;
    }
}


/*---------------Classe SymbolesScience----------------*/
unsigned int Joueur::getNbSymbolesScience()const{
    unsigned int res = 0;
    if(symboles_science.roue!=0) res++;
    if(symboles_science.plume != 0) res++;
    if(symboles_science.pilon != 0) res++;
    if(symboles_science.balance != 0) res++;
    if(symboles_science.globe_terrestre != 0) res++;
    if(symboles_science.fil_a_plomb != 0) res++;
    if(symboles_science.bateau != 0) res++;
    if(symboles_science.autre == true) res++;
    return res;
}

void Joueur::addSymboleScience(SymboleScience& s){
    switch (s)
    {
    case SymboleScience::roue: 
        symboles_science.roue++;
        if(symboles_science.roue == 2) choisirJeton();
        break;
    case SymboleScience::plume:
        symboles_science.plume++;
        if(symboles_science.plume == 2) choisirJeton();
        break;
    case SymboleScience::pilon:
        symboles_science.pilon++;
        if(symboles_science.pilon == 2) choisirJeton();
        break;
    case SymboleScience::balance:
        symboles_science.balance++;
        if(symboles_science.balance ==2) choisirJeton();
        break;
    case SymboleScience::globe_terrestre:
        symboles_science.globe_terrestre++;
        if(symboles_science.globe_terrestre == 2) choisirJeton();
        break;
    case SymboleScience::fil_a_plomb:
        symboles_science.fil_a_plomb++;
        if(symboles_science.fil_a_plomb == 2) choisirJeton();
        break;
    case SymboleScience::bateau:
        symboles_science.bateau++;
        if(symboles_science.bateau == 2) choisirJeton();
        break;
    default:
        break;
    }
}


void Joueur::removeSymboleScience(SymboleScience& s){
        switch (s)
    {
    case SymboleScience::roue: 
        if(symboles_science.roue!=0) symboles_science.roue--;
        break;
    case SymboleScience::plume:
        if(symboles_science.plume!=0) symboles_science.plume--;
        break;
    case SymboleScience::pilon:
        if(symboles_science.pilon!=0) symboles_science.pilon--;
        break;
    case SymboleScience::balance:
        if(symboles_science.balance!=0) symboles_science.balance--;
        break;
    case SymboleScience::globe_terrestre:
        if(symboles_science.globe_terrestre!=0) symboles_science.globe_terrestre--;
        break;
    case SymboleScience::fil_a_plomb:
        if(symboles_science.fil_a_plomb!=0) symboles_science.fil_a_plomb--;
        break;
    case SymboleScience::bateau:
        if(symboles_science.bateau!=0) symboles_science.bateau--;
        break;
    default:
        break;
    }
}

/*------------------classe Joueur----------------------*/
//constructeurs
Joueur::Joueur(): pt_victoire(0), monnaie(7), ressources() {
    for(int i=0; i<60; i++) cartes_construite[i] = nullptr;
    for(int i=0; i<4; i++) merveille_construite[i] = nullptr;
    for(int i=0; i<6; i++) jetons_science[i] = nullptr;
}

Joueur::Joueur(const Joueur& j): monnaie(j.monnaie), pt_victoire(j.pt_victoire),
ressources(j.ressources){
    for(int i=0; i<60; i++) cartes_construite[i] = j.cartes_construite[i];
    for(int i=0; i<4; i++) merveille_construite[i] = j.merveille_construite[i];
    for(int i=0; i<6; i++) jetons_science[i] = j.jetons_science[i];
}

Joueur& Joueur::operator=(const Joueur& j){
    if(this != &j){
        monnaie = j.monnaie;
        pt_victoire = j.pt_victoire;
        ressources = j.ressources;
        for(int i=0; i<60; i++) cartes_construite[i] = j.cartes_construite[i];
        for(int i=0; i<4; i++) merveille_construite[i] = j.merveille_construite[i];
        for(int i=0; i<6; i++) jetons_science[i] = j.jetons_science[i];
    }
    return *this;
}

bool Joueur::operator==(const Joueur& j){
    return this == &j;
}

//destructeur
Joueur::~Joueur(){
    for(int i=0; i< getNbCartesConstruites(); i++) free(cartes_construite[i]);
    for(int i=0; i< getNbMerveillesConstruites(); i++) free(merveille_construite[i]);
    for(int i=0; i< getNbJetonsScience(); i++) free(jetons_science[i]);
}

// _____les getteurs_____//

//getteur de Nb de Cartes / jetons
unsigned int Joueur::getNbCartesConstruites() const{
    unsigned int i = 0;
    while(i<60 && cartes_construite[i]!= NULL){
        i++;
    }
    return i;
}

unsigned int Joueur::getNbMerveillesConstruites() const {
    unsigned int i = 0;
    while(i<4 && merveille_construite[i]!= NULL){
        i++;
    }
    return i;
}

unsigned int Joueur::getNbJetonsScience()const{
    
}


unsigned int Joueur::getNbCarteType(TypeCarte type) const{
    switch (type)
    {
    case TypeCarte::CarteRessourcePrimaire:

        break;
    
    default:
        break;
    }
}

TypeCarte hashit(std::string const& type){
    if(type=="CarteRessourcePrimaire") return TypeCarte::CarteRessourcePrimaire;
    if(type=="CarteRessourceSecondaire") return TypeCarte::CarteRessourceSecondaire;
    if(type=="CarteCarteCommerce") return TypeCarte::CarteCommerce;
    if(type=="CarteGuilde") return TypeCarte::CarteGuilde;
    if(type=="CarteMilitaire") return TypeCarte::CarteMilitaire;
    if(type=="CartePrestige") return TypeCarte::CartePrestige;
    if(type=="CarteScience") return TypeCarte::CarteScience;
 }

unsigned int Joueur::getNbCarteType(std::string type) const {
    switch (hashit(type)) {
        case TypeCarte::CarteRessourcePrimaire:
        {
            unsigned int res = 0;
            for (int i = 0; i < 60; ++i) {
                if (cartes_construite[i] != nullptr && cartes_construite[i]->get_type() == "CarteRessourcePrimaire") {
                    res++;
                }
            }
            return res;
        }
        case TypeCarte::CarteRessourceSecondaire:
        {
            unsigned int res = 0;
            for (int i = 0; i < 60; ++i) {
                if (cartes_construite[i] != nullptr && cartes_construite[i]->get_type() == "CarteRessourceSecondaire") {
                    res++;
                }
            }
            return res;
        }
        case TypeCarte::CarteCommerce:
        {
            unsigned int res = 0;
            for (int i = 0; i < 60; ++i) {
                if (cartes_construite[i] != nullptr && cartes_construite[i]->get_type() == "CarteCommerce") {
                    res++;
                }
            }
            return res;
        }
        case TypeCarte::CarteGuilde:
        {
            unsigned int res = 0;
            for (int i = 0; i < 60; ++i) {
                if (cartes_construite[i] != nullptr && cartes_construite[i]->get_type() == "CarteGuilde") {
                    res++;
                }
            }
            return res;
        }
        case TypeCarte::CarteMilitaire:
        {
            unsigned int res = 0;
            for (int i = 0; i < 60; ++i) {
                if (cartes_construite[i] != nullptr && cartes_construite[i]->get_type() == "CarteMilitaire") {
                    res++;
                }
            }
            return res;
        }
        case TypeCarte::CartePrestige:
        {
            unsigned int res = 0;
            for (int i = 0; i < 60; ++i) {
                if (cartes_construite[i] != nullptr && cartes_construite[i]->get_type() == "CartePrestige") {
                    res++;
                }
            }
            return res;
        }
        case TypeCarte::CarteScience:
        {
            unsigned int res = 0;
            for (int i = 0; i < 60; ++i) {
                if (cartes_construite[i] != nullptr && cartes_construite[i]->get_type() == "CarteScience") {
                    res++;
                }
            }
            return res;
        }
        default:
            return 0;
    }
}



//d'autres méthodes utiles
void Joueur::gagnerArgent(int argent){
    unsigned int res = this->getMonnaie();
    res += argent;
    if (res < 0) res = 0;
    this->setMonnaie(res);
}

void Joueur::gagnerPtVictoire(unsigned int p){
    unsigned int res = this->getPtVictoire();
    res += p;
    this->setPtVictoire(res);
}

void Joueur::addSymboleScience(SymboleScience symbole){
    for(unsigned int i=0; i<6; i++){
        if(symboles_science[i] == nullptr){
            symboles_science[i] = &symbole;
            break;
        }
    }
}

void Joueur::construireCarte(Carte& carte, PlateauCartes& p){
    Carte* c = p.trouverCarteDansPlateau(carte);
    if((c != NULL) && estConstructible(carte)){
        monnaie -= getCout(carte);
        p.enleverCarteDuPlateau(c);
        unsigned int nb = getNbCartesConstruites();
        cartes_construite[nb] = &carte;
    }
    else{
        SetException("Impossible de construire la carte!");
    }
}

unsigned int getCout(const Carte& carte){
        //En cours
}


//méthodes de vérification
bool Joueur::estConstructible(const Carte& carte) const{ //! erreur due à getCout() donc pas grave pour l'instant
    //!rajouter les liens de chainage.....
    if(getCout(carte) < getMonnaie()) return true;
    return false;

}


/*-------------------------------------PlateauCarte-------------------------------------*/
 