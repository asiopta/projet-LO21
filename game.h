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
protected:
    //dans la dernière version de l'UML, seul Plateau carte donne l'age.
    unsigned int cout_construction;
    //comment distinguer le cout de construction pour chaque joueur? //pour moi, on l'obtient avec le joueur donnée en effectuant getcout(&Joueur)
    //cout_construction désigne uniquement le cout initial de la carte, auquel va venir s'ajouter des couts supplémentaires
    RessourcePrimaire* materiauxPrimaires;
    RessourceSecondaire* materiauxSecondaires;
    bool accessible;
    bool facevisible;
    unsigned int position; //Je propose qu'on mette la position de la carte directement dans la classCarte, 
    //on met à 0 si elle n'est pas sur le plateau, et sinon, on commence à 1.
    //c'est interessent parceque du coup on peut faire une méthode qui verifie directement si la carte est dans le plateau
    //en faissant un if position:


public:

    //constructeur
    Carte();
    //constructeur de recopie 
    Carte(const Carte &c);
    //methodes
    void setAge(int newAge);
    int getAge() const;
    RessourcePrimaire* getMateriauxPrimaires()const{return materiauxPrimaires;} ;
    RessourceSecondaire* getMateriauxSecondaires()const{return materiauxSecondaires;};
    unsigned int getPrix() const{return cout_construction;};
    unsigned int getNbMateriauxPrimaires()const{};


    //methode virtuelle pure, cad est appelable uniquement par les classes filles, et à definir pour chaques classes filles
    //permet d'activer le polymorphisme pour toutes les classes filles 
    virtual string gettype() const = 0;

    //destructeur
    virtual ~Carte() = default;
};


class Merveille : public Carte{

private:
    unsigned int pt_victoire;
    RessourcePrimaire* productionPrimaire;
    RessourceSecondaire* productionSecondaire;
    Capacite* capacite;

public:
    //constructeur 
    //!!!il faut regarder quels entrées mettre comme const et quand utiliser des références ou pas
    Merveille(int age, RessourcePrimaire* matiere_primaire, RessourceSecondaire* matiere_secondaire, 
    unsigned int pt_victoire, RessourcePrimaire* prod_primaire, RessourceSecondaire* prod_secondaire);
    //void execCapacite(list Capacite);
    string gettype() const override;

    //destructeur
    virtual ~Merveille() = default;
};

//cartes Marrons
class CarteRessourcePrimaire : public Carte{
private:
    RessourcePrimaire production[2]; //certaines cartes peuvent produire 2 ressources

public:
    //constructeur
    CarteRessourcePrimaire(int age, int cout_construction, RessourcePrimaire* prod_primaire);
    // les cartes marron ne peuvent étre construites qu'avec la monnaie
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
    //constructeur
    CarteRessourceSecondaire(int age, int cout_construction, RessourceSecondaire prod_secondaire);

    //méthodes
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
    void execCapacite(); //pt étre à mettre comme méthode privée?
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
    Carte* cartes_construite[60]; //diviser en sous tableaux pr cartes marrons/grises construites??
    //utiliser plutot qu'un tableau une liste chainée? pour faciliter le parcours des cartes sans connaitre la taille??
    JetonScience jetons_science[6];
    unsigned int piece;
    unsigned int ptVictoire; 
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

    unsigned int getQuantiteDeRessourcePrimaire(const RessourcePrimaire& symbole){
        Carte* constr = *cartes_construite;
        unsigned int res=0;
        for(int i=0; i<60; i++){
            RessourcePrimaire* tab = constr->getMateriauxPrimaires();
            while(tab != nullptr){
                if(*tab == symbole) res++;
                tab++;
            }
        }
        return res;
    };
    unsigned int getQuantiteDeRessourceSecondaire(const RessourceSecondaire& symbole){
        Carte* constr = *cartes_construite;
        unsigned int res=0;
        for(int i=0; i<60; i++){
            RessourceSecondaire* tab = constr->getMateriauxSecondaires();
            while(tab != nullptr){
                if(*tab == symbole) res++;
                tab++;
            }
        }
        return res;
    };
    //ces deux méthodes renvoient combien de ressources sont produites d'un symbole donné
    //par ex: 2 bois ou 3 verres

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

//Dans le jeu, il n'y a pas un plateau scientifique. C'est considéré comme une partie du plateau militaire
// Do we do the same maybe?
class PLateauScience{
private:
    JetonScience jeton_in_game[5];
    JetonScience jeton_out_game[3];

public:

    // tirerjeton() -> JetonScience[3]
    // retirerJeton(unsigned int : position) -> None
    ~PLateauScience();
};


int getCout(const Carte& carte, const Joueur joueur, const Joueur adversaire);
