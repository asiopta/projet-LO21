#ifndef PLATEAU_H
#define PLATEAU_H


#pragma once
#include <iostream>
#include <string>
#include <tuple>
#include "Joueur.h"
#include "Carte.h"
#include "const_and_enum.h"


//! CONSTANTES
const unsigned int LargeurPlateauMilitaire = 9; //la largeur maxe du plateau militaire
const unsigned int TAILLE_CARTE_EN_JEU = 21; //nombre de cartes en jeu
const unsigned int TAILLE_DEFAUSSES = 60; //nombre de cartes defaussées
const unsigned int TAILLE_MERVEILLES = 8; //nombre de merveilles

//! Predeclaration de classe
class Joueur;
class Carte;
class Merveille;

//! Définition des classes




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




/*-------------------------------------PlateauScience-------------------------------------*/
class PlateauScience{
private:
    const int Dim_jetons_in_game = 5; //est la dimension du tableau jeton_in_game
    const int Dim_liste_position = 5; //est la dimension du tableau liste_position
    const int Dim_jetons_out_game = 5; //est la dimension du tableau jeton_out_game
    JetonScience** jeton_in_game;
    unsigned int* liste_position;
    JetonScience** jeton_out_game;

public:
    PlateauScience();
    JetonScience** tirer_jeton_out_game();
    void retirer_jeton_out_game(JetonScience& jeton);
    void retirer_jeton_in_game(JetonScience& jeton);
    void ajouter_jeton_in_game(JetonScience& jeton);
    void ajouter_jeton_out_game(JetonScience& jeton);
    JetonScience** getJetonInGame() const{return jeton_in_game;}
    ~PlateauScience();
};


/*-------------------------------------PlateauMilitaire-------------------------------------*/
class PlateauMilitaire{
    private:
        const int avance_win = 9;
        unsigned int avance;
        const int Dim_jetons_malus = 4;
        JetonMalus **liste_jetons_malus;
        Joueur* joueur_derriere;
    public:
        PlateauMilitaire(unsigned int a, Joueur* joueur_derr, Joueur* autre_joueur);
        bool gagneMilitairement(Joueur* joueur) const ; //renvoie le joueur qui a gagné militairement, nullptr sinon
        void update_avance(unsigned int a, Joueur* joueur_cible); //ajoute l'avancé militaire ajout en direction du joueur_cible
        void retirer_jeton_malus(JetonMalus& jeton);
        JetonMalus* jeton_malus_ici() const; //renvoie un jeton malus vide si il n'y en a pas, et le jeton malus sinon
        Joueur* getJoueurDerriere() const{return joueur_derriere;}
        unsigned int getAvance() const{return avance;}
        ~PlateauMilitaire();

        //Joueur& gagneMilitairement();
        auto gagneMilitairement(); //maybe this? //! à faire
        //! une fonction qui renvoie le gagant militairement si c'est le cas sinon NULL
};


/*-------------------------------------PlateauCartes-------------------------------------*/

class PlateauCartes{
private:
    unsigned int age;
    Carte* cartes_en_jeu[TAILLE_CARTE_EN_JEU]; //tableau dynamique de pointeurs de Carte 
    Merveille* merveilles[TAILLE_MERVEILLES]; //tableau dynamique de pointeurs de Merveille
    Carte* defausses[TAILLE_DEFAUSSES];
    unsigned int taille_defausse = 0; 

public:
    PlateauCartes();

    //**Actions du PlateauCarte**//
    void addAge(); //modifie carte_en_jeu en tirant de nouvelles cartes en jeu d'age age
    void ajouterCarte(Carte* carte); //ajoute la carte dans carte_en_jeu
    void prendreCarte(Carte* carte); //prend la carte si elle est accessible
    void defausserCarte(Carte* carte); //defausse la carte si elle est accessible
    void prendreMerveille(Merveille* merveille); //prend la merveille si elle est accessible
    void rendreAccessible(Carte* carte);

    //**Initialisation**//

    void initPlateauCarte(); //initialise le plateau de carte
    void initCarteRandom(unsigned int nombre_carte,unsigned int taille_tableau, Carte** tableau_cartes); //renvoie un tableau de pointeurs de Carte de taille nombre_carte tiré aléatoirement dans cartes
    void initMerveilleRandom(unsigned int nombre_merveille,unsigned int taille_tableau, Merveille** tableau_merveilles);
    //**Verification d'états des cartes**//
    bool estEnJeu(Carte* carte) const; //verifie que la carte est dans carte_en_jeu
    bool estAccessible(Carte* carte) const; //verifie que la carte est dans carte_en_jeu et est accessible
    bool estVisible(Carte* carte) const; //verifie que la carte est dans carte_en_jeu et est visible

    //**Getters**//
    unsigned int getAge() const{return age;} //renvoie l'age du plateau
    Carte** getCartesEnJeu() const{return const_cast<Carte**>(cartes_en_jeu);}
    Carte** getDefausse() const{return const_cast<Carte**>(defausses);}
    unsigned int getTailleDefausse() const {return taille_defausse;}
    Merveille** getMerveilles() const {return const_cast<Merveille**>(merveilles);}
    Carte** getCartesAccessibles() const; //renvoie un tableau de pointeus de Carte accessibles
    Carte** getCartesVisibles() const; //renvoie un tableau de pointeurs de Carte visibles
    unsigned int getNbMerveilles() const; //renvoie le nombre de merveilles restantes
    unsigned int getNbCartesAccessibles() const;

    //*Concernant l'état du Plateau*//
    void update_accessibilite();
    bool estVide() const; // renvoie si il ya encore des carte sur le plateau ou pas, que ce soit l'age

   ~PlateauCartes();

   
};







#endif //PLATEAU_H
