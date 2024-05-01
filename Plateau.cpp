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
JetonMalus::JetonMalus() : malus(0), position(0), joueur(nullptr) {}
JetonMalus::JetonMalus(unsigned int m, unsigned int position, Joueur* j) : malus(m), joueur(j) {
    if (position > LargeurPlateauMilitaire) {
        throw("Erreur JetonMilitaire : position invalide, en dehors du PlateauMilitaire"); //si on defini une position en dehors du plateau militaire, on renvoie une erreur
    }
    else {
        this->position = position;
    }
}




void JetonMalus::exec_malus(){
    // implementation of exec_malus
    if (malus < joueur->get_monnaie()){
        joueur->set_monnaie(joueur->get_monnaie() - malus); //on retire le malus de la monnaie du joueur
    }
    else {
        joueur->set_monnaie(0); //si le malus est superieur à la monnaie du joueur, on met la monnaie à 0
    }
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

//constructeur de PlateauMilitaire
PlateauMilitaire::PlateauMilitaire(unsigned int a, Joueur& joueur_derr, JetonMalus* liste_jetons){ //! erreur normale car il manque l'operateur = pour Joueur
    unsigned int avance = a;
    Joueur& joueur_derriere = joueur_derr;
    JetonMalus* liste_jetons_malus = new JetonMalus[Dim_jetons_malus];
    for (int i = 0; i < Dim_jetons_malus; i++) {
        liste_jetons_malus[i] = liste_jetons[i];
    }
}

void PlateauMilitaire::update_avance(unsigned int ajout, Joueur& joueur_cible){
    //ajoute l'avancé militaire ajout en direction du joueur_cible
    if (joueur_cible == joueur_derriere) { //! erreur normale car il manque l'operateur == pour Joueur
        avance += ajout; //si je joueur cible est le joueur le plus derriere, on avance le pion dans sa direction et c'est tout
    }
    else {
        avance -= ajout;
        if (avance < 0) { // si le joueur cible n'est pas le joueur le plus derriere, on avance le pion en direction de l'autre joueur
            avance = abs(avance); //si avance < 0, on le rend positif et on change le joueur derriere
            joueur_derriere = joueur_cible;
        }
    }
}

JetonMalus& PlateauMilitaire::jeton_malus_ici() const{
    for(int i = 0; i < Dim_jetons_malus; i++){
        if (liste_jetons_malus[i].get_malus() != 0 and liste_jetons_malus[i].get_positon() == avance  and liste_jetons_malus[i].get_joueur() == &joueur_derriere) {
            return liste_jetons_malus[i];
        }
    }
}

void PlateauMilitaire::retirer_jeton_malus(JetonMalus& jeton) { 
    unsigned int compteur_teste = 0;
    for (int i = 0; i < Dim_jetons_malus; i++) {
        if (liste_jetons_malus[i] == jeton) { //! erreur normale car il manque l'operateur == pour JetonMalus
            liste_jetons_malus[i] = JetonMalus(); //on retire le jeton de la liste en ajoutant une jeton "neutre"
            jeton.exec_malus(); //on execute l'effet du jeton 
            compteur_teste += 1; //on incremente le compteur de jeton retiré
        }
    }
}


//destructeur de PlateauMilitaire
PlateauMilitaire::~PlateauMilitaire() {
    delete[] liste_jetons_malus;
}

