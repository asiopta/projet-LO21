#pragma once
#include <iostream>
#include <string>
#include <tuple>
#include "Joueur.h"
#include "setup.h"
#include "Carte.h"

const unsigned int LargeurPlateauMilitaire = 9; //la largeur maxe du plateau militaire
const unsigned int TAILLE_CARTE_EN_JEU = 21; //nombre de cartes en jeu
const unsigned int TAILLE_DEFAUSSES = 60; //nombre de cartes defaussées
const unsigned int TAILLE_MERVEILLES = 8; //nombre de merveilles


enum class CapaciteScience{
    none,
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

//surcharge de l'opérateur << pour afficher CapaciteScience
std::ostream& operator<<(std::ostream& f, const CapaciteScience& capacite) {
    switch (capacite) {
        case CapaciteScience::agriculture: f << "Agriculture"; break;
        case CapaciteScience::architecture: f << "Architecture"; break;
        case CapaciteScience::economie: f << "Économie"; break;
        case CapaciteScience::loi: f << "Loi"; break;
        case CapaciteScience::maconnerie: f << "Maçonnerie"; break;
        case CapaciteScience::urbanisme: f << "Urbanisme"; break;
        case CapaciteScience::theologie: f << "Théologie"; break;
        case CapaciteScience::strategie: f << "Stratégie"; break;
        case CapaciteScience::philosophie: f << "Philosophie"; break;
        case CapaciteScience::mathematique: f << "Mathématique"; break;
        default:
            f.setstate(std::ios_base::failbit);
    }
    return f;
}

/*-------------------------------------JetonScience-------------------------------------*/
class JetonScience {
private:
    CapaciteScience capacite;

public:
    JetonScience();
    JetonScience(CapaciteScience capacite);
    void exec_capacite_science(Joueur* joueur) const;
    CapaciteScience get_capacite() const;
    ~JetonScience() = default;
};


class JetonMalus{
private:
    unsigned int malus;
    unsigned int position;
    Joueur* joueur; 
    //! OK
    
public:
    JetonMalus();
    JetonMalus(unsigned int m, unsigned int position, Joueur* j);
    unsigned int get_positon()const{return position;}
    unsigned int get_malus()const{return malus;}
    Joueur* get_joueur()const{return joueur;}
    bool operator ==(const JetonMalus& other) const;
    void exec_malus(); //applique le malus pour le joueur
    ~JetonMalus() = default;
};

bool JetonMalus::operator==(const JetonMalus& other) const {
    //compair address of other and this
    return this == &other;
}


/*-------------------------------------PlateauScience-------------------------------------*/
class PlateauScience{
private:
    const int Dim_jetons_in_game = 5; //est la dimension du tableau jeton_in_game
    const int Dim_liste_position = 5; //est la dimension du tableau liste_position
    const int Dim_jetons_out_game = 5; //est la dimension du tableau jeton_out_game
    JetonScience **jeton_in_game;
    unsigned int *liste_position;
    JetonScience **jeton_out_game;

public:
    PlateauScience();
    JetonScience** tirer_jeton_out_game();
    void retirer_jeton_out_game(JetonScience& jeton);
    void retirer_jeton_in_game(JetonScience& jeton);
    void ajouter_jeton_in_game(JetonScience& jeton);
    void ajouter_jeton_out_game(JetonScience& jeton);
    ~PlateauScience();
};


/*-------------------------------------PlateauMilitaire-------------------------------------*/
class PlateauMilitaire{
    private:
        const int avance_win = 9;
        unsigned int avance;
        const int Dim_jetons_malus = 4;
        JetonMalus **liste_jetons_malus;
        Joueur& joueur_derriere;
    public:
        PlateauMilitaire(unsigned int a, Joueur& joueur_derr, Joueur& autre_joueur);
        bool gagneMilitairement(Joueur& joueur) const ; //renvoie le joueur qui a gagné militairement, nullptr sinon
        void update_avance(unsigned int a, Joueur& joueur_cible); //ajoute l'avancé militaire ajout en direction du joueur_cible
        void retirer_jeton_malus(JetonMalus& jeton);
        JetonMalus* jeton_malus_ici() const; //renvoie un jeton malus vide si il n'y en a pas, et le jeton malus sinon
        Joueur& getJoueurDerriere() const{return joueur_derriere;}
        ~PlateauMilitaire();

        //Joueur& gagneMilitairement();
        auto gagneMilitairement(); //maybe this? //! à faire
        //! une fonction qui renvoie le gagant militairement si c'est le cas sinon NULL
};


/*-------------------------------------PlateauCartes-------------------------------------*/

class PlateauCartes{
private:
    unsigned int age;
    Carte** cartes_en_jeu; //tableau dynamique de pointeurs de Carte
    Merveille** merveilles; //tableau dynamique de pointeurs de Merveille
    Carte** defausses;

public:
    PlateauCartes();
    void addAge(); //modifie carte_en_jeu en tirant de nouvelles cartes en jeu d'age age
    void ajouterCarte(Carte* carte); //ajoute la carte dans carte_en_jeu
    void prendreCarte(Carte* carte); //prend la carte si elle est accessible
    void defausserCarte(Carte* carte); //defausse la carte si elle est accessible
    void prendreMerveille(Merveille* merveille); //prend la merveille si elle est accessible
    void tirerCarteRandom(); // tire les cartes pour l'age donné /!\ supprime les cartes déjà présente dans cartes_en_jeu
    void tirerMerveilleRandom();

    bool estEnJeu(Carte* carte) const; //verifie que la carte est dans carte_en_jeu
    bool estAccessible(Carte* carte) const; //verifie que la carte est dans carte_en_jeu et est accessible
    bool estVisible(Carte* carte) const; //verifie que la carte est dans carte_en_jeu et est visible

    unsigned int getAge() const{return age;} //renvoie l'age du plateau
    Carte** getCartesEnJeu() const{return cartes_en_jeu;}
    Carte** getDefausse() const{return defausses;}
    Carte** getCartesAccessibles() const; //renvoie un tableau de pointeurs de Carte accessibles
    Carte** getCartesVisibles() const; //renvoie un tableau de pointeurs de Carte visibles
    unsigned int getNbMerveilles() const; //renvoie le nombre de merveilles restantes
   ~PlateauCartes();

   bool estVide() const; //! renvoie si il ya encore des carte sur le plateau ou pas, que ce soit l'age
};








