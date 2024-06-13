
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
    std::cout<< "C'est le tour du joueur " << controleur.getTour() <<"/ "<< controleur.quiJoue() <<std::endl;
    //** VERIFICATION DE LA VICTOIRE D'UN DES JOUEURS **//
    if (controleur.jeuEstFinie()) { //OK
        // std::cout<< "jeu est fini?"<< std:: endl; //! test
        return controleur.gagnant(); //OK
    } //!condition d'arret de la fonction recursive SevenWondersDuel

    
    //** CHOIX D'UNE ACTION POUR LE JOUEUR ACTIF **//
    // std::cout<< "action légales?" << std:: endl; //! test
    Action* actions_legales = controleur.actionsLegales();
    // std::cout<< "actions légales ok" << std:: endl; //! test
    bool boucle = true;
    while (boucle) {
        std::cout<< "choisir action?" << std:: endl; //! test
        Action action = joueur_actif->choisir_action(actions_legales);
        std::cout<< "choisir action ok" << std:: endl; //! test
        // std::cout<< "boucle du jeu: action est choisie!" << std::endl; //!test
        if (controleur.actionEstLegale(action)){
            controleur.playAction(action);
            // std::cout<< "boucle du jeu: action est exécutée!" << std::endl; //!test
            boucle = false;
        }
        else{
            cout << "Action illégale, veuillez choisir une action legale" << endl;
        }
    } //!While True tant que le joueur n'as pas choisir une action légale
    //free(actions_legales);

    controleur.addTour(); //OK
    //** VERIFICATION DE LA FIN DE L'AGE **//
    if (controleur.getPlateau().getPlateauCartes()->estVide()){
        //changement d'age
        // std::cout<< "add age?" << std::endl; //! test
        if (controleur.getPlateau().getPlateauCartes()->getAge() < 3){
            controleur.getPlateau().getPlateauCartes()->addAge();
            // std::cout<< "add age ok" << std::endl; //! test
            // std::cout<< "joueur derriere?"<<std::endl; //! test
            Joueur* joueur_derriere = controleur.getPlateau().getPlateauMilitaire()->getJoueurDerriere();
            // std::cout<< "joueur derriere ok: "<< joueur_derriere << std::endl; //! test
            // std::cout<< "joueur 1: "<< controleur.getJoueur1() << "/ joueur2: " << controleur.getJoueur2() << std::endl;
            return SevenWondersDuel(controleur, joueur_derriere);
        }
        else {
            std::cout<< "fin de l'age 3" << std::endl;
            std::cout<<"fin du jeu !" << std::endl;
            Joueur* joueur_gagnant = controleur.determineGagnant();
            if (joueur_gagnant == controleur.getJoueur1()){
                std::cout << "Le joueur 1 a gagné!" << endl;
                return 1;
            }
            else if (joueur_gagnant == controleur.getJoueur2()){
                std::cout << "Le joueur 2 a gagné!" << endl;
                return 2;
            }
            else {
                std::cout << "Egalité!" << endl;
                return 0;
            }
        }
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
    std::cout << "Voulez vous jouer:" << endl;
    std::cout << "1/ PVP" << endl;
    std::cout << "2/ PVIA" << endl;
    int p;
    std:: cin >> p;
    bool ia = false;
    while(p != 1 && p!=2){
        std::cout<< "choix invalide. veuillez réessayer!";
        std::cin>> p;
    }
    Controleur* jeu;
    if(p == 1)
        jeu =  &Controleur::getInstance();// initialisation du jeu via le controleur
    if(p==2){
        jeu =  &Controleur::getInstance("IA");
        ia = true;
    }


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

    if (ia == false){
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
    }
    // else{
    //     Merveille* choix = nullptr;
    //     std::cout<<"A vous de choisir deux merveilles dans le premier lot !" <<endl;
    //     //choix des merveilles pour le 1er lot de 4 merveilles
    //     choix_merveille(jeu, merveilles_etape_1, 1);
    //     // jeu->getJoueur2()->setMerveille(merveilles_etape_1[0]);
    //     choix_merveille(jeu, merveilles_etape_1, 1);
    //     std::cout<<"A vous de choisir deux merveilles dans le deuxième lot !" <<endl;
    //     //choix des merveilles pour le 2eme lot de 4 merveilles
    //     choix_merveille(jeu, merveilles_etape_2, 2);
    //     choix_merveille(jeu, merveilles_etape_2, 1);
    //     choix_merveille(jeu, merveilles_etape_2, 1);
    //     choix_merveille(jeu, merveilles_etape_2, 2);
    // } 



    //!LANCEMENT DU JEU
    std::cout << "Lancement de la boucle de jeu !!"<<endl;
    int gagnant  = SevenWondersDuel(*jeu, jeu->getJoueur1()); 
    if (gagnant == 1){
        std::cout << "Le joueur 1 a gagné!" << endl;
    }
    else if (gagnant == 2){
        std::cout << "Le joueur 2 a gagné!" << endl;
    }
    else {
        std::cout << "Match nul!" << endl;
    }
    delete jeu;
    return 0;
    }catch (...) {
        std::cerr << "Une exception inconnue a été lancée" << std::endl;
        return 1;
    }
}







