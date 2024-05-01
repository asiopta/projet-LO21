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
    //? J'ai mis les getters en methode const
    unsigned int get_quantite_ressource_primaire(const RessourcePrimaire& symbole) const;
    unsigned int get_quantite_ressource_secondaire(const RessourceSecondaire& symbole) const;
    //getteur de monnaie et pt_victoire
    unsigned int get_monnaie() const{ return monnaie; };
    unsigned int get_pt_victoire() const{ return pt_victoire; };
    //getteur des tailles de listes
    unsigned int get_nb_cartes_construites() const{return 60; };
    unsigned int get_nb_merveilles_construites() const{return 4; };
    unsigned int get_nb_jetons_science() const {return 6;};

    void set_monnaie(unsigned int m) { monnaie = m; };



/*
    des méthodes à rajouter:
    + updatemonnaie(int) //!equivalent de la fonction set_monnaie que j'ai ajouté 
    + get_production() -> Production //? c'est ce que tu as fait avec les get_quantite_ressource_primaire et get_quantite_ressource_secondaire ?
    ? pour moi c'est mieux comme tu as fait avec ces fonction parceque ca permet de pas tout tester a chaque fois qu'on doit construir une carte
    + get_cout(Carte) -> unsigned int (monnaie) //** existe deja dans carte ? 
    + est_constructible(Carte, PlateauCarte) -> bool 
    + construire_carte(Carte, PlateauCarte) -> None
    + construire_merveille(Merveille, Carte, PlateauCarte) -> None
    ////+ get_pt_victoire()
    + choisir_action(Carte)
    */
};

class PlateauCartes{
private:
    unsigned int age =1;
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


