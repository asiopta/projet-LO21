#include "Plateau.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <unordered_set>

const unsigned int NB_MERVEILLES_JEU = 8;
const unsigned int NB_MERVEILLES_TOT = 10;
const unsigned int NB_CARTES_AGE_1_JEU = 21;
const unsigned int NB_CARTES_AGE_2_JEU = 21;
const unsigned int NB_CARTES_AGE_3_JEU = 20;
const unsigned int NB_CARTE_AGE_1_TOT = 31;
const unsigned int NB_CARTE_AGE_2_TOT = 31;
const unsigned int NB_CARTE_AGE_3_TOT = 31;

/*-------------------------------------JetonScience-------------------------------------*/

JetonScience::JetonScience() : capacite(CapaciteScience::none) {} //si vous n'arrivez pas à lire le none, verifier qu'il y est bien dans le enum de CapaciteScience
JetonScience::JetonScience(CapaciteScience capacite) : capacite(capacite) {} //rafrechir la memoire si vous ne voyez pas le enum CapaciteScience

CapaciteScience JetonScience::get_capacite() const{return capacite;}

//fonction d'execution de la capacite du jeton science
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
    joueur->addSymboleScience(SymboleScience::balance); //addSymboleScience est une méthode de la classe Joueur qui ajoute un symbole science balance
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
    jeton_in_game = new JetonScience*[Dim_jetons_in_game];
    liste_position = new unsigned int[Dim_liste_position];
    jeton_out_game = new JetonScience*[Dim_jetons_out_game];

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


    for (int i = 0; i < Dim_jetons_in_game; i++) {
        jeton_in_game[i] = new JetonScience(capacites[i]);
    }
    for (int i = Dim_jetons_in_game; i < Dim_jetons_out_game; i++) {
        jeton_out_game[i] = new JetonScience(capacites[i]);
    }
    for (int i = 0; i < Dim_liste_position; i++) {
        liste_position[i] = i+1;
    }
}


//ajoute un jeton science dans le tableau jeton_in_game
void PlateauScience::ajouter_jeton_in_game(JetonScience& jeton) {
    for (int i = 0; i < Dim_jetons_in_game; i++) {
        if (jeton_in_game[i]->get_capacite() == CapaciteScience::none) { ////la capacité de JetonScience est inacessible directement. Comme c'est privé 
                                                                        // Erreur corrigé en rajoutant une méthode get_capacite() dans la classe JetonScience
            jeton_in_game[i] = &jeton;
            liste_position[i] = i+1;
        }
        else {throw("Erreur : pas de place pour ajouter un jeton");}
    }
}

void PlateauScience::ajouter_jeton_out_game(JetonScience& jeton) {
    for (int i = 0; i < Dim_jetons_out_game; i++) {
        if (jeton_out_game[i]->get_capacite() == CapaciteScience::none) {
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
PlateauMilitaire::PlateauMilitaire(unsigned int a, Joueur& joueur_derr, Joueur& autre_joueur)
    : avance(a), joueur_derriere(joueur_derr)
{
    liste_jetons_malus[0] = new JetonMalus(2, 3, &joueur_derr);
    liste_jetons_malus[1] = new JetonMalus(5, 6, &joueur_derr);
    liste_jetons_malus[2] = new JetonMalus(2, 3, &autre_joueur);
    liste_jetons_malus[3] = new JetonMalus(5, 6, &autre_joueur);

}

void PlateauMilitaire::update_avance(unsigned int ajout, Joueur& joueur_cible){
    //ajoute l'avancé militaire ajout en direction du joueur_cible
    if (joueur_cible == joueur_derriere) { 
        avance += ajout; //si je joueur cible est le joueur le plus derriere, on avance le pion dans sa direction et c'est tout
    }
    else {
        avance -= ajout;
        if (avance < 0) { // si le joueur cible n'est pas le joueur le plus derriere, on avance le pion en direction de l'autre joueur
            avance = -avance; //si avance < 0, on le rend positif et on change le joueur derriere
            joueur_derriere = joueur_cible;
        }
    }
}

JetonMalus* PlateauMilitaire::jeton_malus_ici() const{
    for(int i = 0; i < Dim_jetons_malus; i++){
        if (liste_jetons_malus[i] != nullptr){
            if (liste_jetons_malus[i]->get_malus() != 0 and liste_jetons_malus[i]->get_positon() == avance  and liste_jetons_malus[i]->get_joueur() == &joueur_derriere) {
                return liste_jetons_malus[i];
            }
        }
    }
}

bool PlateauMilitaire::gagneMilitairement(Joueur& joueur) const {
    if (avance >= avance_win && &joueur != &joueur_derriere){
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

PlateauCartes::PlateauCartes() 
{
    age = 0; //on commence a 0 car on effectue un addAge() au début de la partie dans le contstructeur de Plateau
    Carte** cartes_en_jeu = new Carte*[TAILLE_CARTE_EN_JEU];
    Carte** defausses = new Carte*[TAILLE_DEFAUSSES];
    Merveille** merveilles = new Merveille*[TAILLE_MERVEILLES];

    int i = 0;
    for (int i = 0; i < TAILLE_CARTE_EN_JEU; i++) {
        cartes_en_jeu[i] = nullptr;
        i++;
    }
    for(int i=0; i<TAILLE_DEFAUSSES; i++){
        defausses[i] = nullptr;
    }
    for(int i=0; i<TAILLE_MERVEILLES; i++){
        merveilles[i] = nullptr;
    }
}

void PlateauCartes::addAge(){
    age++;
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

bool PlateauCartes::estVisible(Carte* carte) const{
    if (this->estEnJeu(carte)){ //si la carte est en jeu
        return carte->est_facevisible();
    }
    return false;
}

Carte**PlateauCartes::getCartesAccessibles() const{
    Carte** cartes_accessibles = new Carte*[TAILLE_CARTE_EN_JEU];
    for(int i =0; i< TAILLE_CARTE_EN_JEU; i++){
        if (cartes_en_jeu[i]->est_accessible()){
            cartes_accessibles[i] = cartes_en_jeu[i];
        }
    }
    return cartes_accessibles;
}

Carte** PlateauCartes::getCartesVisibles() const{
    Carte** cartes_visibles = new Carte*[TAILLE_CARTE_EN_JEU];
    for(int i =0; i< TAILLE_CARTE_EN_JEU; i++){
        if (cartes_en_jeu[i]->est_facevisible()){
            cartes_visibles[i] = cartes_en_jeu[i];
        }
    }
    return cartes_visibles;
}

void PlateauCartes::prendreCarte(Carte* carte){
    for (int i = 0; i < TAILLE_CARTE_EN_JEU; i++){
        if (cartes_en_jeu[i] == carte){
            cartes_en_jeu[i] = nullptr;
        }
    }
}

void PlateauCartes::defausserCarte(Carte* carte){
    for (int i = 0; i < TAILLE_DEFAUSSES; i++){
        if (defausses[i] == nullptr){
            defausses[i] = carte;
            break;
        }
    }
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
    if (age == 1){
        //initialisation des cartes en jeu pour l'age 1
        Merveille* LISTE_MERVEILLES[NB_MERVEILLES_TOT] = {
            //! Mettre les merveilles sous la forme suivante :
            //! new Merveille( attributs )
        };
        Carte* LISTE_CARTE_AGE_1[NB_CARTE_AGE_1_TOT] = {
    
            //! Mettre les cartes sous la forme suivante :
            //! new CarteRessourcePrimaire( attributs )

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

            


/*CartePrestige(std::string n,unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, 

        };
        initCarteRandom(NB_CARTES_AGE_1_JEU,NB_CARTE_AGE_1_TOT, LISTE_CARTE_AGE_1);
        initMerveilleRandom(NB_MERVEILLES_JEU,NB_MERVEILLES_TOT, LISTE_MERVEILLES);
        delete[] LISTE_MERVEILLES;
        delete[] LISTE_CARTE_AGE_1;
    }
    else if (age == 2){
        //initialisation des cartes en jeu pour l'age 2
        Carte* LISTE_CARTE_AGE_2[NB_CARTE_AGE_2_TOT] = {
            //! Mettre les cartes sous la forme suivante :
            //! new CarteRessourcePrimaire( attributs )
        };
        initCarteRandom(NB_CARTES_AGE_2_JEU,NB_CARTE_AGE_2_TOT, LISTE_CARTE_AGE_2);
        delete[] LISTE_CARTE_AGE_2;

    }
    else if (age == 3){
        //initialisation des cartes en jeu pour l'age 3
        Carte* LISTE_CARTE_AGE_3[NB_CARTE_AGE_3_TOT] = {
            //! Mettre les cartes sous la forme suivante :
            //! new CarteRessourcePrimaire( attributs )
        };
        initCarteRandom(NB_CARTES_AGE_3_JEU,NB_CARTE_AGE_3_TOT, LISTE_CARTE_AGE_3);
        delete[] LISTE_CARTE_AGE_3;

    }
    else {throw ("Erreur dans init_carte_en_jeu : age invalide");}

}

void PlateauCartes::initCarteRandom(unsigned int nombre_carte,unsigned int taille_tableau, Carte** tableau_cartes){
    if (nombre_carte > TAILLE_CARTE_EN_JEU){throw ("Erreur dans tirerCarteRandom : nombre de carte invalide");}

    std::random_device rd; //sead aléatoire pour mélanger les listes de cartes
    std::mt19937 gen(rd());
    std::shuffle(tableau_cartes, tableau_cartes + nombre_carte, gen); //mélange d'une liste de cartes 
    for (int i = 0; i < nombre_carte; i++){
        cartes_en_jeu[i] = tableau_cartes[i]; //ajout des nombre_carte premières cartes de la liste mélangée
    }
    if (nombre_carte < TAILLE_CARTE_EN_JEU){
        for (int i = nombre_carte; i < TAILLE_CARTE_EN_JEU; i++){
            cartes_en_jeu[i] = nullptr; //on met les cartes restantes à nullptr
        }
    }
    for (int i = nombre_carte; i < taille_tableau ; i++){
        delete tableau_cartes[i];
    }
    delete[] tableau_cartes;
}

void PlateauCartes::initMerveilleRandom(unsigned int nombre_merveille, unsigned int taille_tableau, Merveille** tableau_merveilles){
    if (nombre_merveille > TAILLE_MERVEILLES){throw ("Erreur dans tirerMerveilleRandom : nombre de merveille invalide");}
    std::random_device rd; //sead aléatoire pour mélanger les listes de cartes
    std::mt19937 gen(rd());
    std::shuffle(tableau_merveilles, tableau_merveilles + nombre_merveille, gen); //mélange d'une liste de cartes
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
    delete[] cartes_en_jeu;
    delete[] defausses;
    delete[] merveilles;
}





