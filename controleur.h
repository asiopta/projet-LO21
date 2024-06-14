#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#pragma once
#include <iostream>
#include <string>
#include "Joueur.h"
#include "Carte.h"
#include "Plateau.h"



//! Predeclaration de classe
class Joueur;
class Carte;



/*---------------------------Plateau général-------------------------*/
using Action = std::tuple<Carte*, std::string>;
 

class Plateau{
private:
    PlateauMilitaire* plateau_militaire;
    PlateauScience* plateau_science;
    PlateauCartes* plateau_cartes;

public:
    //constructeurs/destructeur
    Plateau(Joueur* joueur1, Joueur* joueur2); //initialise les 3 plateaux (militaire, science, cartes

    Plateau& operator=(const Plateau& plateau) = default; // potentiellement à refaire
    // Plateau operator==(const Plateau& plateau); 
    
    //getteurs
    PlateauMilitaire* getPlateauMilitaire(){return plateau_militaire;};
    PlateauScience* getPlateauScience(){ return plateau_science;};
    PlateauCartes* getPlateauCartes(){ return plateau_cartes;};

    //méthodes ultra importants
    void init(); //initialise correctement tous les plateaux

    bool isEtatFinal(); //est ce que le jeu est fini ou pas
    //(il n'ya plus de cartes sur PlateauCartes et c'est age 3)

    ~Plateau();
};


//gérer age et distribuer les cartes
//piocher cartes, tt ce qui n'est pas dans les autres classes
class Controleur {
private:
	//Pioche* pioche=nullptr;
    Joueur* joueur1;
    Joueur* joueur2;
    Plateau plateau;
    unsigned int tour = 1;

    struct Handler{
        Controleur* instance = nullptr;
        Handler() = default;
        ~Handler(){delete instance;};
    };
    static Handler handler;


public:
    //Constructeurs/destructeurs
	Controleur(); //initialise les 2 joueurs et le plateau
    Controleur(std::string player);
    // = delete parcequ'on va jamais les utiliser
    Controleur(const Controleur& c) = delete;
	Controleur& operator=(const Controleur& c) = delete;

    //méthodes de handler
    static Controleur& getInstance();//renvoie l'instance de handler //review
    static Controleur& getInstance(const std::string p);
    static void libererInstance();// libère l'instance de handler //review


    //getteurs/setteurs
    //? a t-on vraiment besoin de setteurs pour plateau et joueur? 
    //! non etant donnée quelles seront init par le controleur, et qu'on va pas les modifier après
	const Plateau& getPlateau() const { return plateau; }
    Plateau& getPlateau() { return plateau; }
    Joueur* getJoueur1() { return joueur1; };
    Joueur* getJoueur2() { return joueur2; };
    unsigned int getTotalCartesAccessibles();
    

    int getTour() { return tour;};
    void addTour();

	

    //autres méthodes utiles
    //bool gagne(Joueur& joueur);
    Joueur* quiJoue(); //retourne le joueur dont il est le tour de jouer //review
    Joueur* autreJoueur(Joueur* j);
    Joueur* determineGagnant(); //détermine le gagnant du match à la fin de l'age 3

    bool jeuEstFinie(); // plateau.IsEtatFinal() || joueur1 a gagné || joueur2 a gagné //review
    unsigned int gagnant(); //retourne le gagnant du match //review
    bool gagne(Joueur* joueur);

    bool estConstructible(Carte* carte);
    void construireCarte(Carte* carte); //review
    void defausserCarte(Carte* carte); //review

    void playAction(Action& action); //applique un move à tout les niveau. niveau //review
    //* pour créer une action, il faut utiliser: std::make_tuple(carte*, "construire");
    bool actionEstLegale(Action& action); //review
        //est-ce que une action donné est légale/possible à faire pour le joueur dont il est le tour de jouer.

    Action* actionsLegales(); //review
        //renvoie une liste de ttes les actions légales que le joueurs, dont il est le tour de jouer, peut faire.

    void showStatePlayer(Joueur* joueur);
    void showStatePlateauMilitaire();
    void showStatePlateauScience();

    ~Controleur	();
    

};

/**
 * si on veut faire un IA plus tard, il faut penser à rajouter les fonctions:
// action est un tuple (carte, défausser/construire)
* 
*/

#endif