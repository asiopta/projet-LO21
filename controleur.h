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
    unsigned int age = 1; //! information redondante. existe deja dans plateau_cartes
    PlateauMilitaire* plateau_militaire;
    PlateauScience* plateau_science;
    PlateauCartes* plateau_cartes;

public:
    //constructeurs/destructeur
    Plateau(Joueur& joueur1, Joueur& joueur2); //initialise les 3 plateaux (militaire, science, cartes

    Plateau& operator=(const Plateau& plateau) = default; // potentiellement à refaire
    Plateau operator==(const Plateau& plateau); //à faire

    //getteurs
    PlateauMilitaire* getPlateauMilitaire(){return plateau_militaire;};
    PlateauScience* getPlateauScience(){ return plateau_science;};
    PlateauCartes* getPlateauCartes(){ return plateau_cartes;};

    //méthodes ultra importants
    void init(); //initialise correctement tous les plateaux //pt étre pas nécessaire à faire

    bool isEtatFinal(); //est ce que le jeu est fini ou pas
    //(il n'ya plus de cartes sur PlateauCartes et c'est age 3)
    Action* actionsPossiblesCarte() const; //renvoie la liste des actions possibles à réaliser 
    // soit toutes les cartes visibles et accessibles + (defausser ou construire)
    // Action = tuple(Carte*, "defausser" ou "construire")

    void playActionPlateau(Action& action);//appliquer une certaine action sur le Plateau
    // soit construire ou défausser une carte et appliquer les conséquences correspondantes sur les PlateauMiliaire et Science
    bool changerAge(); //change d'age (ajoute +1 à age) et renvoie false si l'age est 3 et True sinon 
    ~Plateau();

};


//gérer age et distribuer les cartes
//piocher cartes, tt ce qui n'est pas dans les autres classes
class Controleur {
private:
	//Pioche* pioche=nullptr;
	Plateau plateau;
    Joueur joueur1;
    Joueur joueur2;
    unsigned int tour = 1;
    //rajouter singleton pattern
    struct Handler{
        Controleur* instance = nullptr;
        Handler() = default;
        ~Handler(){delete instance;};
    };
    static Handler handler;


public:
    //Constructeurs/destructeurs
	Controleur() = default; //intialise le jeu: Plateau / joueurs / tour = 1
    ~Controleur() = default; //libere tout l'espace
    // = delete parcequ'on va jamais les utiliser
    Controleur(const Controleur& c) = delete;
	Controleur& operator=(const Controleur& c) = delete;

    //méthodes de handler
    static Controleur& getInstance();//renvoie l'instance de handler //review
    static void libererInstance();// libère l'instance de handler //review


    //getteurs/setteurs
    //? a t-on vraiment besoin de setteurs pour plateau et joueur?
	const Plateau& getPlateau() const { return plateau; }
    Plateau& getPlateau() { return plateau; }

    Joueur& getJoueur1() { return joueur1; };
    const Joueur& getJoueur1() const{ return joueur1; };

    Joueur& getJoueur2() { return joueur2; };
    const Joueur& getJoueur2() const{ return joueur2; };

    int getTour() { return tour;};
    void setTour(int j) { tour = j;};
	

    //autres méthodes utiles
    Joueur& quiJoue(); //retourne le joueur dont il est le tour de jouer //review
    Joueur& autreJoueur(Joueur& j);

    bool jeuEstFinie(); // plateau.IsEtatFinal() || joueur1 a gagné || joueur2 a gagné //review
    unsigned int gagnant(); //retourne le gagnant du match //review

    void contruireCarte(Carte* carte);
    void defausserCarte(Carte* carte);

    Action* actionsLegales(); //renvoie une liste de ttes les actions légales que le joueurs, dont il est le tour de jouer, peut faire.
    bool actionEstLegale(Action& action); //est-ce que une action donné est légale/possible à faire pour le joueur dont il est le tour de jouer.
    void playAction(Action& action); //applique un move à tout les niveau. niveau

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


