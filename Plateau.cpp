#include "Plateau.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>


/*-------------------------------------JetonScience-------------------------------------*/

JetonScience::JetonScience() : capacite(CapaciteScience::none) {} //si vous n'arrivez pas à lire le none, verifier qu'il y est bien dans le enum de CapaciteScience
JetonScience::JetonScience(CapaciteScience capacite) : capacite(capacite) {} //rafrechir la memoire si vous ne voyez pas le enum CapaciteScience

CapaciteScience JetonScience::get_capacite() const{return capacite;}

//fonction d'execution de la capacite du jeton science
void JetonScience::exec_capacite_science() const{
    switch (capacite) {
        case CapaciteScience::agriculture: exec_agriculture(); break;
        case CapaciteScience::architecture: exec_architecture(); break;
        case CapaciteScience::economie: exec_economie(); break;
        case CapaciteScience::loi: exec_loi(); break;
        case CapaciteScience::maconnerie: exec_maconnerie(); break;
        case CapaciteScience::urbanisme: exec_urbanisme(); break;
        case CapaciteScience::theologie: exec_theologie(); break;
        case CapaciteScience::strategie: exec_strategie(); break;
        case CapaciteScience::philosophie: exec_philosophie(); break;
        case CapaciteScience::mathematique: exec_mathematique(); break;
        default:
            std::cout << "Erreur";
    }
}

void exec_agriculture() {
    // implementation of exec_agriculture
}

void exec_architecture() {
    // implementation of exec_architecture
}

void exec_economie() {
    // implementation of exec_economie
}

void exec_loi() {
    // implementation of exec_loi
}

void exec_maconnerie() {
    // implementation of exec_maconnerie
}

void exec_urbanisme() {
    // implementation of exec_urbanisme
}

void exec_theologie() {
    // implementation of exec_theologie
}

void exec_strategie() {
    // implementation of exec_strategie
}

void exec_philosophie() {
    // implementation of exec_philosophie
}

void exec_mathematique() {
    // implementation of exec_mathematique
}

/*--------------------------------------------------------------------------*/


/*-------------------------------------JetonMalus-------------------------------------*/

//constructeur de JetonMalus
JetonMalus::JetonMalus(unsigned int m,Joueur* j): malus(m), joueur(j) {} 


void exec_malus(){
    // implementation of exec_malus
    //! ATTENTION : AJOUTER DEFINITION
}

/*--------------------------------------------------------------------------*/

/*-------------------------------------PlateauScience-------------------------------------*/

//constructeur par defaut de PlateauScience
PlateauScience::PlateauScience() {
    jeton_in_game = new JetonScience[Dim_jetons_in_game];
    liste_position = new unsigned int[Dim_liste_position];
    jeton_out_game = new JetonScience[Dim_jetons_out_game];
    for (int i = 0; i < Dim_jetons_in_game; i++) {
        jeton_in_game[i] = JetonScience();
    }
    for (int i = 0; i < Dim_jetons_out_game; i++) {
        jeton_out_game[i] = JetonScience();
    }
    for (int i = 0; i < Dim_liste_position; i++) {
        liste_position[i] = i+1;
    }
}

//constructeur de PlateauScience
PlateauScience::PlateauScience(JetonScience *in_game, JetonScience *out_game){
    jeton_in_game = new JetonScience[Dim_jetons_in_game];
    liste_position = new unsigned int[Dim_liste_position];
    jeton_out_game = new JetonScience[Dim_jetons_out_game];
    for (int i = 0; i < Dim_jetons_in_game; i++) {
        jeton_in_game[i] = in_game[i];
    }
    for (int i = 0; i < Dim_jetons_out_game; i++) {
        jeton_out_game[i] = out_game[i];
    }
    for (int i = 0; i < Dim_liste_position; i++) {
        liste_position[i] = i+1; //va de 1 à 5, 0 designe l'absence de jeton
    }
}

//ajoute un jeton science dans le tableau jeton_in_game
void PlateauScience::ajouter_jeton_in_game(JetonScience& jeton) {
    for (int i = 0; i < Dim_jetons_in_game; i++) {
        if (jeton_in_game[i].get_capacite() == CapaciteScience::none) { ////la capacité de JetonScience est inacessible directement. Comme c'est privé 
                                                                        // Erreur corrigé en rajoutant une méthode get_capacite() dans la classe JetonScience
            jeton_in_game[i] = jeton;
            liste_position[i] = i+1;
        }
        else {throw("Erreur : pas de place pour ajouter un jeton");}
    }
}

void PlateauScience::ajouter_jeton_out_game(JetonScience& jeton) {
    for (int i = 0; i < Dim_jetons_out_game; i++) {
        if (jeton_out_game[i].get_capacite() == CapaciteScience::none) {
            jeton_out_game[i] = jeton;
            liste_position[i] = i+1;
        }
        else {throw("Erreur : pas de place pour ajouter un jeton");}
    }
}

void PlateauScience::retirer_jeton_in_game(JetonScience& jeton) { //cette fonction n'existe pas dans le fichier plateau.h
    for (int i = 0; i < Dim_jetons_in_game; i++) {
        if (jeton_in_game[i].get_capacite() == jeton.get_capacite()) {
            jeton_in_game[i] = JetonScience();
            liste_position[i] = 0;
        }
        else {throw("Erreur : jeton non présent");}
    }
}

void PlateauScience::retirer_jeton_out_game(JetonScience& jeton) { //meme chose ici
    for (int i = 0; i < Dim_jetons_out_game; i++) {
        if (jeton_out_game[i].get_capacite() == jeton.get_capacite()) {
            jeton_out_game[i] = JetonScience();
            liste_position[i] = 0;
        }
        else {throw("Erreur : jeton non présent");}
    }
}

JetonScience* PlateauScience::tirer_jeton_in_game(JetonScience& jeton){
    retirer_jeton_in_game(jeton); //On retire le jeton du plateau
    return &jeton; //on renvoie le jeton retiré, pour eventuellement faire son effet
}

JetonScience* PlateauScience::tirer_jeton_out_game(){ ////pt étre faire la meme chose pour jetons_in_game??
                                                    //? Oui mais en precisant le jeton à tirer parceque c'est le joueur qui choisit, ce n'est pas aléatoire
                                                    //! JSP si il faut renvoyer un pointeur, ou carément un JetonScience ou un JetonScience&
    const unsigned int Dim_resultat = 3;
    JetonScience* resultat = new JetonScience[Dim_resultat]; //génère un tableau de 3 jetons science
    std::vector<int> liste = {1, 2, 3, 4, 5};
    // Initialisation du générateur de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());

    // Mélangez la liste pour faciliter la sélection aléatoire sans remise
    std::shuffle(liste.begin(), liste.end(), gen);

    // Choix de 3 indices distincts aléatoires
    std::vector<int> indices_choisis;
    while(indices_choisis.size() < 3) {
        int indice_aleatoire = std::uniform_int_distribution<>(0, liste.size() - 1)(gen);
        if(std::find(indices_choisis.begin(), indices_choisis.end(), indice_aleatoire) == indices_choisis.end()) {
            indices_choisis.push_back(indice_aleatoire);
        }
    }

    for (int i = 0; i < Dim_resultat; i++) {
        resultat[i] = jeton_out_game[liste[indices_choisis[i]]];
    }
    return resultat;
}

PlateauScience::~PlateauScience() {
    delete[] jeton_in_game;
    delete[] liste_position;
    delete[] jeton_out_game;
}

/*--------------------------------------------------------------------------*/


/*-------------------------------------PlateauMilitaire-------------------------------------*/

