#include "Joueur.h"

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

//les getteurs
unsigned int Joueur::get_quantite_ressource_primaire(const RessourcePrimaire& symbole) const{
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