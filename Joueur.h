#pragma once
#include <iostream>
#include <string>
#include "Carte.h"
#include "Plateau.h"
#include "game.h"

//Amen: j'ai des erreurs partt parceque mon IDE ne reconnait pas "string".
//C'est le cas pr tt le monde ou juste moi?

enum class Age{ one , two , three }; //pt étre on peut faire ca?

// classe pour gérer les exceptions
class SetException {
public:
	SetException(const std::string& i) :info(i) {} //j'ai rajouté des std:: devant les string
	std::string getInfo() const { return info; }
private:
	std::string info;
};


class Joueur{
private:
    Carte* cartes_construite[60]; //diviser en sous tableaux pr cartes marrons/grises construites?? //je pense que c'est mieux de les laisser comme ça
    Merveille* merveille_construite[4];
    JetonScience* jetons_science[6];
    unsigned int monnaie;
    unsigned int pt_victoire; 

public:
    //constructeurs
    Joueur();

    //destructeur
    ~Joueur();

    /* ------les getteurs ----*/
    //getteur de ressources produites. par ex: 2 bois ou 3 verres
    unsigned int getQuantiteDeRessourcePrimaire(const RessourcePrimaire& symbole);
    unsigned int getQuantiteDeRessourceSecondaire(const RessourceSecondaire& symbole);
    //getteur de monnaie et pt_victoire
    unsigned int getMonnaie(){ return monnaie; };
    unsigned int getPtVictoire(){ return pt_victoire; };
    //getteur des tailles de listes
    unsigned int getNbCartesConstruites() { return 60; };
    unsigned int getNbMerveillesConstruites() {return 4; };
    unsigned int getNbJetonsScience() {return 6;};



/*
    des méthodes à rajouter:
    + updatemonnaie(int)
    + getproduction() -> Production
    + getcout(Carte) -> unsigned int (monnaie)
    + estconstructible(Carte, PlateauCarte) -> bool
    + construireCarte(Carte, PlateauCarte) -> None
    + construireMerveille(Merveille, Carte, PlateauCarte) -> None
    + getptdevictoire()
    + choisirAction(Carte)
    */
};

class PlateauCartes{
private:
    unsigned int age;
    CarteEnJeu* cartes_en_jeu[20]; 
    unsigned int nb_merveilles_constr;
    Carte* defausses[60];
public:
/*
    + addage()
    + estaccessible(Carte in listecarteenjeu)
    + estprise(Carte in listecarteenjeu)
    + estdefausse(Carte in listrecarteenjeu)
    + getcartevisible()
    + getcarteaccessibles()
    */

   //destructeur
   ~PlateauCartes();
};


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
    */
};


