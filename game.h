#pragma once
#include <iostream>
#include <string>


//les différente classes d'énumération 
enum class RessourcePrimaire {
    pierre,
    bois,
    brique
};

enum class RessourceSecondaire {
    verre,
    parchemin
};

enum class SymboleChainage{
    jarre,
    toneau,
    masque,
    temple, 
    soleil, 
    goute, 
    lune, 
    pilier, 
    cible, 
    casque, 
    fer_a_cheval, 
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
    globe_terrestre, 
    fil_a_plomb,
    bateau, 
};

enum class EffetGuilde{
    guilde_Armateurs,
    guilde_Batisseurs,
    guilde_Commercants,
    guilde_Magistrats,
    guilde_Tacticiens,
    guilde_Scientifiques,
    guilde_Usuriers
};

enum class Capacite{
    rejouer,
    detruire_carte_marron,
    detruire_carte_grise,
    jouer_carte_defausse,
    gagner_monnaie,
    avancee_militaire,
    choisir_jeton_science,
    ajouter_symbole_science    
};

enum class CapaciteScience{
    agriculture,
    architecture,
    economie,
    loi,
    maconnerie,
    urbanisme,
    theologie,
    strategie,
    philosophie,
    mathematique
};

//______________________________________________________________________________________________________________________________//
//les classes des cartes
class Carte{
private:
    unsigned int age;
    unsigned int cout_construction;
    RessourcePrimaire materiauxPrimaires[4];
    RessourceSecondaire materiauxSecondaires[2];


public:

    //constructeur
    Carte();

    //methodes
    void setAge(int newAge);
    int getAge() const;

    //methode virtuelle pure, cad est appelable uniquement par les classes filles, et à definir pour chaques classes filles
    //permet d'activer le polymorphisme pour toutes les classes filles 
    virtual string gettype() const = 0;

    //destructeur
    virtual ~Carte();
};
/*pour la classe carte, c'est compliqué de faire la variable cout de production qui est une liste de 
RessourcesPrimaires et RessourcesSecondaires à la fois. 
Vaut mieux pt étre créer deux variable materiauxPrim et materiauxSecond
*/
//REPONSE : je suis d'accord avec toi sur ce point

class Merveille : public Carte{
private:
    unsigned int pt_victoire;
    RessourceSecondaire productionSecondaire[3];
    RessourcePrimaire productionPrimaire[3];
    Capacite capacite[3];

public:
    //constructeur 

    //void execCapacite(list Capacite);
    string gettype() const override;

    //destructeur
    virtual ~Merveille();
};

//cartes Marrons
class CarteRessourcePrimaire : public Carte{
private:
    RessourcePrimaire production[2]; //certaines cartes peuvent produire 2 ressources

public:
    //constructeur

    //methodes
    string gettype() const override;

    //destructeur
    virtual ~CarteRessourcePrimaire();
};

//cartes Grises
class CarteRessourceSecondaire : public Carte{
private:
    RessourceSecondaire production;  //Pas de liste car produit toujours 1 seul ressource

public:
    string gettype() const override;

    //destructeur
   virtual  ~CarteRessourceSecondaire();
};

//cartes Jaunes
class CarteCommerce : public Carte{
private:
    RessourcePrimaire productionPrimaire[3];
    RessourceSecondaire productionSecondaire[2];
    Capacite capacite;
    bool choix;
    bool contrepartie;
    unsigned int pt_victoire;

public:
    void execCapacite();
    string gettype() const override;

    //destructeur
    virtual ~CarteCommerce();

};


//Cartes Vertes
class CarteScience : public Carte{
private:
    SymboleScience symbole_science;
    SymboleChainage symbole_chainage;
    unsigned int pt_victoire;
    //Capacite capacite; //il faut pt étre pas rajouter ca ici. On déclence la capacite ssi il ya deux cartes avec meme symbole scientifique
public:
    void execCapacite();
    string gettype() const override;

    //destructeur
    virtual ~CarteScience();

};

//carte Rouges
class CarteMilitaire : public Carte{
private:
    Capacite capacite;
    SymboleChainage symbole_chainage;

public:
    void execCapacite();
    string gettype() const override;

    //destructeur
    virtual ~CarteMilitaire();
};

//cartes Bleues
class CartePrestige : public Carte{
private:
    unsigned int pt_victoire;
    SymboleChainage symbole_chainage;

public:
    string gettype() const override;


    //destructeur
    virtual ~CartePrestige();
};

//cartes Violets
class CarteGuilde : public Carte{
private:
    EffetGuilde effet_guilde;

public:
    void execEffetGuilde();
    string gettype() const override;
    
    //destructeur
    virtual ~CarteGuilde();
};

//__________________________________________________________________________________________________________________//
//les classes des jetons

class JetonScience{
private:
    CapaciteScience capacite;

public:

    //destructeur
    ~JetonScience();
};

class Joueur{
private:
    Carte* cartes_construite[60];
    JetonScience jetons_science[6];
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

   //destructeur
   ~Joueur();
};


class JetonMilitaire{
private:
    Capacite capacite;
    Joueur joueur_cible;

public:
    void execCapacite();

    //destructeur
    ~JetonMilitaire();
};

//__________________________________________________________________________________________________________________//
//les classes des plateaux

class PLateauMilitaire{
private:
    unsigned int avance;
    JetonMilitaire liste_JetonMilitaire[4];
    Joueur deriere; //le joueur perdant militairement

public:
//updateavance(unsigned int, Joueur)
//retirerjeton(Jeton in JetonMalus)

    //destructeur
    ~PLateauMilitaire();
};

class CarteEnJeu{
private:
    Carte& carte;
    int position;
    bool accessible;
    bool visible;

public:
    ~CarteEnJeu();


};

class PlateauCartes{
private:
    unsigned int age;
    CarteEnJeu carte_en_jeu[20]; 
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

class PLateauScience{
private:
    JetonScience jeton_in_game[5];
    JetonScience jeton_out_game[30];

public:

    // tirerjeton() -> JetonScience[3]
    // retirerJeton(unsigned int : position) -> None
    ~PLateauScience();
};



