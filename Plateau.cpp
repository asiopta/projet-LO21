
#include "Plateau.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <unordered_set>

const unsigned int NB_MERVEILLES_JEU = 8;
const unsigned int NB_MERVEILLES_TOT = 12;
const unsigned int NB_CARTES_AGE_1_JEU = 20;
const unsigned int NB_CARTES_AGE_2_JEU = 20;
const unsigned int NB_CARTES_AGE_3_JEU = 17; //17 cartes d'age 3 puis 3 cartes de guilde
const unsigned int NB_CARTE_AGE_1_TOT = 23;
const unsigned int NB_CARTE_AGE_2_TOT = 23;
const unsigned int NB_CARTE_AGE_3_TOT = 20;
const int NB_CARTE_GUILDE_TOT= 7;
const int NB_CARTE_GUILDE_JEU = 3;



/*-------------------------------------JetonScience-------------------------------------*/

JetonScience::JetonScience() : capacite(CapaciteScience::none) {} //si vous n'arrivez pas à lire le none, verifier qu'il y est bien dans le enum de CapaciteScience
JetonScience::JetonScience(CapaciteScience capacite) : capacite(capacite) {} //rafrechir la memoire si vous ne voyez pas le enum CapaciteScience

CapaciteScience JetonScience::get_capacite() const{return capacite;}


//fonctions d'execution des capacités des jetons science
void exec_agriculture(Joueur* joueur) {
    // implementation of exec_agriculture
    //Le joueur prend immédiatement 6 pièce de monnaie et 4 point de victoire 
    joueur->gagnerArgent(6);
    joueur->gagnerPtVictoire(4);
}

void exec_architecture(Joueur* joueur) {
    // implementation of exec_architecture
    //les prochaines Merveilles construites par le joueur coûteront 2 ressources en moins
    joueur->addCapaciteJeton(CapaciteScience::architecture);  //!ajouter dans joueur un bool effet_architecture
}

void exec_economie(Joueur* joueur) {
    // implementation of exec_economie
    //le joueurs recupère l'agent depensé par son adversaire lors de l'achat de ressource de commerce 
    joueur->addCapaciteJeton(CapaciteScience::economie);  //addEffetEconomie est une méthode de la classe Joueur qui ajoute un effet de carte economie
    //!ajouter dans joueur un bool effet_economie
}

void exec_loi(Joueur* joueur) {
    // implementation of exec_loi
    //Rapport un symbole science balance
    joueur->addSymboleBalance(); //addSymboleScience est une méthode de la classe Joueur qui ajoute un symbole science balance
}

void exec_maconnerie(Joueur* joueur) {
    // implementation of exec_maconnerie
    //les cartes bleues sont reduites de deux ressources 
    joueur->addCapaciteJeton(CapaciteScience::maconnerie);  //addEffetMaconnerie est une méthode de la classe Joueur qui ajoute un effet de carte maconnerie
    //! ajouter dans joueur un bool effet_maconnerie

}

void exec_urbanisme(Joueur* joueur) {
    // implementation of exec_urbanisme
    //A chaque fois que le joueur construit un batiment avec l'effet chainage il gagne 6 pièces de monnaie
    joueur->gagnerArgent(6);
    joueur->addCapaciteJeton(CapaciteScience::urbanisme);  //addEffetUrbanisme est une méthode de la classe Joueur qui ajoute un effet de carte urbanisme
}   //!ajouter dans joueur un bool effet_urbanisme

void exec_theologie(Joueur* joueur) {
    // implementation of exec_theologie
    //les merveilles du joueur ont l'Effet rejouer 
    joueur->addCapaciteJeton(CapaciteScience::theologie);  //addEffetTheologie est une méthode de la classe Joueur qui ajoute un effet de carte theologie
    //!ajouter dans joueur un bool effet_theologie

        //on ne peut pas ajouter des effets de types rejouer à une merveille directement car certaines merveilles peuvent etre 
        //volé par l'autre joueur et l'effet rejouer serai alors conservé par le joueur qui a volé la merveille, ce qui n'est pas le but
}

void exec_strategie(Joueur* joueur) {
    // implementation of exec_strategie
    //Le joueur avance le pion militaire de 1 de plus a chaque batiment militaire construit
    joueur->addCapaciteJeton(CapaciteScience::strategie);  //addEffetStrategie est une méthode de la classe Joueur qui ajoute un effet de carte strategie
    //!ajouter dans joueur un bool effet_strategie
}

void exec_philosophie(Joueur* joueur) {
    // implementation of exec_philosophie
    //le joueur gagne 7 points de victoire
    joueur->gagnerPtVictoire(7);
}

void exec_mathematique(Joueur* joueur) {
    // implementation of exec_mathematique
    //A la fin de la partie le joueur marque 3 point de victoire pour chaque jeton Progès Possédé
    joueur->addCapaciteJeton(CapaciteScience::mathematique);  //addEffetMathematique est une méthode de la classe Joueur qui ajoute un effet de carte mathematique
    //!ajouter dans joueur un attribut qui compte le nombre de jeton science possédé
    //!ajouter dans joueur un bool effet_mathematique
}


void JetonScience::exec_capacite_science(Joueur* joueur) const{
    switch (capacite) {
        case CapaciteScience::agriculture: exec_agriculture(joueur); break;
        case CapaciteScience::architecture: exec_architecture(joueur); break;
        case CapaciteScience::economie: exec_economie(joueur); break;
        case CapaciteScience::loi: exec_loi(joueur); break;
        case CapaciteScience::maconnerie: exec_maconnerie(joueur); break;
        case CapaciteScience::urbanisme: exec_urbanisme(joueur); break;
        case CapaciteScience::theologie: exec_theologie(joueur); break;
        case CapaciteScience::strategie: exec_strategie(joueur); break;
        case CapaciteScience::philosophie: exec_philosophie(joueur); break;
        case CapaciteScience::mathematique: exec_mathematique(joueur); break;
        default:
            std::cout << "Erreur";
    }
    delete this; //on supprime le jeton science après avoir executé son effet
}


/*--------------------------------------------------------------------------*/


/*-------------------------------------JetonMalus-------------------------------------*/

//constructeur de JetonMalus
JetonMalus::JetonMalus() : malus(0), position(0), joueur(nullptr) {std::cout<<"ici JetonMalus::JetonMalus()"<<std::endl;}
JetonMalus::JetonMalus(unsigned int m, unsigned int position, Joueur* j) : malus(m), joueur(j) {
    // std::cout<<"ici JetonMalus::JetonMalus() : debut de construction"<<std::endl; //!test
    if (position > LargeurPlateauMilitaire) {
        throw("Erreur JetonMilitaire : position invalide, en dehors du PlateauMilitaire"); //si on defini une position en dehors du plateau militaire, on renvoie une erreur
    }
    else {
        this->position = position;
    }
    // std::cout<<"ici JetonMalus::JetonMalus() : fin de construction"<<std::endl; //!test
}

bool JetonMalus::operator==(const JetonMalus& other) const {
    //compair address of other and this
    return this == &other;
}



void JetonMalus::exec_malus(){
    // implementation of exec_malus
    if (malus < joueur->getMonnaie()){
        joueur->setMonnaie(joueur->getMonnaie() - malus); //on retire le malus de la monnaie du joueur
    }
    else {
        joueur->setMonnaie(0); //si le malus est superieur à la monnaie du joueur, on met la monnaie à 0
    }
}

/*--------------------------------------------------------------------------*/

/*-------------------------------------PlateauScience-------------------------------------*/

//constructeur par defaut de PlateauScience
PlateauScience::PlateauScience() {
    // std::cout<<"ici PlateauScience::PlateauScience"<<std::endl; //!test
    
    jeton_in_game = new JetonScience*[Dim_jetons_in_game];
    // std::cout<<"Init de jeton in game fini"<<std::endl; //!test
    liste_position = new unsigned int[Dim_liste_position];
    // std::cout<<"Init de liste_positon fini"<<std::endl; //!test
    jeton_out_game = new JetonScience*[Dim_jetons_out_game];
    // std::cout<<"Init de jeton out game fini"<<std::endl; //!test

    std::vector<CapaciteScience> capacites = {
        CapaciteScience::agriculture,
        CapaciteScience::architecture,
        CapaciteScience::economie,
        CapaciteScience::loi,
        CapaciteScience::maconnerie,
        CapaciteScience::urbanisme,
        CapaciteScience::theologie,
        CapaciteScience::strategie,
        CapaciteScience::philosophie,
        CapaciteScience::mathematique
    };

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(capacites.begin(), capacites.end(), g);

    int j = 0;
    for (int i = 0; i < Dim_jetons_in_game; i++) {
        jeton_in_game[i] = new JetonScience(capacites[j]);
        j++;
        // std::cout<<"construct Plateauscience: jetons in game" << jeton_in_game[i]->get_capacite()<<std::endl; //!test

    }
    for (int i = 0; i < Dim_jetons_out_game ; i++) {
        jeton_out_game[i] = new JetonScience(capacites[j]);
        j++;
        // std::cout<<"construct Plateauscience: jeton out game" << jeton_out_game[i]->get_capacite()<<std::endl; //!test

    }
    for (int i = 0; i < Dim_liste_position; i++) {
        liste_position[i] = i+1;
    }
    // std::cout<<"Changement de value des listes + fin du constructeur JetonScience"<<std::endl; //!test
}


//ajoute un jeton science dans le tableau jeton_in_game
void PlateauScience::ajouter_jeton_in_game(JetonScience& jeton) {
    for (int i = 0; i < Dim_jetons_in_game; i++) {
        if (jeton_in_game[i]->get_capacite() == CapaciteScience::none) { //! changement de signe effectué
            jeton_in_game[i] = &jeton;
            liste_position[i] = i+1;
        }
        else {throw("Erreur : pas de place pour ajouter un jeton");}
    }
}

void PlateauScience::ajouter_jeton_out_game(JetonScience& jeton) {
    for (int i = 0; i < Dim_jetons_out_game; i++) {
        if (jeton_out_game[i]->get_capacite() == CapaciteScience::none) { //! changement de signe effectué
            jeton_out_game[i] = &jeton;
            liste_position[i] = i+1;
        }
        else {throw("Erreur : pas de place pour ajouter un jeton");}
    }
}

void PlateauScience::retirer_jeton_in_game(JetonScience& jeton) { //cette fonction n'existe pas dans le fichier plateau.h
    for (int i = 0; i < Dim_jetons_in_game; i++) {
        if (jeton_in_game[i]->get_capacite() == jeton.get_capacite()) {
            jeton_in_game[i] = nullptr;
            liste_position[i] = 0;
        }
        else {throw("Erreur : jeton non présent");}
    }
}

void PlateauScience::retirer_jeton_out_game(JetonScience& jeton) { //meme chose ici
    for (int i = 0; i < Dim_jetons_out_game; i++) {
        if (jeton_out_game[i]->get_capacite() == jeton.get_capacite()) {
            jeton_out_game[i] = nullptr;
            liste_position[i] = 0;
        }
        else {throw("Erreur : jeton non présent");}
    }
}


/*
JetonScience** PlateauScience::tirer_jeton_out_game(){ //renvoie un tableau de 3 jetons science tiré depuis l'exterieur du jeu. 
    const unsigned int Dim_resultat = 3;
    JetonScience** resultat = new JetonScience*[Dim_resultat]; //génère un tableau de 3 jetons science
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

        std::cout<<"tirer_jeton_out_game: jeton: "<< resultat[i]->get_capacite() <<std::endl; //!test

    }
    return resultat;
}
*/

JetonScience** PlateauScience::tirer_jeton_out_game() { 
    const unsigned int Dim_resultat = 3;
    JetonScience** resultat = new JetonScience*[Dim_resultat]; // Génère un tableau de 3 jetons science

    std::vector<JetonScience*> valid_jetons;
    for (int i = 0; i < Dim_jetons_out_game; i++) {
        if (jeton_out_game[i] != nullptr) {
            valid_jetons.push_back(jeton_out_game[i]);
        }
    }

    if (valid_jetons.size() < Dim_resultat) {
        delete[] resultat;
        throw SetException("tirer_jeton_out_game: pas assez de jetons valides pour choisir");
    }

    // Initialisation du générateur de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());

    // Mélangez la liste pour faciliter la sélection aléatoire sans remise
    std::shuffle(valid_jetons.begin(), valid_jetons.end(), gen);

    // Choix des premiers Dim_resultat éléments après mélange
    for (unsigned int i = 0; i < Dim_resultat; i++) {
        resultat[i] = valid_jetons[i];

        // std::cout << "tirer_jeton_out_game: jeton: " << resultat[i]->get_capacite() << std::endl; //!test
    }

    return resultat;
}



PlateauScience::~PlateauScience() {
    for (int i = 0; i < Dim_jetons_in_game; i++) {
        delete jeton_in_game[i];
    }
    delete[] jeton_in_game;
    delete[] liste_position;
    for (int i = 0; i < Dim_jetons_out_game; i++) {
        delete jeton_out_game[i];
    }
    delete[] jeton_out_game;
}

/*--------------------------------------------------------------------------*/


/*-------------------------------------PlateauMilitaire-------------------------------------*/




//constructeur de PlateauMilitaire
PlateauMilitaire::PlateauMilitaire(unsigned int a, Joueur* joueur_derr, Joueur* autre_joueur)
    : avance(a), joueur_derriere(joueur_derr)
{   
    liste_jetons_malus = new JetonMalus*[Dim_jetons_malus];
    // std::cout<<"ici PlateauMilitaire::PlateauMilitaire"<<std::endl;
    liste_jetons_malus[0] = new JetonMalus(2, 3, joueur_derr);
    // std::cout<<"ici PlateauMilitaire::PlateauMilitaire : jeton 1 construit"<<std::endl; //!test
    // liste_jetons_malus[1] = new JetonMalus(5, 6, joueur_derr);
    liste_jetons_malus[1] = new JetonMalus(2, 3, joueur_derr);
    // std::cout<<"ici PlateauMilitaire::PlateauMilitaire : jeton 2 construit"<<std::endl; //!test
    liste_jetons_malus[2] = new JetonMalus(2, 3, autre_joueur);
    // std::cout<<"ici PlateauMilitaire::PlateauMilitaire : jeton 3 construit"<<std::endl; //!test
    liste_jetons_malus[3] = new JetonMalus(5, 6, autre_joueur);
    // std::cout<<"ici PlateauMilitaire::PlateauMilitaire : jeton 4 construit"<<std::endl; //!test

    // std::cout<<"ici PlateauMilitaire::PlateauMilitaire : joueur_derriere= "<< joueur_derriere <<std::endl; //!test

    // std::cout<<"ici PlateauMilitaire::PlateauMilitaire : fin de construction"<<std::endl; //!test

}

void PlateauMilitaire::update_avance(unsigned int ajout, Joueur* joueur_cible){
    //ajoute l'avancé militaire ajout en direction du joueur_cible
    if (joueur_cible == joueur_derriere) {
        // std::cout<<"ici PlateauMilitaire::update_avance : joueur_derriere= "<< joueur_derriere <<std::endl; //!test
        // std::cout<<"ici PlateauMilitaire::PlateauMilitaire : joueur_cible= "<< joueur_cible <<std::endl; //!test


        avance += ajout; //si je joueur cible est le joueur le plus derriere, on avance le pion dans sa direction et c'est tout
    }
    else {
        if (avance - ajout < 0) { // si le joueur cible n'est pas le joueur le plus derriere, on avance le pion en direction de l'autre joueur
            avance = ajout-avance; //si avance < 0, on le rend positif et on change le joueur derriere
            joueur_derriere = joueur_cible;
            // std::cout<<"ici PlateauMilitaire::update_avance : joueur_derriere= "<< joueur_derriere <<std::endl; //!test
            // std::cout<<"ici PlateauMilitaire::PlateauMilitaire : joueur_cible= "<< joueur_cible <<std::endl; //!test
        }
    }
}

JetonMalus* PlateauMilitaire::jeton_malus_ici() const{
    for(int i = 0; i < Dim_jetons_malus; i++){
        if (liste_jetons_malus[i] != nullptr){
            if (liste_jetons_malus[i]->get_malus() != 0 and liste_jetons_malus[i]->get_positon() == avance  and liste_jetons_malus[i]->get_joueur() == joueur_derriere) {
                return liste_jetons_malus[i];
            }
        }
    }
    return nullptr; // si aucun jeton trouvé on renvoie nullptr
}

bool PlateauMilitaire::gagneMilitairement(Joueur* joueur) const {
    if (avance >= avance_win && joueur != joueur_derriere){
        // std::cout<<"avance: "<<avance << "  joueur:" << (joueur != joueur_derriere) <<std::endl; //!test
        return true;
    }
    else {
        return false;
    }
}

void PlateauMilitaire::retirer_jeton_malus(JetonMalus& jeton) { 
    unsigned int compteur_teste = 0;
    for (int i = 0; i < Dim_jetons_malus; i++) {
        if (liste_jetons_malus[i] == &jeton) { 
            liste_jetons_malus[i] = nullptr; //on retire le jeton de la liste en ajoutant une jeton "neutre"
            jeton.exec_malus(); //on execute l'effet du jeton 
            compteur_teste += 1; //on incremente le compteur de jeton retiré
        }
    }
}


//destructeur de PlateauMilitaire
PlateauMilitaire::~PlateauMilitaire() {
    for (int i = 0; i < Dim_jetons_malus; i++) {
        delete liste_jetons_malus[i];
    }
    delete[] liste_jetons_malus;
}

/*-------------------------------------PlateauCarte-------------------------------------*/


//!constructeur de plateauCarte 
PlateauCartes::PlateauCartes() 
{
    // std::cout<<"ici PlateauCarte::Plateau::Carte()"<<std::endl;
    age = 0; //on commence a 0 car on effectue un addAge() au début de la partie dans le contstructeur de Plateau
    Carte** cartes_en_jeu = new Carte*[TAILLE_CARTE_EN_JEU];
    Carte** defausses = new Carte*[TAILLE_DEFAUSSES];
    Merveille** merveilles = new Merveille*[TAILLE_MERVEILLES];

    // int i = 0;
    // for (int i = 0; i < TAILLE_CARTE_EN_JEU; i++) {
    //     cartes_en_jeu[i] = nullptr;
    //     i++;
    // }
    // for(int i=0; i<TAILLE_DEFAUSSES; i++){
    //     defausses[i] = nullptr;
    // }
    // for(int i=0; i<TAILLE_MERVEILLES; i++){
    //     merveilles[i] = nullptr;
    // }
}

void PlateauCartes::addAge(){
    age++;
    std::cout << "Passage à l'âge suivant : Age "<<age <<std::endl;
    initPlateauCarte();
}

void PlateauCartes::ajouterCarte(Carte* carte){
    for (int i = 0; i < TAILLE_CARTE_EN_JEU; i++){
        if (cartes_en_jeu[i] == nullptr){
            cartes_en_jeu[i] = carte;
            break;
        }
    }
}

bool PlateauCartes::estEnJeu(Carte* carte) const{
    for (int i = 0; i < TAILLE_CARTE_EN_JEU; i++){
        if (cartes_en_jeu[i] == carte){
            return true;
        }
    }
    return false;
}

bool PlateauCartes::estAccessible(Carte* carte) const{
    if (this->estEnJeu(carte)){ //si la carte est en jeu
        return carte->est_accessible();
    }
    return false;
}

void PlateauCartes::rendreAccessible(Carte* carte){
    if(this->estEnJeu(carte)){
        carte->set_accessible();
    }
    else throw SetException("erreur: carte n'est pas en jeu.");
}

bool PlateauCartes::estVisible(Carte* carte) const{
    if (this->estEnJeu(carte)){ //si la carte est en jeu
        return carte->est_facevisible();
    }
    return false;
}

Carte** PlateauCartes::getCartesAccessibles() const{
    /*
    Carte** cartes_accessibles = new Carte*[TAILLE_CARTE_EN_JEU];
    for(int i =0; i< TAILLE_CARTE_EN_JEU; i++){
        if (cartes_en_jeu[i]->est_accessible()){
            cartes_accessibles[i] = cartes_en_jeu[i];
        }
    }
    return cartes_accessibles;
    */

    Carte** cartes_accessibles = new Carte*[TAILLE_CARTE_EN_JEU];
    size_t j = 0;
    for(int i =0; i< TAILLE_CARTE_EN_JEU; i++){
        if (cartes_en_jeu[i]->est_accessible()){
            cartes_accessibles[j] = cartes_en_jeu[i];
            j++;
        }
    }
    for(j; j<TAILLE_CARTE_EN_JEU; j++){
        cartes_accessibles[j] = nullptr;
    }
    return cartes_accessibles;
}

unsigned int PlateauCartes::getNbCartesAccessibles() const{
    unsigned int res = 0;
    for(int i =0; i< TAILLE_CARTE_EN_JEU; i++){
        if (cartes_en_jeu[i]->est_accessible()){
            res++;
        }
    }
    return res;
}

Carte** PlateauCartes::getCartesVisibles() const{
    /*
    Carte** cartes_visibles = new Carte*[TAILLE_CARTE_EN_JEU];
    for(int i =0; i< TAILLE_CARTE_EN_JEU; i++){
        if (cartes_en_jeu[i]->est_facevisible()){
            cartes_visibles[i] = cartes_en_jeu[i];
        }
    }
    return cartes_visibles;
    */
    Carte** cartes_visibles = new Carte*[TAILLE_CARTE_EN_JEU];
    size_t j = 0;
    for(int i =0; i< TAILLE_CARTE_EN_JEU; i++){
        if (cartes_en_jeu[i]->est_facevisible()){
            cartes_visibles[j] = cartes_en_jeu[i];
            j++;
        }
    }
    for(j; j<TAILLE_CARTE_EN_JEU; j++){
        cartes_visibles[j] = nullptr;
    }
    return cartes_visibles;
}

void PlateauCartes::update_accessibilite(){ //! fonction OK
    std::cout << "PlateauCartes::update_accessibilite : age :"<< age << std::endl; //! test
    std::vector<std::vector<unsigned int>> liste_adjacence;
    if (age == 1){
        liste_adjacence = {{2, 3}, {3, 4}, {5, 6}, {6, 7}, {7, 8}, {9, 10}, {10,11}, {11, 12}, {12, 13}, {14, 15}, {15, 16}, {16, 17}, {17, 18}, {18, 19}};
    }
    else if (age == 2){
        // std::cout << "PlateauCartes::update_accessibilite age 2" << std::endl; //! test
        liste_adjacence = {{6}, {6,7}, {7, 8}, {8, 9}, {9, 10}, {10}, {11}, {11, 12}, {12, 13},{13, 14}, {14},{15}, {15, 16}, {16, 17}, {17}, {18}, {18, 19}, {19}};
    }
    else if (age == 3){

        liste_adjacence = {{2, 3}, {3, 4}, {5, 6}, {6, 7}, {7, 8}, {9}, {9}, {10}, {10}, {11, 12}, {13, 14}, {15}, {15, 16}, {16, 17}, {17}, {18}, {18, 19}, {19}};
    }

    for(unsigned int i = 0; i < liste_adjacence.size(); i++){
        unsigned int compteur = 0;
        for(unsigned int j = 0; j < liste_adjacence[i].size(); j++){

            if (cartes_en_jeu[liste_adjacence[i][j]] == nullptr){ 
                compteur += 1;
            
            }
            if (cartes_en_jeu[i] != nullptr && compteur == liste_adjacence[i].size()){
                rendreAccessible(cartes_en_jeu[i]); 
                // std::cout << "element "<< i << " rendu accessible" << std::endl;
            }
        }
    }

}

void PlateauCartes::prendreCarte(Carte* carte){ //! fonction OK
    // std::cout << "PlateauCartes::prendreCarte" << std::endl; /!test
    for (int i = 0; i < TAILLE_CARTE_EN_JEU; i++){
        if (cartes_en_jeu[i] == carte && cartes_en_jeu[i] != nullptr){
            // if (age == 2) std::cout << "PlateauCartes::prendreCarte : carte prise n°"<< i << std::endl; /!test
            cartes_en_jeu[i] = nullptr;
            // if (age == 2) std::cout << "PlateauCartes::prendreCarte : carte prise n°"<< i << " supprimée" << std::endl; /!test
        }
    }
    update_accessibilite();
}

void PlateauCartes::defausserCarte(Carte* carte){
    defausses[taille_defausse] = carte;
    taille_defausse++;
    if (taille_defausse >= TAILLE_CARTE_EN_JEU){throw "Dans PlateauCartes::defausserCarte, la taille de la defausse est superieur à la taille max";}
}

void PlateauCartes::prendreMerveille(Merveille* merveille){
    for (int i = 0; i < TAILLE_MERVEILLES; i++){
        if (merveilles[i] == merveille){
            merveilles[i] = nullptr;
            break;
        }
    }
}

unsigned int PlateauCartes::getNbMerveilles() const{
    unsigned int compteur = 0;
    for(int i = 0; i < TAILLE_MERVEILLES; i++){
        if (merveilles[i] != nullptr){
            compteur++;
        }
    }
    return compteur;
}



bool PlateauCartes::estVide() const{
    for (int i = 0; i < TAILLE_CARTE_EN_JEU; i++){
        if (cartes_en_jeu[i] != nullptr){
            return false;
        }
    }
    return true;
}


void PlateauCartes::initPlateauCarte(){
    // std::cout << "ici debut initPlateauCarte" <<std::endl; //! test
    if (age == 1){
        // std::cout<< "initialisation d'age 1!"<< std::endl; //! test
        //initialisation des cartes en jeu pour l'age 1
        Merveille* LISTE_MERVEILLES[NB_MERVEILLES_TOT] = {
            //!LISTE DE TOUTE LES MERVEILLES
            new Merveille({RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::detruire_carte_grise, Capacite::none, Capacite::none}, 
                3, 1, false, "LeCircusMaximus", 1, 0, {RessourcePrimaire::pierre, RessourcePrimaire::pierre, RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::verre, RessourceSecondaire::none, RessourceSecondaire::none} ),

            new Merveille({RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::none, Capacite::none, Capacite::none}, 
                3, 2, false, "LeColosse", 1, 0, {RessourcePrimaire::brique, RessourcePrimaire::brique, RessourcePrimaire::brique, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::verre, RessourceSecondaire::none, RessourceSecondaire::none} ),

            new Merveille({RessourcePrimaire::bois, RessourcePrimaire::pierre, 
                RessourcePrimaire::brique}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::none, Capacite::none, Capacite::none}, 
                4, 0, true, "LeGrandPhare", 1, 0, {RessourcePrimaire::pierre, RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::parchemin, RessourceSecondaire::parchemin, RessourceSecondaire::none} ),

            new Merveille({RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::gagner_monnaie_6, 
                Capacite::rejouer, Capacite::none}, 3, 0, false, "LesJardinsSuspendus", 1, 0, {RessourcePrimaire::bois, 
                RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::parchemin, RessourceSecondaire::none} ),

            new Merveille({RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::choisir_jeton_science, 
                Capacite::none, Capacite::none}, 4, 0, false, "LaGrandeBibliotheque", 1, 0, {RessourcePrimaire::bois, 
                RessourcePrimaire::bois, RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::parchemin, RessourceSecondaire::none} ),

            new Merveille({RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::jouer_carte_defausse, 
                Capacite::none, Capacite::none}, 2, 0, false, "LeMausolee", 1, 0, {RessourcePrimaire::brique, 
                RessourcePrimaire::brique, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::verre, RessourceSecondaire::parchemin} ),

            new Merveille({RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::verre}, {Capacite::rejouer, 
                Capacite::none, Capacite::none}, 2, 0, true, "LePiree", 1, 0, {RessourcePrimaire::bois, 
                RessourcePrimaire::bois, RessourcePrimaire::pierre, RessourcePrimaire::brique, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} ),

            new Merveille({RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::none, 
                Capacite::none, Capacite::none}, 9, 0, false, "LesPyramides", 1, 0, {RessourcePrimaire::pierre, 
                RessourcePrimaire::pierre, RessourcePrimaire::pierre, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::none, RessourceSecondaire::none} ),

            new Merveille({RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::rejouer, 
                Capacite::none, Capacite::none}, 6, 0, false, "LeSphynx", 1, 0, {RessourcePrimaire::brique, 
                RessourcePrimaire::pierre, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::verre, RessourceSecondaire::none} ),
            new Merveille({RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::detruire_carte_marron, 
                Capacite::none, Capacite::none}, 3, 1, false, "LaStatueDeZeus", 1, 0, {RessourcePrimaire::brique, 
                RessourcePrimaire::bois, RessourcePrimaire::pierre, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::parchemin, RessourceSecondaire::none} ),

            new Merveille({RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::gagner_monnaie_12, 
                Capacite::rejouer, Capacite::none}, 0, 0, false, "LeTempleDArtemis", 1, 0, {RessourcePrimaire::pierre, 
                RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::verre, RessourceSecondaire::none} ),

            new Merveille({RessourcePrimaire::pierre, RessourcePrimaire::pierre, 
                RessourcePrimaire::brique}, {RessourceSecondaire::parchemin, RessourceSecondaire::none}, {Capacite::gagner_monnaie_3, 
                Capacite::rejouer, Capacite::perdre_monnaie_3}, 3, 0, false, "LaViaAppia",1, 0, {RessourcePrimaire::brique, 
                RessourcePrimaire::brique, RessourcePrimaire::pierre, RessourcePrimaire::pierre, RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::none, RessourceSecondaire::none} )
        };

        initMerveilleRandom(NB_MERVEILLES_JEU,NB_MERVEILLES_TOT, LISTE_MERVEILLES);

        Carte* LISTE_CARTE_AGE_1[NB_CARTE_AGE_1_TOT] = {
            //! LISTE DE TOUTES LES CARTES DE L'AGE 1

            new CarteRessourcePrimaire("Chantier", 1, 0, {RessourcePrimaire::bois, 
                RessourcePrimaire::none, RessourcePrimaire::none},{RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}),
            
            new CarteRessourcePrimaire("Exploitation", 1, 1, {RessourcePrimaire::bois, 
                RessourcePrimaire::none, RessourcePrimaire::none},{RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none}),

            new CarteRessourcePrimaire("BassinArgileux", 1, 0, {RessourcePrimaire::brique, 
                RessourcePrimaire::none, RessourcePrimaire::none},{RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none}),
            
            new CarteRessourcePrimaire("Cavite", 1, 1, {RessourcePrimaire::brique, 
                RessourcePrimaire::none, RessourcePrimaire::none},{RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none}),

            new CarteRessourcePrimaire("Gisement", 1, 0, {RessourcePrimaire::pierre, 
                RessourcePrimaire::none, RessourcePrimaire::none},{RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} ),
            
            new CarteRessourcePrimaire("Mine", 1, 1, {RessourcePrimaire::pierre, 
                RessourcePrimaire::none, RessourcePrimaire::none},{RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} ),

            new CarteRessourceSecondaire("Verrerie", 1, 1, RessourceSecondaire::verre,
                {RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none}),

            new CarteRessourceSecondaire("Presse", 1, 1, RessourceSecondaire::parchemin,
                {RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} ),
            

            new CarteCommerce({RessourcePrimaire::pierre, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none}, Capacite::none, 
                SymboleChainage::none, SymboleChainage::none, false, true, 0, "DepotDePierre", 1, 3, {RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} ),

            new CarteCommerce({RessourcePrimaire::brique, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none}, Capacite::none,
                SymboleChainage::none, SymboleChainage::none, false, true, 0, "DepotDArgile", 1, 3, {RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} ),

            new CarteCommerce({RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none}, Capacite::none,
                SymboleChainage::none, SymboleChainage::none, false, true, 0, "DepotDeBois", 1, 3, {RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} ),

            new CarteCommerce({RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none}, Capacite::gagner_monnaie_4, SymboleChainage::none, 
                SymboleChainage::jarre, false, false, 0, "Taverne", 1, 0, {RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} ),
            
            new CartePrestige("Theatre", 1, 0, {RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::masque, 3),

            new CartePrestige("Autel", 1, 0, {RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::lune, 3),

            new CartePrestige("Bains", 1, 0, {RessourcePrimaire::pierre, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::goute, 3),

            new CarteMilitaire("TourDeGarde", 1, 0, {RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, 
                RessourceSecondaire::none, RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::none, 1),

            new CarteMilitaire("Ecuries", 1, 0, {RessourcePrimaire::bois, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, 
                RessourceSecondaire::none, RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::fer_a_cheval, 1),

            new CarteMilitaire("Caserne", 1, 0, {RessourcePrimaire::brique, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, 
                RessourceSecondaire::none, RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::epee, 1),

            new CarteMilitaire("Palissade", 1, 2, {RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, 
                RessourceSecondaire::none, RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::tour, 1),

            
            new CarteScience("Atelier", 1, 0, {RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::parchemin, 
                RessourceSecondaire::none, RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::none, SymboleScience::fil_a_plomb, 1),

            new CarteScience("Apothicaire", 1, 0, {RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, 
                RessourceSecondaire::none, RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::none, SymboleScience::roue, 1),

            new CarteScience("Scriptorium", 1, 2, {RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, 
                RessourceSecondaire::none, RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::livre, SymboleScience::plume, 0),

            new CarteScience("Officine", 1, 2, {RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, 
                RessourceSecondaire::none, RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::engrenage, SymboleScience::pilon, 0)
        };


        //*ajout des cartes dans le plateau
        initCarteRandom(NB_CARTES_AGE_1_JEU,NB_CARTE_AGE_1_TOT, LISTE_CARTE_AGE_1);

        //*initialisation des positions des cartes et de leur visibilité et de leur accessibilité et de leur position
        unsigned int i_counter = 0;
        for(int j = 0; j < 5; j++){ //rangé 0 à 4
            for(int _ =0; _ <j+2; _++){
                if (j%2 ==0){cartes_en_jeu[i_counter]->set_face_visible();}//carte visible pour toutes les lignes paires
                if (j==4){cartes_en_jeu[i_counter]->set_accessible();}//carte accessible pour la dernière ligne
                cartes_en_jeu[i_counter]->set_position(i_counter);
                i_counter++;
            }
        }
        // std::cout<< "age 1 initialisé correctement" << std::endl; //! test
        
        //* Remarque, on a deja suprimé les cartes non utilisées dans la fonction initCarteRandom
        // delete[] LISTE_MERVEILLES;
        // delete[] LISTE_CARTE_AGE_1;
        //! on delet les element du tableau mais pas les tableau car il ne sont pas alloué dynamiquement 
    }
    else if (age == 2){
        // std::cout<< "initialisation d'age 2!"<< std::endl; //! test
        //initialisation des cartes en jeu pour l'age 2
        Carte* LISTE_CARTE_AGE_2[NB_CARTE_AGE_2_TOT] = {
            //! LISTE DE TOUTES LES CARTES DE L'AGE 2

            new CarteRessourcePrimaire("Scierie", 2, 2, {RessourcePrimaire::bois, 
                RessourcePrimaire::bois, RessourcePrimaire::none}, {RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, 
                RessourceSecondaire::none, RessourceSecondaire::none} ),

            new CarteRessourcePrimaire("Briqueterie", 2, 2, {RessourcePrimaire::brique, 
                RessourcePrimaire::brique, RessourcePrimaire::none},{RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, 
                RessourceSecondaire::none, RessourceSecondaire::none} ),

            new CarteRessourcePrimaire("Carriere", 2, 2, {RessourcePrimaire::pierre, 
                RessourcePrimaire::pierre, RessourcePrimaire::none},{RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none,
                RessourceSecondaire::none, RessourceSecondaire::none} ),

            new CarteRessourceSecondaire("Soufflerie", 2, 0, RessourceSecondaire::verre,
                {RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} ),

            new CarteRessourceSecondaire("Sechoir", 2, 0, RessourceSecondaire::parchemin,
                {RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} ),

            
            new CartePrestige("Tribunal", 2, 0, {RessourcePrimaire::bois, RessourcePrimaire::bois, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::none, RessourceSecondaire::none}, 
                SymboleChainage::none, SymboleChainage::none, 5),

            new CartePrestige("Statue", 2, 0, {RessourcePrimaire::brique, RessourcePrimaire::brique, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none}, 
                SymboleChainage::masque, SymboleChainage::pilier, 4),

            new CartePrestige("Temple", 2, 0, {RessourcePrimaire::bois, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::none, RessourceSecondaire::none}, 
                SymboleChainage::lune, SymboleChainage::soleil, 4),

            new CartePrestige("Aqueduc", 2, 0, {RessourcePrimaire::pierre, RessourcePrimaire::pierre, 
                RessourcePrimaire::pierre, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none}, 
                SymboleChainage::goute, SymboleChainage::none, 5),

            new CartePrestige("Rostres", 2, 0, {RessourcePrimaire::pierre, RessourcePrimaire::bois, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none}, 
                SymboleChainage::none, SymboleChainage::temple, 4),

            new CarteMilitaire("Muraille", 2, 0, {RessourcePrimaire::pierre, RessourcePrimaire::pierre, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none}, 
                SymboleChainage::none, SymboleChainage::none, 2),

            new CarteMilitaire("Haras", 2, 0, {RessourcePrimaire::brique, RessourcePrimaire::bois, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none}, 
                SymboleChainage::fer_a_cheval, SymboleChainage::none, 1),

            new CarteMilitaire("Baraquements", 2, 3, {RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none}, 
                SymboleChainage::epee, SymboleChainage::none, 1),

            new CarteMilitaire("ChampDeTir", 2, 0, {RessourcePrimaire::pierre, RessourcePrimaire::bois, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::none, RessourceSecondaire::none}, 
                SymboleChainage::none, SymboleChainage::cible, 2),

            new CarteMilitaire("PlaceDArmes", 2, 0, {RessourcePrimaire::brique, RessourcePrimaire::brique, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::none, RessourceSecondaire::none}, 
                SymboleChainage::none, SymboleChainage::casque, 2),

            new CarteScience("Bibliotheque", 2, 0, {RessourcePrimaire::pierre, RessourcePrimaire::bois, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::none, RessourceSecondaire::none}, 
                SymboleChainage::livre, SymboleChainage::none, SymboleScience::plume, 2),

            new CarteScience("Dispensaire", 2, 0, {RessourcePrimaire::brique, RessourcePrimaire::brique, 
                RessourcePrimaire::pierre, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none}, 
                SymboleChainage::engrenage, SymboleChainage::none, SymboleScience::pilon, 2),

            new CarteScience("Ecole", 2, 0, {RessourcePrimaire::bois, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::parchemin, RessourceSecondaire::none},
                SymboleChainage::none, SymboleChainage::lyre, SymboleScience::roue, 1),

            new CarteScience("Laboratoire", 2, 0, {RessourcePrimaire::bois, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::verre, RessourceSecondaire::none}, 
                SymboleChainage::none,SymboleChainage::lampe, SymboleScience::fil_a_plomb, 1),

            new CarteCommerce({RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::verre, RessourceSecondaire::parchemin}, Capacite::none,
                SymboleChainage::none, SymboleChainage::none, true, false, 0, "Forum", 2, 3, {RessourcePrimaire::brique, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} ),

            new CarteCommerce({RessourcePrimaire::bois, RessourcePrimaire::brique, RessourcePrimaire::pierre}, 
                {RessourceSecondaire::none, RessourceSecondaire::none}, Capacite::none, 
                SymboleChainage::none, SymboleChainage::none, true, false, 0, "Caravanserail", 2, 2, {RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::verre, RessourceSecondaire::parchemin, RessourceSecondaire::none} ),

            new CarteCommerce({RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::verre, RessourceSecondaire::parchemin}, Capacite::none,  SymboleChainage::none, SymboleChainage::none, false, true, 
                0, "Douanes", 2, 4, {RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} ),

            new CarteCommerce({RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none}, Capacite::gagner_monnaie_6,  
                SymboleChainage::none, SymboleChainage::toneau, false, false, 0, "Brasserie", 2, 0, {RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} )
        };

        //* Ajout des cartes dans le plateau
        initCarteRandom(NB_CARTES_AGE_2_JEU,NB_CARTE_AGE_2_TOT, LISTE_CARTE_AGE_2);

        //*initialisation des positions des cartes et de leur visibilité et de leur accessibilité et de leur position

        unsigned int i_counter = 0;
        for(int j = 0; j < 5; j++){ //rangé 0 à 4
            for(int _ =0; _ <j+2; _++){
                if (j%2 ==0){cartes_en_jeu[i_counter]->set_face_visible();}//carte visible pour toutes les lignes paires
                // if (j==0){cartes_en_jeu[i_counter]->set_accessible();}//carte accessible pour la dernière ligne
                cartes_en_jeu[i_counter]->set_position(NB_CARTES_AGE_2_JEU-1-i_counter);
                i_counter++;
            }
        }
        cartes_en_jeu[19]->set_accessible(); //carte accessible pour la dernière ligne
        cartes_en_jeu[18]->set_accessible(); //carte accessible pour la dernière ligne
        //supression de la liste de cartes
        //* Remarque, on a deja suprimé les cartes non utilisées dans la fonction initCarteRandom
        // delete[] LISTE_CARTE_AGE_2;
        // std::cout<< "initialisation d'age 2 réussi!"<< std::endl; //! test
    }
    else if (age == 3){
        // std::cout<< "initialisation d'age 3!"<< std::endl; //! test
        //initialisation des cartes en jeu pour l'age 3
        Carte* LISTE_CARTE_AGE_3[NB_CARTE_AGE_3_TOT] = {
            //! LISTE DES CARTES DE L'AGE 3

            new CarteCommerce({RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none}, Capacite::gagner_monnaie_carte_grise, SymboleChainage::none, 
                SymboleChainage::none, false, false, 3, "ChambreDeCommerce", 3, 0, {RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::parchemin, RessourceSecondaire::none} ),

            new CarteCommerce({RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none}, Capacite::gagner_monnaie_carte_marron, SymboleChainage::none,
                SymboleChainage::none, false, false, 3, "Port", 3, 0, {RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::parchemin, RessourceSecondaire::none} ),

            new  CarteCommerce({RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none}, Capacite::gagner_monnaie_carte_rouge, SymboleChainage::none, 
                SymboleChainage::none, false, false, 3, "Armurerie", 3, 0, {RessourcePrimaire::pierre, RessourcePrimaire::pierre, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::none, RessourceSecondaire::none} ),

            new CarteCommerce({RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none}, Capacite::gagner_monnaie_carte_jaune, SymboleChainage::jarre, 
                SymboleChainage::none, false, false, 3, "Phare", 3, 0, {RessourcePrimaire::brique, RessourcePrimaire::brique, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::none, RessourceSecondaire::none} ),

            new CarteCommerce({RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none}, Capacite::gagner_monnaie_2_par_merveille, SymboleChainage::toneau, SymboleChainage::none, 
                false, false, 3, "Arene", 3, 0, {RessourcePrimaire::brique, RessourcePrimaire::pierre, RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none}, 
                {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} ),

            new CartePrestige("Palace", 3, 0, {RessourcePrimaire::brique, RessourcePrimaire::pierre, 
                RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::verre, RessourceSecondaire::none} , 
                SymboleChainage::none, SymboleChainage::none, 7),

            new CartePrestige("HotelDeVille", 3, 0, {RessourcePrimaire::pierre, RessourcePrimaire::pierre, 
                RessourcePrimaire::pierre, RessourcePrimaire::bois, RessourcePrimaire::bois}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} , 
                SymboleChainage::none, SymboleChainage::none, 7),

            new CartePrestige("Obelisque", 3, 0, {RessourcePrimaire::pierre, RessourcePrimaire::pierre, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::none, RessourceSecondaire::none} , 
                SymboleChainage::none, SymboleChainage::none, 5),

            new CartePrestige("Jardins", 3, 0, {RessourcePrimaire::brique, RessourcePrimaire::brique, 
                RessourcePrimaire::bois, RessourcePrimaire::bois, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} , 
                SymboleChainage::pilier, SymboleChainage::none, 6),

            new CartePrestige("Pantheon", 3, 0, {RessourcePrimaire::brique, RessourcePrimaire::bois, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::parchemin, RessourceSecondaire::none} , 
                SymboleChainage::soleil, SymboleChainage::none, 6),

            new CartePrestige("Senat", 3, 0, {RessourcePrimaire::brique, RessourcePrimaire::brique, 
                RessourcePrimaire::pierre, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::none, RessourceSecondaire::none} , 
                SymboleChainage::temple, SymboleChainage::none, 5),

            new CarteMilitaire("Arsenal", 3, 0, {RessourcePrimaire::brique, RessourcePrimaire::brique, 
                RessourcePrimaire::brique, RessourcePrimaire::bois, RessourcePrimaire::bois}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} , 
                SymboleChainage::none, SymboleChainage::none, 3),

            new CarteMilitaire("Pretoire", 3, 8, {RessourcePrimaire::none, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} , 
                SymboleChainage::none, SymboleChainage::none, 3),

            new CarteMilitaire("Fortifications", 3, 0, {RessourcePrimaire::pierre, RessourcePrimaire::pierre, 
                RessourcePrimaire::brique, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::none, RessourceSecondaire::none} , 
                SymboleChainage::tour, SymboleChainage::none, 2),

            new CarteMilitaire("AtelierDeSiege", 3, 0, {RessourcePrimaire::bois, RessourcePrimaire::bois, 
                RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::none, RessourceSecondaire::none} , 
                SymboleChainage::cible, SymboleChainage::none, 2),

            new CarteMilitaire("Cirque", 3, 0, {RessourcePrimaire::brique, RessourcePrimaire::brique, 
                RessourcePrimaire::pierre, RessourcePrimaire::pierre, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none} , 
                SymboleChainage::casque, SymboleChainage::none, 2),

            new CarteScience("Academie", 3, 0, {RessourcePrimaire::pierre, RessourcePrimaire::bois, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::verre, RessourceSecondaire::none} , 
                SymboleChainage::none, SymboleChainage::none, SymboleScience::balance, 3),

            new CarteScience("Etude", 3, 0, {RessourcePrimaire::bois, RessourcePrimaire::bois, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::parchemin, RessourceSecondaire::none} , 
                SymboleChainage::none, SymboleChainage::none, SymboleScience::balance, 3),

            new CarteScience("Universite", 3, 0, {RessourcePrimaire::brique, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::parchemin, RessourceSecondaire::none} , 
                SymboleChainage::lyre, SymboleChainage::none, SymboleScience::globe_terrestre, 2),

            new CarteScience("Observatoire", 3, 0, {RessourcePrimaire::pierre, RessourcePrimaire::none, 
                RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::parchemin, RessourceSecondaire::none} , 
                SymboleChainage::lampe, SymboleChainage::none, SymboleScience::globe_terrestre, 2)

        };

        Carte* LISTE_CARTE_GUILDE[NB_CARTE_GUILDE_TOT] = {
            //!LISTE DES CARTES GUILDE

            new CarteGuilde("GuildeDesCommercants", 3, 0, {RessourcePrimaire::brique, 
                RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::parchemin, RessourceSecondaire::none},
                EffetGuilde::guilde_commercants),

            new CarteGuilde("GuildeDesArmateurs", 3, 0, {RessourcePrimaire::brique, 
                RessourcePrimaire::pierre, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::parchemin, RessourceSecondaire::none},
                EffetGuilde::guilde_armateurs),

            new CarteGuilde("GuildeDesBatisseurs", 3, 0, {RessourcePrimaire::pierre, 
                RessourcePrimaire::pierre, RessourcePrimaire::brique, RessourcePrimaire::bois, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::none, RessourceSecondaire::none},
                EffetGuilde::guilde_batisseurs),

            new CarteGuilde("GuildeDesMagistrats", 3, 0, {RessourcePrimaire::bois, 
                RessourcePrimaire::bois, RessourcePrimaire::brique, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::none, RessourceSecondaire::none},
                EffetGuilde::guilde_magistrats),

            new CarteGuilde("GuildeDesScientifiques", 3, 0, {RessourcePrimaire::brique, 
                RessourcePrimaire::brique, RessourcePrimaire::bois, RessourcePrimaire::bois, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none},
                EffetGuilde::guilde_scientifiques),

            new CarteGuilde("GuildeDesUsuriers", 3, 0, {RessourcePrimaire::pierre, 
                RessourcePrimaire::pierre, RessourcePrimaire::bois, RessourcePrimaire::bois, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none, RessourceSecondaire::none},
                EffetGuilde::guilde_usuriers),

            new CarteGuilde("GuildeDesTacticiens", 3, 0, {RessourcePrimaire::pierre, 
                RessourcePrimaire::pierre, RessourcePrimaire::brique, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::none, RessourceSecondaire::none},
                EffetGuilde::guilde_tacticiens)
        };
        //ETAPE 1 : initialisation des cartes en jeu pour l'age 3, avec NB_CARTE_GUILDE_JEU en plus,
        initCarteRandom(NB_CARTES_AGE_3_JEU+NB_CARTE_GUILDE_JEU,NB_CARTE_AGE_3_TOT, LISTE_CARTE_AGE_3); 
        //ETAPE 2 : on remplit les première case du tableau avec le nombre de carte guilde necessaire
        //on reecrit donc par dessus les cartes age 3, mais pas grave parcequ'on en à tiré exactement NB_CARTE_GUILDE_JEU en plus
        for (int i = 0; i < NB_CARTE_GUILDE_JEU; i++){
            delete cartes_en_jeu[i]; //on supprime les cartes age 3 qui vont etre reecrite
            cartes_en_jeu[i] = nullptr; //on remplace apr des nullptr
        
        }
        initCarteRandom(NB_CARTE_GUILDE_JEU,NB_CARTE_GUILDE_TOT, LISTE_CARTE_GUILDE);
        //ETAPE 3 : on shuffle pour eviter que les cartes guilde soient toujours au debut
        std::random_device rd; 
        std::mt19937 gen(rd());
        std::shuffle(cartes_en_jeu, cartes_en_jeu + NB_CARTE_AGE_3_TOT, gen); 
    

        int i_counter = 0;
        for(int j = 0; j < 3; j++){ //rangé 0 à 4
            for(int _ =0; _ <j+2; _++){
                if (j%2 ==0){cartes_en_jeu[i_counter]->set_face_visible();}//carte visible pour toutes les lignes paires
                i_counter++;
            }
        }
        cartes_en_jeu[9] -> set_position(9); //les deux cartes centrales dans le schemat de l'age 3
        cartes_en_jeu[10] -> set_position(10);
        i_counter =0;
        for(int j = 0; j < 3; j++){ //rangé 0 à 4
            for(int _ =0; _ <j+2; _++){
                if (j%2 ==0){cartes_en_jeu[20-1-i_counter]->set_face_visible();}//carte visible pour toutes les lignes paires
                if (j==0){cartes_en_jeu[20-1-i_counter]->set_accessible();}//carte accessible pour la dernière ligne
                i_counter++;
            }
        }


        // delete[] LISTE_CARTE_AGE_3;
        // std::cout<< "initialisation d'age 3 réussi!"<< std::endl; //! test
    }
    else {throw ("Erreur dans init_carte_en_jeu : age invalide");}
    // std::cout << "Fin de initPlateauCarte" <<std::endl;

}

void PlateauCartes::initCarteRandom(unsigned int nombre_carte,unsigned int taille_tableau, Carte** tableau_cartes){
    // std::cout<<"ici initCarteRandom : debut de la fonction"<<std::endl; //!teste
    if (nombre_carte > TAILLE_CARTE_EN_JEU){throw ("Erreur dans tirerCarteRandom : nombre de carte invalide");}

    std::random_device rd; //sead aléatoire pour mélanger les listes de cartes
    std::mt19937 gen(rd());
    std::shuffle(tableau_cartes, tableau_cartes + nombre_carte, gen); //mélange d'une liste de cartes 
    // std::cout<<"ici initCarteRandom : fin du shuffle"<<std::endl; //!teste
    for (int i = 0; i < nombre_carte; i++){
        cartes_en_jeu[i] = tableau_cartes[i]; //ajout des nombre_carte premières cartes de la liste mélangée
    }
    // std::cout<<"ici initCarteRandom : fin de l'ajout des cartes"<<std::endl; //!teste
    for (int i = nombre_carte; i < taille_tableau ; i++){
        delete tableau_cartes[i]; //on delete les cartes non utilisées
    }
    // std::cout<<"ici initCarteRandom : fin de la suppression des cartes non utilisées"<<std::endl; //!teste
    // delete[] tableau_cartes; 
    //! ne pas delete les tableaux non aloué dynamiquement 
}

void PlateauCartes::initMerveilleRandom(unsigned int nombre_merveille, unsigned int taille_tableau, Merveille** tableau_merveilles){
    if (nombre_merveille > TAILLE_MERVEILLES){throw ("Erreur dans tirerMerveilleRandom : nombre de merveille invalide");}
    std::random_device rd; //sead aléatoire pour mélanger les listes de cartes
    std::mt19937 gen(rd());
    // std::cout << "AVANT SHUFFLE" << std::endl; //!test
    std::shuffle(tableau_merveilles, tableau_merveilles + nombre_merveille +4, gen); //mélange d'une liste de cartes
    for (int i = 0; i < nombre_merveille; i++){
        merveilles[i] = tableau_merveilles[i]; //ajout des TAILLE_MERVEILLES premières merveilles de la liste mélangée
    }
    if (nombre_merveille < TAILLE_MERVEILLES){
        for (int i = nombre_merveille; i < TAILLE_MERVEILLES; i++){
            merveilles[i] = nullptr; //on met les merveilles restantes à nullptr
        }
    }
    for (int i = nombre_merveille; i < taille_tableau ; i++){
        delete tableau_merveilles[i];
    }
}



PlateauCartes::~PlateauCartes(){
    for (int i = 0; i < TAILLE_CARTE_EN_JEU; i++){
        delete cartes_en_jeu[i];
    }
    for (int i = 0; i < TAILLE_DEFAUSSES; i++){
        delete defausses[i];
    }
    for (int i = 0; i < TAILLE_MERVEILLES; i++){
        delete merveilles[i];
    }
    // delete[] cartes_en_jeu;
    // delete[] defausses; 
    // delete[] merveilles;
    //! voir ligne 704 pour les explications 
}




std::ostream& operator<<(std::ostream& os, CapaciteScience capacite_science) {
    switch (capacite_science) {
        case CapaciteScience::none:
            os << "none";
            break;
        case CapaciteScience::agriculture:
            os << "agriculture";
            break;
        case CapaciteScience::architecture:
            os << "architecture";
            break;
        case CapaciteScience::economie:
            os << "economie";
            break;
        case CapaciteScience::loi:
            os << "loi";
            break;
        case CapaciteScience::maconnerie:
            os << "maconnerie";
            break;
        case CapaciteScience::urbanisme:
            os << "urbanisme";
            break;
        case CapaciteScience::theologie:
            os << "theologie";
            break;
        case CapaciteScience::strategie:
            os << "strategie";
            break;
        case CapaciteScience::philosophie:
            os << "philosophie";
            break;
        case CapaciteScience::mathematique:
            os << "mathematique";
            break;
        default:
            os << "capacite_merveille non reconnue!";
            throw SetException("capacite_merveille non reconnue!");
            break;
    }
    return os;
}
