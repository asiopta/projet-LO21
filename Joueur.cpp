#include "Joueur.h"
#include "Carte.h"
#include <string.h>
#include <string>


/*--------------------classe Ressource--------------*/
void Joueur::Ressource::ajouterRessource(RessourcePrimaire rp){
    switch (rp){
        case RessourcePrimaire::bois: bois++; break;
        case RessourcePrimaire::pierre: pierre++; break;
        case RessourcePrimaire::brique: brique++; break;
        case RessourcePrimaire::none: break;
    }
}

void Joueur::Ressource::ajouterRessource(RessourceSecondaire rs){
    switch (rs){
        case RessourceSecondaire::verre: verre++; break;
        case RessourceSecondaire::parchemin: parchemin++; break;
        case RessourceSecondaire::none: break;
    }
}

void Joueur::Ressource::retirerRessource(RessourcePrimaire rp){
    switch (rp){
        case RessourcePrimaire::bois: bois--; break;
        case RessourcePrimaire::pierre: pierre--; break;
        case RessourcePrimaire::brique: brique--; break;
        case RessourcePrimaire::none: break;
    }
}

void Joueur::Ressource::retirerRessource(RessourceSecondaire rs){
    switch (rs){
        case RessourceSecondaire::verre: verre--; break;
        case RessourceSecondaire::parchemin: parchemin--; break;
        case RessourceSecondaire::none: break;
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
    unsigned int i = 0;
    while(i<6 && jetons_science[i]!= NULL){
        i++;
    }
    return i;
}

unsigned int Joueur::getNbSymbolesScience()const{
    unsigned int i = 0;
    while(i<6 && symboles_science[i] != NULL){
        i++;
    }
    return i;
}

//les getteurs de ressources
unsigned int Joueur::getQuantiteDeRessourcePrimaire(const RessourcePrimaire& symbole) const {
        Carte* constr = *cartes_construite;
        unsigned int res=0;
        for(int i=0; i<60; i++){
            RessourcePrimaire* tab = constr->getMateriauxPrimaires();
            while(tab != nullptr){
                if(*tab == symbole) res++;
                tab++;
            }
        }
        return res;
    };

unsigned int Joueur::getQuantiteDeRessourceSecondaire(const RessourceSecondaire& symbole) const{
        Carte* constr = *cartes_construite;
        unsigned int res=0;
        for(int i=0; i<60; i++){
            RessourceSecondaire* tab = constr->getMateriauxSecondaires();
            while(tab != nullptr){
                if(*tab == symbole) res++;
                tab++;
            }
        }
        return res;
    };



//d'autres méthodes utiles
void Joueur::gagnerArgent(unsigned int argent){
    unsigned int res = this->getMonnaie();
    res += argent;
    this->setMonnaie(res);
}

void Joueur::gagnerPtVictoire(unsigned int p){
    unsigned int res = this->getPtVictoire();
    res += p;
    this->setPtVictoire(res);
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
    if(getCout(carte) < getMonnaie()) return true;
    return false;

}


/*-------------------------------------PlateauCarte-------------------------------------*/


