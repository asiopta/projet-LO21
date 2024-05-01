#include "Joueur.h"
#include <string.h>
#include <string>


/*------------------classe Joueur----------------------*/
//constructeur
Joueur::Joueur(): pt_victoire(0), monnaie(7) {
    for(int i=0; i<60; i++) cartes_construite[i] = nullptr;
    for(int i=0; i<4; i++) merveille_construite[i] = nullptr;
    for(int i=0; i<6; i++) jetons_science[i] = nullptr;
}

//destructeur
Joueur::~Joueur(){
    for(int i=0; i< get_nb_cartes_construites(); i++) free(cartes_construite[i]);
    for(int i=0; i< get_nb_merveilles_construites(); i++) free(merveille_construite[i]);
    for(int i=0; i< get_nb_jetons_science(); i++) free(jetons_science[i]);
}

// _____les getteurs_____//

//getteur de Nb de Cartes / jetons
unsigned int Joueur::getNbCartesConstruites(){
    unsigned int i = 0;
    while(i<60 && cartes_construite[i]!= NULL){
        i++;
    }
    return i;
}

unsigned int Joueur::getNbMerveillesConstruites(){
    unsigned int i = 0;
    while(i<4 && merveille_construite[i]!= NULL){
        i++;
    }
    return i;
}

unsigned int Joueur::getNbJetonsScience(){
    unsigned int i = 0;
    while(i<6 && jetons_science[i]!= NULL){
        i++;
    }
    return i;
}



unsigned int Joueur::getNbSymbolesScience(){
    unsigned int i = 0;
    while(i<6 && SymboleScience[i]!= NULL){
        i++;
    }
    return i;
}

//les getteurs de ressources
unsigned int Joueur::getQuantiteDeRessourcePrimaire(const RessourcePrimaire& symbole){
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

unsigned int Joueur::get_quantite_ressource_secondaire(const RessourceSecondaire& symbole) const{
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

//méthodes de vérification
bool Joueur::estConstructible(const Carte& carte, const PlateauCartes& p){
    if(this->getCout(carte) < this->getMonnaie()) return true;
    return false;

}
