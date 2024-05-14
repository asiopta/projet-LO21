#pragma once
#include <iostream>
#include <string>
#include "Carte.h"
#include "Plateau.h"

const unsigned int NB_MERVEILLES_JOUEUR = 4;

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
TODO: méthode addCarte() qui construit une carte gratuitement

TODO: changer constructeurs/ destructeurs;
TODO: termine getCout();
TODO: changer la fonction construireCarte();



*/
private:
    Carte* cartes_construite[60];
    Merveille* merveille_construite[4];
    Merveille* merveille_non_construite[4];
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
        
        Ressource():bois(0), pierre(0), brique(0), verre(0), parchemin(0){};
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

public:
    //constructeurs
    Joueur(); // à refaire
    Joueur(const Joueur& j); //à refaire
    Joueur& operator=(const Joueur& j); //à refaire
    bool operator==(const Joueur& j); // à refaire

    //destructeur
    ~Joueur(); // à refaire

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
    SymbolesChainage getSymbolesChainage() const {return symboles_chainage;}; //ok
    unsigned int getNbCartesType(std::string type) const; // review
    //getteurs de ressources produites. par ex: 2 bois ou 3 verres
    unsigned int getQuantiteDeRessourcePrimaire(const RessourcePrimaire& symbole) const; //ok
    unsigned int getQuantiteDeRessourceSecondaire(const RessourceSecondaire& symbole) const ; //ok
    Ressource* getRessources(){return &ressources;}; //review


    //setteurs générales
    void setMonnaie(unsigned int argent){ monnaie = argent; }; //ok
    void setPtVictoire(unsigned int p){ pt_victoire = p;}; //ok
    void setRessource(RessourcePrimaire rp, unsigned int quantite); //review
    void setRessource(RessourceSecondaire rs, unsigned int quantite); //review
    void addCapaciteJeton(CapaciteScience& jeton); //review
    
    //méthodes de l'attribut rejouer
    void setRejouerTrue(){rejouer = true;}; //ok
    void setRejouerFalse(){rejouer = false;}; //ok


    //méthodes de jetons
    void construireJeton(CapaciteScience& jeton); //review
    
    //méthodes de l'attribut symboles_science
    unsigned int getNbSymbolesScience()const; //review
    bool gagneScientifiquement() const {return getNbSymbolesScience() >= 6;};//review
    void addSymboleScience(const SymboleScience s); //review
    void removeSymboleScience(SymboleScience& s); // review
    void choisirJeton(); // à faire 
    //c'est une fonction qui choisit un jeton dans le plateau et le construit

    //méthodes spécifiques à l'attribut ressources
    void ajouterRessource(RessourcePrimaire rp); //ok
    void ajouterRessource(RessourceSecondaire rs); //ok
    void retirerRessource(RessourcePrimaire rp); //ok
    void retirerRessource(RessourceSecondaire rs); //ok

    //méthodes spécifiques à l'attribut symboles_chainage
    void setSymboleChainage(SymboleChainage s, bool var); //review
    void addSymboleChainage(SymboleChainage s); // review
        // à appeler à chaque fois qu'on construit une carte
    void removeSymboleChainage(SymboleChainage s); // review
        //à appeler à chaque fois qu'on supprime une des cartes construites par le joueur
    bool possedeSymboleChainage(SymboleChainage s) const;

    //méthodes d'update
    void gagnerArgent(int argent); //ok
    void gagnerPtVictoire(unsigned int p); //ok

    //méthodes de vérification
    bool estConstructible(const Carte& carte) const; // review
    //! en gros est ce qu'on a les ressources necessaires pour construire la carte


    //méthodes qui permettent de rajouter une carte
    void updateRessourcesCarte(Carte* carte); // à faire
    void updatePtVictoireCarte(Carte* carte); //à faire
    void updateSymbolesChainageCarte(Carte* carte); // à faire
    void updateSymbolesScienceCarte(Carte* carte); //à faire
    void addCarte(Carte* carte); // à faire
    //construire une carte
    void construireCarte(Carte& carte, PlateauCartes& p); //à faire

    //autres fonctions importantes
    unsigned int getCout(const Carte& carte); //à faire bientot
    
    //void construireMerveille(Merveille& merveille, PlateauCartes& p); //à faire
    void choisir_action(PlateauCartes& p); // à faire plus tard

    


/*
    + get_cout(Carte) -> unsigned int (monnaie) //** existe deja dans carte ?
    //** on doit décider si getCout() est une fonction de joueur ou carte. parcequ'on a besoin des deux classes.
    //** on peut aussi la considérer comme une fonction à part qui prend les deux classes comme entrées
    //** je pense meme que c'est pt étre une fonction de controleur
    */
};

//PlateauCarte est maintenant dans le fichier Plateau.h

/*
* ? jsp si il faut ajouter une autre classe Jeu (comme le td) ou pas? //!je pense que non (en fait c'est controleur non ?)
* ? je suis aussi pas sur de quand utiliser le singleton //!controleur
* * en tout cas, je crois qu'on a pas à utiliser un iterator en ce moment. //!pas besoin d'iterator 
*/


//gérer age et distribuer les cartes
//piocher cartes, tt ce qui n'est pas dans les autres classes
class Controleur {
private:
	//Pioche* pioche=nullptr;
	PlateauCartes plateau_cartes;
    PlateauScience plateau_science;
    PlateauMilitaire plateau_militaire;
    Joueur joueur1;
    Joueur joueur2;
    int tour;
    //! rajouter notion d'action sous forme de tuple

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




TypeCarte hashit(std::string const& type);