#ifndef JOUEUR_H
#define JOUEUR_H

#pragma once
#include <iostream>
#include <string>
#include "Carte.h"
#include "Plateau.h"
#include "controleur.h"
#include "const_and_enum.h"

#include <tuple>
#include <cstdlib>
#include <ctime>
#include <random>

//!predeclaration de classe

class Carte;
class Merveille;
class PlateauCartes;
class PlateauMilitaire;
class PlateauScience;
class JetonScience;


const unsigned int NB_MERVEILLES_JOUEUR = 4;
using Action = std::tuple<Carte*, std::string>; 

// classe pour gérer les exceptions
class SetException {
public:
	SetException(const std::string& i) :info(i) {}
	std::string getInfo() const { return info; }
private:
	std::string info;
};

/*
bool effet_maconnerie

bool effet_urbanisme

bool effet_stragegie

bool effet_mathematique

bool effet_theologie
*/



class Joueur{
/*
//TODO: terminer classe CapaciteJetons/ rajouter attribut nbJetons
//TODO: terminer classe SymboleScience
//TODO: rajouter attribut pour les merveilles non construites
//TODO: essayer de faire une fonction addEffetX()
    *je l'ai nommé addCapaciteJeton()
//TODO: fonction getNbCarte(std::string type)
//TODO: rajouter notion de symboles de chainage
//TODO: changer getteurs/setteurs;

//TODO: changer la fonction estConstructible();
//TODO: penser à comment rejouer/ maybe attribut bool rejouer;


//TODO: méthode addCarte() qui construit une carte gratuitement
//TODO: fonction retirerCarte();

//TODO: rajouter les effets guildes et les méthodes qui vont avec
//TODO: changer constructeurs/ destructeurs;
//TODO: termine getCout();

TODO: estConstructible()
TODO: changer la fonction construireCarte(carte);
TODO; defausserCarte(carte)
//TODO: choisirJetons()




*/

private:
    Carte* cartes_construite[60];
    Merveille* merveille_construite[5];
    Merveille* merveille_non_construite[5];
    unsigned int nb_jetons;
    unsigned int monnaie;
    unsigned int pt_victoire;
    bool rejouer = false;
    class Ressource{
    public:
        unsigned int bois;
        unsigned int pierre;
        unsigned int brique;
        unsigned int verre;
        unsigned int parchemin;
        
        bool forum; //verre ou parchemin
        bool caravanserail; //bois ou brique ou pierre

        Ressource():bois(0), pierre(0), brique(0), verre(0), parchemin(0), forum(false), caravanserail(false){};
        Ressource(const Ressource& r) = default;
        ~Ressource() = default;
    };
    Ressource ressources;

    struct CapaciteJeton{
        //attributs
        bool architecture;
        bool economie;
        bool maconnerie;
        bool mathematiques;
        bool strategie;
        bool theologie;
        bool urbanisme;

        /*
        les capacites de ces jetons vont étre appelé potentiellement à chaque tour du joueur
        les autres jetons ont un effet immédiat et donc pas besoin de les préciser ici
        -pour le jeton agriculture, il suffit juste de rajouter 6 pièces et 4 ptVictoire qd on le construit
        -pour le jeton loi, il suffit de rajouter 1 "autre" à l'attribut symboles_science
        -jetons philo: rajouter 7 ptVictoire
        *j'ai choisi d'appliquer l'effet des capacites immédiatesdans la méthode setCapacite()
        *Donc, lorsque un jeton est construit, il suffit seulement d'appliquer setCapacite() est on est bon
        * il reste à voir comment appliquer les capacités long-terme

        !On peut utiliser cette meme classe pour rajouter potentiellement d'autres capacités à long terme qui ne sont pas liés au jetonsScience
        */
        //méthodes
        CapaciteJeton(): architecture(false), economie(false), maconnerie(false), mathematiques(false), strategie(false),
            theologie(false), urbanisme(false){};
        CapaciteJeton(const CapaciteJeton& cap) = default;
        ~CapaciteJeton() = default;
        CapaciteJeton& operator=(const CapaciteJeton& capacite) = default;


    };
    CapaciteJeton capacites;

    struct SymbolesScience{
        //attributs
        unsigned int roue = 0;
        unsigned int plume = 0;
        unsigned int pilon = 0;
        unsigned int balance = 0;
        unsigned int globe_terrestre = 0;
        unsigned int fil_a_plomb = 0;
        unsigned int bateau = 0;
        bool autre = false; //cet attribut sera converti en true si le jeton loi est construit
        // on pourra donc compter un symboleScience de plus s'il est à true

        //méthodes
        SymbolesScience() = default;
        SymbolesScience(const SymbolesScience& s) = default;
        ~SymbolesScience() = default;
        SymbolesScience& operator=(const SymbolesScience& symbole_science) = default;
    };
    SymbolesScience symboles_science;

    struct SymbolesChainage{
        //attributs
        bool jarre = false;
        bool toneau = false;
        bool masque = false;
        bool temple = false;
        bool soleil = false;
        bool goute = false;
        bool lune = false;
        bool pilier = false;
        bool cible = false;
        bool casque = false;
        bool fer_a_cheval = false;
        bool epee = false;
        bool tour = false;
        bool lyre = false;
        bool engrenage = false;
        bool livre = false;
        bool lampe = false;

        //méthodes
        SymbolesChainage() = default;
        SymbolesChainage(const SymbolesChainage& s) = default;
        ~SymbolesChainage() = default;

    };
    SymbolesChainage symboles_chainage;

    struct Effets{
        //attributs
        bool guilde_armateurs = false;
        bool guilde_batisseurs = false;
        bool guilde_commercants = false;
        bool guilde_magistrats = false;
        bool guilde_tacticiens = false;
        bool guilde_scientifiques = false;
        bool guilde_usuriers = false;

        bool depot_pierre = false;
        bool depot_argile = false;
        bool depot_bois = false;
        bool douanes = false;


        //méthodes
        Effets() = default;
        Effets(const Effets& effets_guilde) = default;
        ~Effets() = default;
        Effets& operator=(const Effets& effet_guilde) = default;

    };
    Effets effets;

public:
    //constructeurs
    Joueur(); // review
    Joueur(const Joueur& j); //review
    // Joueur& operator=(const Joueur& j); //review
    bool operator==(const Joueur& j); // review

    //destructeur
    ~Joueur(); // review

    /* ------les getteurs ----*/
    //getteur de monnaie et pt_victoire
    unsigned int getMonnaie() const { return monnaie; }; //ok
    unsigned int getPtVictoire()const { return pt_victoire; }; //ok
    //getteur de Nb de Cartes / jetons
    unsigned int getNbCartesConstruites() const; //ok
    unsigned int getNbMerveillesConstruites()const; //ok
    unsigned int getNbMerveillesNonConstruites()const; //ok
    unsigned int getNbJetonsScience() const {return nb_jetons;}; //ok
    SymbolesScience getSymbolesScience() const {return symboles_science;}; //ok
    CapaciteJeton getCapacitesJetons() const {return capacites;}; //ok
    Effets getEffetsGuilde() const { return effets;} ; //ok
    SymbolesChainage getSymbolesChainage() const {return symboles_chainage;}; //ok
    unsigned int getNbCartesType(std::string type) const; // review
    //getteurs de ressources produites. par ex: 2 bois ou 3 verres
    unsigned int getQuantiteDeRessourcePrimaire(const RessourcePrimaire& symbole) const; //ok
    unsigned int getQuantiteDeRessourceSecondaire(const RessourceSecondaire& symbole) const ; //ok
    Ressource* getRessources(){return &ressources;}; //review
    bool getRejouer() const {return rejouer;}; //ok
    Carte** getCartesConstruites() {return cartes_construite;}; //review
    
    Merveille** getMerveillesNonConstruites(){ return merveille_non_construite;}
    bool isInMerveillesNonConstruites(Merveille* merveille);

    //setteurs générales
    void setMonnaie(unsigned int argent){ monnaie = argent; }; //ok
    void setPtVictoire(unsigned int p){ pt_victoire = p;}; //ok
    void setRessource(RessourcePrimaire rp, unsigned int quantite); //review
    void setRessource(RessourceSecondaire rs, unsigned int quantite); //review
    void addCapaciteJeton(const CapaciteScience& jeton); //review
    void setMerveille(Merveille* merveille); //rajoute merveilles à celles non construites
    
    
    //méthodes de l'attribut rejouer
    void setRejouerTrue(){rejouer = true;}; //ok
    void setRejouerFalse(){rejouer = false;}; //ok


    //méthodes de jetons
    void construireJeton(JetonScience* jeton); //construit le jeton pour le joueur
    
    
    //méthodes de l'attribut symboles_science
    unsigned int getNbSymbolesScience()const; //review
    bool gagneScientifiquement() const {return getNbSymbolesScience() >= 6;};//review
    void addSymboleScience(const SymboleScience s, PlateauScience* plateau_science); //review
    void addSymboleBalance() {symboles_science.balance++;}; //review
    void removeSymboleScience(SymboleScience& s); // review


    //méthodes spécifiques à l'attribut ressources
    void ajouterRessource(RessourcePrimaire rp, unsigned int quant); //ok
    void ajouterRessource(RessourceSecondaire rs, unsigned int quant); //ok
    void retirerRessource(RessourcePrimaire rp, unsigned int quant); //ok
    void retirerRessource(RessourceSecondaire rs, unsigned int quant); //ok

    //méthodes pour effets_guilde*
    void addEffetGuilde(EffetGuilde effet);
    void removeEffetGuilde(EffetGuilde effet);

    //méthodes spécifiques à l'attribut symboles_chainage
    void setSymboleChainage(SymboleChainage s, bool var); //review
    void addSymboleChainage(SymboleChainage s); // review
        // à appeler à chaque fois qu'on construit une carte
    void removeSymboleChainage(SymboleChainage s); // review
        //à appeler à chaque fois qu'on supprime une des cartes construites par le joueur
    bool possedeSymboleChainage(SymboleChainage s) const; //ok

    //méthodes d'update
    void gagnerArgent(int argent); //ok
    void gagnerPtVictoire(unsigned int p); //ok

    //méthodes de vérification

    //déconstruire une carte
    void retirerCarte(Carte* carte); //! à utiliser que avec CarteRessourcesPrimaire/Secondaire

    //méthodes qui permettent de rajouter une carte
    void updateRessourcesCarte(Carte* carte); //review
    //! à utiliser qd on contruit une carte 
    void updatePtVictoireCarte(Carte* carte); //review
    void updateSymbolesChainageCarte(Carte* carte); // review
    void updateSymbolesScienceCarte(Carte* carte, PlateauScience* plateau_science); //review
    void updateEffetsGuilde(Carte* carte); //review
    void addCarte(Carte* carte, PlateauScience* plateau_science); // review

    //construire une carte
    unsigned int getCout(const Carte& carte, Joueur& adversaire); //review



    //void construireMerveille(Merveille& merveille, PlateauCartes& p); //à faire
    
    virtual Carte* choisirCarte(Carte** liste_cartes, unsigned int taille_tableau);
    virtual Merveille* choisirCarte(Merveille** liste_merveilles, unsigned int taille_tableau);
    virtual JetonScience* choisirJetonScience(JetonScience** liste_jetons, unsigned int taille_tableau);
    Action choisir_action(PlateauCartes* p);
    virtual Action choisir_action(Action* actions);
    //* une fonction qui prend en entrée les Controleur::actionsLegales() et retourne l'action choisie par le joueur 

/*
    + get_cout(Carte) -> unsigned int (monnaie) //** existe deja dans carte ?
    //** on doit décider si getCout() est une fonction de joueur ou carte. parcequ'on a besoin des deux classes.
    //** on peut aussi la considérer comme une fonction à part qui prend les deux classes comme entrées
    //** je pense meme que c'est pt étre une fonction de controleur
    */
};




class IARandom: public Joueur{


public:
    Action choisir_action(Action* actions) override ; 
    Carte* choisirCarte(Carte** liste_cartes, unsigned int taille_tableau) override;
    //Merveille* choisirCarte(Merveille** liste_merveilles, unsigned int taille_tableau) override;

    Merveille* choisirMerveille(Merveille** liste_merveille, unsigned int taille_tableau);

    JetonScience* choisirJetonScience(JetonScience** liste_jetons, unsigned int taille_tableau) override;

};


// TypeCarte hashit(std::string const& type);

#endif