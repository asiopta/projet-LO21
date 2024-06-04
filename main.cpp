
#include <iostream>
#include <string>
#include "Carte.h"
#include "Joueur.h"
#include "Plateau.h"
#include "controleur.h"
#include "const_and_enum.h"


using namespace std;


//!--------------------------------LA FONCTION RECURSIVE QUI GERE LE JEU------------------------------------------*/

int SevenWondersDuel(Controleur& controleur, Joueur* joueur_actif){ //le 1er joueur donnée en argument est le joueur qui joue
    std::cout << "debut de SevenWondersDuel" << std::endl; //!teste
    //** VERIFICATION DE LA VICTOIRE D'UN DES JOUEURS **//
    if (controleur.jeuEstFinie()) { //OK
        return controleur.gagnant(); //OK
    } //!condition d'arret de la fonction recursive SevenWondersDuel

    controleur.addTour(); //OK
    //** CHOIX D'UNE ACTION POUR LE JOUEUR ACTIF **//
    Action* actions_legales = controleur.actionsLegales();
    bool boucle = true;
    while (boucle) {

        Action action = joueur_actif->choisir_action(actions_legales);
        std::cout<< "boucle du jeu: action est choisie!" << std::endl; //!test
        if (controleur.actionEstLegale(action)){
            controleur.playAction(action);
            std::cout<< "boucle du jeu: action est exécutée!" << std::endl; //!test
            boucle = false;
        }
        else{
            cout << "Action illégale, veuillez choisir une action legale" << endl;
        }
    } //!While True tant que le joueur n'as pas choisir une action légale
    //free(actions_legales);

    //** VERIFICATION DE LA FIN DE L'AGE **//
    if (controleur.getPlateau().getPlateauCartes()->estVide()){
        //changement d'age
        controleur.getPlateau().getPlateauCartes()->addAge();
        return SevenWondersDuel(controleur, controleur.getPlateau().getPlateauMilitaire()->getJoueurDerriere());
    }
    else{
            //** PASSAGE AU TOUR SUIVANT **//
        if (joueur_actif->getRejouer() == true){ //gestion du second tour de jeu en cas de Rejouer == TRUE 
            joueur_actif->setRejouerFalse();
            return SevenWondersDuel(controleur, joueur_actif); //le joueur rejoue
            
        }
        else{
            if(joueur_actif == controleur.getJoueur1()){ //changement de joueur actif
                return SevenWondersDuel(controleur, controleur.getJoueur2()); 
            }
            else{
                return SevenWondersDuel(controleur, controleur.getJoueur1());
            }
        }
    }
}


const unsigned int NB_CHOIX_MERVEILLE = 4;

void choix_merveille(Controleur* jeu, Merveille** merveilles, int joueur){
    if (joueur == 1){
        Joueur* joueur1 = jeu->getJoueur1();
        Merveille* choix = joueur1->choisirCarte(merveilles, 4); 
        joueur1->setMerveille(choix);
        bool found = false;
        for(int i = 0; i < NB_CHOIX_MERVEILLE; i++){
            if (merveilles[i] == choix){
                merveilles[i] = nullptr;
            }
        
        } //supression de la merveille de la liste donnée en argument
    }

    else{
        Joueur* joueur2 = jeu->getJoueur2();
        Merveille* choix = joueur2->choisirCarte(merveilles, 4);
        joueur2->setMerveille(choix);
        for(int i = 0; i < NB_CHOIX_MERVEILLE; i++){
            if (merveilles[i] == choix){
                merveilles[i] = nullptr;
            }
        }
    }
}

int main(){


    //!INITIALISATION DU JEU
    try{
    std::cout << "Bienvenue dans Seven Wonders Duel!" << endl;
    // Controleur* jeu =  new Controleur();
    Controleur* jeu =  &Controleur::getInstance();// initialisation du jeu via le controleur


    //!CHOIX DES MERVEILLES
    Merveille** merveille = jeu->getPlateau().getPlateauCartes()->getMerveilles(); //recuperation des merveilles
    Merveille** merveilles_etape_1 = new Merveille*[NB_CHOIX_MERVEILLE]; //creation du premier lot de 4 merveilles

    for (int i = 0; i < NB_CHOIX_MERVEILLE; i++){
        merveilles_etape_1[i] = merveille[i];
    }
    Merveille** merveilles_etape_2 = new Merveille*[NB_CHOIX_MERVEILLE]; //creation du deuxieme lot de 4 merveilles
    for (int i =0; i < NB_CHOIX_MERVEILLE; i++){
        merveilles_etape_2[i] = merveille[i+NB_CHOIX_MERVEILLE];
    }


    std::cout<<"A vous de choisir deux merveilles dans le premier lot !" <<endl;
    //choix des merveilles pour le 1er lot de 4 merveilles
    choix_merveille(jeu, merveilles_etape_1, 1);
    choix_merveille(jeu, merveilles_etape_1, 2);
    choix_merveille(jeu, merveilles_etape_1, 2);
    choix_merveille(jeu, merveilles_etape_1, 1);
    std::cout<<"A vous de choisir deux merveilles dans le deuxième lot !" <<endl;
    //choix des merveilles pour le 2eme lot de 4 merveilles
    choix_merveille(jeu, merveilles_etape_2, 2);
    choix_merveille(jeu, merveilles_etape_2, 1);
    choix_merveille(jeu, merveilles_etape_2, 1);
    choix_merveille(jeu, merveilles_etape_2, 2);


    //!LANCEMENT DU JEU
    std::cout << "Lancement de la boucle de jeu !!"<<endl;
    int gagnant  = SevenWondersDuel(*jeu, jeu->getJoueur1()); 
    if (gagnant == 1){
        std::cout << "Le joueur 1 a gagné!" << endl;
    }
    else{
        std::cout << "Le joueur 2 a gagné!" << endl;
    }
    delete jeu;
    return 0;
    }catch (...) {
        std::cerr << "Une exception inconnue a été lancée" << std::endl;
        return 1;
    }
}







