#pragma once
#include <iostream>
#include <string>
using namespace std;


//les différente classes d'énumération 
enum class RessourcePrimaire {
    Pierre,
    Bois,
    Brique
};

enum class RessourceSecondaire {
    verre,
    parchemin
};

enum class SymboleChainage{
    Jarre,
    toneau,
    masque,
    temple, 
    soleil, 
    goute, 
    lune, 
    pilier, 
    cible, 
    casque, 
    feracheval, 
    epee, 
    tour, 
    lyre, 
    engrenage, 
    livre, 
    lampe 
};

enum class SymboleScience{
    roue, 
    plume, 
    pilon,
    balance, 
    globeterrestre, 
    filaplomb,
    bateau, 
};

enum class EffetGuilde{
    GuildeArmateurs,
    GuildeBatisseurs,
    GuildeCommercants,
    GuildeMagistrats,
    GuildeDesTacticiens,
    GuildeDesScientifiques,
    GuildeUsuriers
};

enum class Capacite{
    rejouer,
    detruirecartemarron,
    detruirecartegrise,
    jouercartedefausse,
    gagnermonnaie,
    avanceemilitaire,
    choisirjetonscience,
    ajoutersymbolescience    
};

enum class CapaciteScience{
    Agriculture,
    Architecture,
    Economie,
    Loi,
    Maconnerie,
    Urbanisme,
    Theologie,
    Strategie,
    Philosophie,
    Mathematique
};

//______________________________________________________________________________________________________________________________//
//les classes des cartes
class Carte{
private:
    unsigned int age;
    unsigned int coutconstruction;
    RessourcePrimaire MateriauxPrimaires[4];
    RessourceSecondaire MaterieuxSecondaires[2];


public:
    void setAge(int newAge) {
        if (newAge >= 1 && newAge <= 3) {
            age = newAge;
        } else {
            cout<< "Error: Age must be 1, 2, or 3." << endl;
        }
    }

    int getAge() const {
        return age;
    }

    string gettype();
};
/*pour la classe carte, c'est compliqué de faire la variable cout de production qui est une liste de 
RessourcesPrimaires et RessourcesSecondaires à la fois. 
Vaut mieux pt étre créer deux variable materiauxPrim et materiauxSecond
*/

class Merveille{
private:
    Carte c;
    unsigned int ptVictoire;
    RessourceSecondaire productionSecondaire[3];
    RessourcePrimaire productionPrimaire[3];
    Capacite capacite[3];

public:
    //void execCapacite(list Capacite);
};

//cartes Marrons
class CarteRessourcePrimaire{
private:
    RessourcePrimaire production[2]; //certaines cartes peuvent produire 2 ressources

public:
};

//cartes Grises
class CarteRessourceSecondaire{
private:
    RessourceSecondaire production;  //Pas de liste car produit toujours 1 seul ressource

public:
};

//cartes Jaunes
class CarteCommerce{
private:
    RessourcePrimaire productionPrimaire[3];
    RessourceSecondaire productionSecondaire[2];
    Capacite capacite;
    bool choix;
    bool contrepartie;
    unsigned int ptVictoire;

public:
    void execCapacite();

};


//Cartes Vertes
class CarteScience{
private:
    SymboleScience symbole_science;
    SymboleChainage symbole_chainage;
    unsigned int ptVictoire;
    //Capacite capacite; //il faut pt étre pas rajouter ca ici. On déclence la capacite ssi il ya deux cartes avec meme symbole scientifique
public:
    void execCapacite();

};

//carte Rouges
class CarteMilitaire{
private:
    Capacite capacite;
    SymboleChainage symbole_chainage;

public:
    void execCapacite();
};

//cartes Bleues
class CartePrestige{
private:
    unsigned int ptVictoire;
    SymboleChainage symbole_chainage;

public:

};

//cartes Violets
class CarteGuilde{
private:
    EffetGuilde effet_guilde;

public:
    void execEffetGuilde();
};

//__________________________________________________________________________________________________________________//
//les classes des jetons

class JetonScience{
private:
    CapaciteScience capacite;

public:
};

class Joueur{
private:
    Carte cartesconstruite[60];
    JetonScience jetonsscience[6];
    unsigned int piece;

public:
/*
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


class JetonMilitaire{
private:
    Capacite capacite;
    Joueur joueurCible;

public:
    void execCapacite();
};

//__________________________________________________________________________________________________________________//
//les classes des plateaux

class PLateauMilitaire{
private:
    unsigned int avance;
    JetonMilitaire listJetonsMilitaire[4];
    Joueur deriere; //le joueur perdant militairement

public:
//updateavance(unsigned int, Joueur)
//retirerjeton(Jeton in JetonMalus)
};

class CarteEnJeu{
private:
    Carte carte;
    int position;
    bool accessible;
    bool visible;

public:

};

class PlateauCartes{
private:
    unsigned int age;
    CarteEnJeu carte_en_jeu[20]; 
    unsigned int nb_merveilles_constr;
    Carte defausses[60];
public:
/*
    + addage()
    + estaccessible(Carte in listecarteenjeu)
    + estprise(Carte in listecarteenjeu)
    + estdefausse(Carte in listrecarteenjeu)
    + getcartevisible()
    + getcarteaccessibles()
    */
};

class PLateauScience{
private:
    JetonScience jeton_in_game[5];
    JetonScience jeton_out_game[30];

public:

    // tirerjeton() -> JetonScience[3]
    // retirerJeton(unsigned int : position) -> None
};


