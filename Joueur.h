#pragma once
#include <iostream>
#include <string>
#include "Carte.h"
#include "Plateau.h"
#include "game.h"

// classe pour gérer les exceptions
class SetException {
public:
	SetException(const std::string& i) :info(i) {} //j'ai rajouté des std:: devant les string
	std::string getInfo() const { return info; }
private:
	std::string info;
};


class Ressource{
private:
    unsigned int bois;
    unsigned int pierre;
    unsigned int brique;
    unsigned int verre;
    unsigned int parchemin;
public:
    //bla bla bla
};

class Joueur{
private:
    Carte* cartes_construite[60]; //diviser en sous tableaux pr cartes marrons/grises construites?? //je pense que c'est mieux de les laisser comme ça
    Merveille* merveille_construite[4];
    JetonScience* jetons_science[6];
    SymboleScience* symboles_science[6]; //techniquement, il y a 7 symboles différents. mais, si on a 6, la game est finie.
    unsigned int monnaie;
    unsigned int pt_victoire; 
    //je suis en train de penser à créer une nouvelle classe qui englobe les ressources 
    //genre "Ressource* ressources" comme attribut
    //et la classe aura comme attributs: verre, bois, etc..
    // avec chaque truc int. Ca facilitera beaucoup tracking les ressources du joueur mais aussi des cartes
    //On peut appliquer ca au lieu d'un tableau de ressources qu'on doit parcourir à chaque fois
    // au pire, on garde la classe Carte comme elle est comme y'a très peu de ressources produites de tte facon
    // Mais, on applique ca pour la classe Joueur pour étre tranquil plus tard
    // Cela remplacera les méthodes getteur de ressources produites par un simple getteur de classe Joueur

public:
    //constructeurs
    Joueur();
    /** 
     *Todo: rajotuer operator: = , ==, and constructeur par recopie
      */

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
    unsigned int getQuantiteDeRessourcePrimaire(const RessourcePrimaire& symbole) const ;
    unsigned int getQuantiteDeRessourceSecondaire(const RessourceSecondaire& symbole) const ;

    //setteurs
    void setMonnaie(unsigned int argent){ monnaie = argent; };
    void setPtVictoire(unsigned int p){ pt_victoire = p;};
    
    //méthodes d'update
    void gagnerArgent(unsigned int argent);
    void gagnerPtVictoire(unsigned int p);

    //méthodes de vérification
    bool estConstructible(const Carte& carte, const PlateauCartes& p);
    //bool estConstructible(const Merveille& merveille, const PlateauCartes& p); // pt étre inutile
    //Merveille est sous-classe de Carte donc normalement cette dernière méthode est inutile

    

    //autres fonctions importantes
    unsigned int getCout(const Carte& carte); //à faire
    unsigned int getCout(const Merveille& merveille); // à faire, pt étre inutile et que celle dessus suffit
    void construireCarte(Carte& carte, PlateauCartes& p); //à faire
    void construireMerveille(Merveille& merveille, PlateauCartes& p); //à faire
    void choisir_action(PlateauCartes& p);


};

class PlateauCartes{
private:
    unsigned int age;
    CarteEnJeu* cartes_en_jeu[20]; 
    unsigned int nb_merveilles_constr; // je pense que ce n'est pas le bon lieu de cet attribut. Mieux en controlleur?
    //Ou peut étre totalement inutile, on peut calculer le nombre de merveille construite par chaque Joueur
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
};


/**
* ? jsp si il faut ajouter une autre classe Jeu (comme le td) ou pas?
* ? je suis aussi pas sur de quand utiliser le singleton
* * en tout cas, je crois qu'on a pas à utiliser un iterator en ce moment.
*/
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

* 
*/

