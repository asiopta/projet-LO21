
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
const unsigned int NB_CHOIX_MERVEILLE = 4;

void choix_merveille(Controleur* jeu, Merveille** merveilles, int joueur){
    if (joueur == 1){
        Merveille* choix = jeu->getJoueur1().choisir_merveille(merveilles); //!!! A DEFINIR !!!//
        jeu->getJoueur1().setMerveille(choix);
        for(int i = 0; i < NB_CHOIX_MERVEILLE; i++){
            if (merveilles[i] == choix){
                merveilles[i] = nullptr;
            }
        } //supression de la merveille de la liste donnée en argument
    }

    else{
        Merveille* choix = jeu->getJoueur2().choisir_merveille(merveilles); //!!! A DEFINIR !!!//
        jeu->getJoueur2().setMerveille(choix);
        for(int i = 0; i < NB_CHOIX_MERVEILLE; i++){
            if (merveilles[i] == choix){
                merveilles[i] = nullptr;
            }
        }
    }
}

int main(){

    //!INITIALISATION DU JEU

    cout << "Bienvenue dans 7 Wonders Duel!" << endl;
    Controleur* jeu =  new Controleur(); // initialisation du jeu via le controleur

    
    //!CHOIX DES MERVEILLES
    Merveille** merveille = jeu->getPlateau().getPlateauCartes()->getMerveilles(); //recuperation des merveilles
    Merveille** merveilles_etape_1; //creation du premier lot de 4 merveilles
    for (int i = 0; i < NB_CHOIX_MERVEILLE; i++){
        merveilles_etape_1[i] = merveille[i];
    }
    Merveille** merveilles_etape_2; //creation du deuxieme lot de 4 merveilles
    for (int i =0; i < NB_CHOIX_MERVEILLE; i++){
        merveilles_etape_2[i] = merveille[i+NB_CHOIX_MERVEILLE];
    }
    //choix des merveilles pour le 1er lot de 4 merveilles
    choix_merveille(jeu, merveilles_etape_1, 1);
    choix_merveille(jeu, merveilles_etape_1, 2);
    choix_merveille(jeu, merveilles_etape_1, 2);
    choix_merveille(jeu, merveilles_etape_1, 1);
    //choix des merveilles pour le 2eme lot de 4 merveilles
    choix_merveille(jeu, merveilles_etape_2, 2);
    choix_merveille(jeu, merveilles_etape_2, 1);
    choix_merveille(jeu, merveilles_etape_2, 1);
    choix_merveille(jeu, merveilles_etape_2, 2);


    //!LANCEMENT DU JEU
    int gagnant  = SevenWondersDuel(*jeu, jeu->getJoueur1()); 
    if (gagnant == 1){
        cout << "Le joueur 1 a gagné!" << endl;
    }
    else{
        cout << "Le joueur 2 a gagné!" << endl;
    }
    delete jeu;
    return 0;
}







