
#include <iostream>
#include <string>
using namespace std;
#include "Carte.h"
#include "Joueur.h"
#include "Plateau.h"
#include "controleur.h"

using namespace std;


//!--------------------------------LA FONCTION RECURSIVE QUI GERE LE JEU------------------------------------------*/

int SevenWondersDuel(Controleur& controleur, Joueur& joueur_actif){ //le 1er joueur donnée en argument est le joueur qui joue

    //** VERIFICATION DE LA VICTOIRE D'UN DES JOUEURS **//
    if (controleur.jeuEstFinie()) {
        return controleur.gagnant();
    } //!condition d'arret de la fonction recursive SevenWondersDuel

    controleur.addTour(); //ajoute un tour à la partie
    //** CHOIX D'UNE ACTION POUR LE JOUEUR ACTIF **//
    while (true) {
        Action action = joueur_actif.choisir_action(*(controleur.getPlateau().getPlateauCartes())); 
        if (controleur.actionEstLegale(action)){
            controleur.playAction(action);
            break;
        }
        else{
            cout << "Action illégale, veuillez choisir une action legale" << endl;
        }
    } //!While True tant que le joueur n'as pas choisir une action légale

    //** VERIFICATION DE LA FIN DE L'AGE **//
    if (controleur.getPlateau().getPlateauCartes()->estVide()){
        //changement d'age
        controleur.getPlateau().getPlateauCartes()->addAge();
        SevenWondersDuel(controleur, controleur.getPlateau().getPlateauMilitaire()->getJoueurDerriere());
    }
    else{
            //** PASSAGE AU TOUR SUIVANT **//
        if (joueur_actif.getRejouer() == 1){ //gestion du second tour de jeu en cas de Rejouer == TRUE 
            joueur_actif.setRejouerFalse();
            SevenWondersDuel(controleur, joueur_actif); //le joueur rejoue
        }
        else{
            if(joueur_actif == controleur.getJoueur1()){ //changement de joueur actif
                SevenWondersDuel(controleur, controleur.getJoueur2()); 
            }
            else{
                SevenWondersDuel(controleur, controleur.getJoueur1());
            }
        }
    }
}


int main(){
    cout << "Bienvenue dans 7 Wonders Duel!" << endl;

    Controleur jeu = Controleur();
    int gagnant  = SevenWondersDuel(jeu, jeu.getJoueur1());
    if (gagnant == 1){
        cout << "Le joueur 1 a gagné!" << endl;
    }
    else{
        cout << "Le joueur 2 a gagné!" << endl;
    }
    return 0;
}







