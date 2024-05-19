#pragma once
#include <iostream>
#include <string>
#include "Carte.h"
#include "Plateau.h"
#include "setup.h"
#include "Joueur.h"


/*---------------------------Plateau général-------------------------*/
using Action = std::tuple<Carte*, std::string>;
class Plateau{
private:
    PlateauMilitaire plateau_militaire;
    PlateauScience plateau_science;
    PlateauCartes plateau_cartes;

public:
    //constructeurs/destructeur
    Plateau() = default;
    ~Plateau() = default;
    Plateau(const Plateau& plateau) = default; //potentiellement à refaire
    Plateau& operator=(const Plateau& plateau) = default; // potentiellement à refaire
    Plateau operator==(const Plateau& plateau); //à faire

    //getteurs
    PlateauMilitaire& getPlateauMilitaire(){return plateau_militaire;};
    PlateauScience& getPlateauScience(){ return plateau_science;};
    PlateauCartes& getPlateauCartes(){ return plateau_cartes;};

    //méthodes ultra importants
    void init(); //initialise correctement tous les plateaux //pt étre pas nécessaire à faire

    bool isEtatFinal() const; //est ce que le jeu est fini ou pas
    //(il n'ya plus de cartes sur PlateauCartes et c'est age 3) || (un des joueurs a gagné militairement)
    Action* actionsPossibles() const; //renvoie la liste des actions possibles à réaliser
    // soit toutes les cartes visibles et accessibles + (defausser ou construire)
    // Action = tuple(Carte*, "defausser" ou "construire")

    void play_move(Action& action);//appliquer une certaine action sur le Plateau
    // soit construire ou défausser une carte et appliquer les conséquences correspondantes sur les PlateauMiliaire et Science


};


//gérer age et distribuer les cartes
//piocher cartes, tt ce qui n'est pas dans les autres classes
class Controleur {
private:
	//Pioche* pioche=nullptr;
	Plateau plateau;
    Joueur joueur1;
    Joueur joueur2;
    int tour;
    //! rajouter notion d'action sous forme de tuple
    //rajouter singleton pattern
public:
    // = delete parcequ'on va jamais les utiliser
    Controleur(const Controleur& c) = delete;
	Controleur& operator=(const Controleur& c) = delete;

	Controleur() = default; //intialise le jeu: Plateau / joueurs / tour = 1
    ~Controleur() = default; //libere tout l'espace
	const Plateau& getPlateau() const { return plateau; }
    Plateau& getPlateau() { return plateau; }
	
    Joueur& quiJoue();
    bool jeuEstFinie(); // plateau.IsEtatFinal() || joueur1 a gagné || joueur2 a gagné

    Action* actionsLegales(); //renvoie une liste de ttes les actions légales que le joueurs, dont il est le tour de jouer, peut faire.
    bool actionEstLegale(Action& action); //est-ce que une action donné est légale/possible à faire pour le joueur dont il est le tour de jouer.
    void play_action(Action& action); //applique un move à tout les niveau. niveau

};

/**
 * si on veut faire un IA plus tard, il faut penser à rajouter les fonctions:
 * TODO: bool actionEstLegale(Controleur& c, Action& a);
** le problème c'est comment modéliser l'action. Cette fonction sera aussi utilise pour la classe Joueur
** pour s'assurer que les joueur effectuent une action légale à chaque fois

* TODO: Action* actionsLégales(Controleur& c, Joueur& j);
 * --> retourne un tableau contenant ttes les actions légales pour un joueur donné à cet instant du jeu

// action est un tuple (carte, défausser/construire)
* 
*/


