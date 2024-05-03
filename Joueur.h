#pragma once
#include <iostream>
#include <string>
#include "Carte.h"
#include "Plateau.h"
#include "game.h"

// classe pour gérer les exceptions
class SetException {
public:
	SetException(const std::string& i) :info(i) {}
	std::string getInfo() const { return info; }
private:
	std::string info;
};




class Joueur{
private:
    Carte* cartes_construite[60]; //diviser en sous tableaux pr cartes marrons/grises construites?? //je pense que c'est mieux de les laisser comme ça
    Merveille* merveille_construite[4];
    JetonScience* jetons_science[6];
    SymboleScience* symboles_science[6]; //techniquement, il y a 7 symboles différents. mais, si on a 6, la game est finie.
    unsigned int monnaie;
    unsigned int pt_victoire;
    class Ressource{
    private:
        unsigned int bois = 0;
        unsigned int pierre = 0;
        unsigned int brique = 0;
        unsigned int verre = 0;
        unsigned int parchemin = 0;
    public:
        Ressource() = default;
        Ressource(const Ressource& r) = default;
        ~Ressource() = default;
        void ajouterRessource(RessourcePrimaire rp);
        void ajouterRessource(RessourceSecondaire rs);
        void retirerRessource(RessourcePrimaire rp);
        void retirerRessource(RessourceSecondaire rs);

    };
    Ressource ressources;


public:
    //constructeurs
    Joueur();
    Joueur(const Joueur& j);
    Joueur& operator=(const Joueur& j);
    bool operator==(const Joueur& j);

    //destructeur
    ~Joueur();

    /* ------les getteurs ----*/
    //getteur de monnaie et pt_victoire
    unsigned int getMonnaie() const { return monnaie; };
    unsigned int getPtVictoire()const { return pt_victoire; };
    //getteur de Nb de Cartes / jetons
    unsigned int getNbCartesConstruites() const;
    unsigned int getNbMerveillesConstruites()const;
    unsigned int getNbJetonsScience() const;
    unsigned int getNbSymbolesScience() const;
    //getteur de ressources produites. par ex: 2 bois ou 3 verres
    unsigned int getQuantiteDeRessourcePrimaire(const RessourcePrimaire& symbole) const;
    unsigned int getQuantiteDeRessourceSecondaire(const RessourceSecondaire& symbole) const ;
    Ressource getRessources(){return ressources;}; //?est ce que c'est mieux de retourner Ressource ou Ressource& ou Ressource*?

    //setteurs
    void setMonnaie(unsigned int argent){ monnaie = argent; };
    void setPtVictoire(unsigned int p){ pt_victoire = p;};
    
    //méthodes d'update
    void gagnerArgent(unsigned int argent);
    void gagnerPtVictoire(unsigned int p);

    //méthodes de vérification
    bool estConstructible(const Carte& carte) const; //! en gros est ce qu'on a les ressources necessaires pour construire la carte

    //autres fonctions importantes
    unsigned int getCout(const Carte& carte); //à faire bientot
    void construireCarte(Carte& carte, PlateauCartes& p); //à faire
    //void construireMerveille(Merveille& merveille, PlateauCartes& p); //à faire
    void choisir_action(PlateauCartes& p); // à faire plus tard


/*
    + get_cout(Carte) -> unsigned int (monnaie) //** existe deja dans carte ?
    //** on doit décider si getCout() est une fonction de joueur ou carte. parcequ'on a besoin des deux classes.
    //** on peut aussi la considérer comme une fonction à part qui prend les deux classes comme entrées
    //** je pense meme que c'est pt étre une fonction de controleur
    */
};

class PlateauCartes{
private:
    unsigned int age =1;
    CarteEnJeu* cartes_en_jeu[20]; 
    Carte* defausses[60];

public:
/*
    + addAge()
    + estaccessible(Carte in listecarteenjeu)
    + estprise(Carte in listecarteenjeu)
    + estdefausse(Carte in listrecarteenjeu)
    + getcartevisible()
    + getcarteaccessibles()

    + set_age(unsigned int)
    + const rend_accessible(&Carte)
    + const rend_face_visible(&Carte)
    + prendre(&Carte)
    + prendre(&Merveille)
    + defausser(&Carte)
    + const get_cartes_visibles() -> &Carte[]
    + const get_cartes_accessibles() -> &Carte[]
    + const nb_merveilles_restantes() -> unsigned int 
    */

   //constructuer

   //destructeur
   ~PlateauCartes();


   //méthodes en lien avec construireCarte() de la classe Joueur
   CarteEnJeu* trouverCarteDansPlateau(Carte& carte); 
   // retourne NULL si la carte n'est pas dans le tableau, et le pointeur sinon.
   void enleverCarteDuPlateau(CarteEnJeu* carte_plateau); //appelle trouverCarteDansPlateau()
};


/**
* ? jsp si il faut ajouter une autre classe Jeu (comme le td) ou pas?
* ? je suis aussi pas sur de quand utiliser le singleton
* * en tout cas, je crois qu'on a pas à utiliser un iterator en ce moment.
*/


//gérer age et distribuer les cartes
//piocher cartes, tt ce qui n'est pas dans les autres classes
class Controleur {
private:
	//Pioche* pioche=nullptr;
	PlateauCartes plateau_cartes;
    PlateauScience plateau_science;
    PLateauMilitaire plateau_militaire;
    Joueur joueur1;
    Joueur joueur2;

public:
    /*
	Controleur();
	void distribuer();
    ~Controleur() { delete pioche; }
	const Plateau& getPlateau() const { return plateau; }
    Plateau& getPlateau() { return plateau; }
    const Pioche& getPioche() const { return *pioche; }
	Controleur(const Controleur& c) = delete;
	Controleur& operator=(const Controleur& c) = delete;
    bool jeuEstFinie();
    */
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

