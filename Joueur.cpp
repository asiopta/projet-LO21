
#include "Joueur.h"
#include <string.h>
#include <string>
#include <vector>
#include <iostream>


/*--------------------classe Ressource--------------*/
void Joueur::ajouterRessource(RessourcePrimaire rp, unsigned int quant){
    switch (rp){
        case RessourcePrimaire::bois: ressources.bois+= quant; break;
        case RessourcePrimaire::pierre: ressources.pierre+= quant; break;
        case RessourcePrimaire::brique: ressources.brique+= quant; break;
        case RessourcePrimaire::none: break;
    }
}

void Joueur::ajouterRessource(RessourceSecondaire rs, unsigned int quant){
    switch (rs){
        case RessourceSecondaire::verre: ressources.verre+= quant; break;
        case RessourceSecondaire::parchemin: ressources.parchemin+= quant; break;
        case RessourceSecondaire::none: break;
    }
}

void Joueur::retirerRessource(RessourcePrimaire rp, unsigned int quant){
    switch (rp){
        case RessourcePrimaire::bois: 
            if(ressources.bois > quant){ressources.bois-= quant;} 
            else ressources.bois = 0;
            break;

        case RessourcePrimaire::pierre: 
            if(ressources.pierre > quant){ ressources.pierre-= quant;} 
            else ressources.pierre = 0;
            break;

        case RessourcePrimaire::brique: 
            if(ressources.brique > quant){ressources.brique-= quant;} 
            else ressources.brique = 0;
            break;

        case RessourcePrimaire::none: break;
    }
}

void Joueur::retirerRessource(RessourceSecondaire rs, unsigned int quant){
    switch (rs){
        case RessourceSecondaire::verre: if(ressources.verre!= 0){ressources.verre--;} break;
        case RessourceSecondaire::parchemin: if(ressources.parchemin!=0){ressources.parchemin--;} break;
        case RessourceSecondaire::none: break;
    }
}


void Joueur::setRessource(RessourcePrimaire rp, unsigned int quantite){
    if(quantite>=0){
        switch (rp){
            case RessourcePrimaire::bois: ressources.bois= quantite; break;
            case RessourcePrimaire::pierre: ressources.pierre = quantite; break;
            case RessourcePrimaire::brique: ressources.brique = quantite; break;
            case RessourcePrimaire::none: break;
        }
    }
    else{
        SetException("erreur: quantite de ressource négative");
    }
}

void Joueur::setRessource(RessourceSecondaire rs, unsigned int quantite){
        if(quantite>=0){
        switch (rs){
            case RessourceSecondaire::verre: ressources.verre = quantite; break;
            case RessourceSecondaire::parchemin: ressources.parchemin = quantite; break;
            case RessourceSecondaire::none: break;
        }
    }
    else{
        SetException("erreur: quantite de ressource négative");
    }
}

unsigned int Joueur::getQuantiteDeRessourcePrimaire(const RessourcePrimaire& symbole) const{
    switch (symbole){
        case RessourcePrimaire::bois: 
            return ressources.bois;
            break;

        case RessourcePrimaire::pierre: 
            return ressources.pierre;
            break;

        case RessourcePrimaire::brique: 
            return ressources.brique;
            break;

        default: return 0; break;
    }
}

unsigned int Joueur::getQuantiteDeRessourceSecondaire(const RessourceSecondaire& symbole) const{
    switch (symbole){
        case RessourceSecondaire::verre: return ressources.verre; break;
        case RessourceSecondaire::parchemin: return ressources.parchemin; break;
        default : return 0; break;
    }
}



/*---------classe CapaciteJetons------------------------*/
void Joueur::addCapaciteJeton(const CapaciteScience& capacite){
    switch (capacite)
    {
    case CapaciteScience::architecture: capacites.architecture = true; break;
    case CapaciteScience::economie: capacites.economie = true; break;
    case CapaciteScience::maconnerie: capacites.maconnerie = true; break;
    case CapaciteScience::mathematique: capacites.mathematiques = true; break;
    case CapaciteScience::strategie: capacites.strategie = true; break;
    case CapaciteScience::theologie: capacites.theologie = true; break;
    case CapaciteScience::urbanisme: capacites.urbanisme = true; break;
    default:break;
    }
}

void Joueur::construireJeton(JetonScience* jeton){
    if(jeton == nullptr) return;
    jeton->exec_capacite_science(this);

    //! + gerer le fait que le jeton n'est plus prenable
}

//TODO //////////////////////////////////////////////////////////////////
//!FONCTION DE CHOIX

Carte* Joueur::choisirCarte(Carte** liste_cartes, unsigned int taille_tableau){
    //prend en argument une liste de pointeurs vers des cartes accessibles, et demande au joueur d'en choisir une
    //renvoie un pointeur vers la carte choisit

    if (taille_tableau == 0) return nullptr;
    std::cout << "Ici Joueur::choisirCarte() : debut " << std::endl;
    std::cout << "Choisissez une carte parmi les suivantes: " << std::endl;
    int j = 1;
    for (int i = 0; i<taille_tableau; i++){
        if(liste_cartes[i] != nullptr){
            std::cout << j << " : " << liste_cartes[i]->getNom() << std::endl;
            j++;
        }
    }
    int choix;
    std::cin >> choix;
    while ((choix <= 0 || choix > taille_tableau) || (choix != (int)choix)){
        std::cout << "Choix invalide, veuillez choisir un nombre entre 1 et " << taille_tableau << std::endl;
        std::cin >> choix;
    }
    return liste_cartes[choix-1];
}


//!surcharge pour les merveilles
Merveille* Joueur::choisirCarte(Merveille** liste_merveilles, unsigned int taille_tableau){
    //prend en argument une liste de pointeurs vers des cartes accessibles, et demande au joueur d'en choisir une
    //renvoie un pointeur vers la carte choisit
    // std::cout << "choisirCarte: taille_tableau" << taille_tableau<<std::endl; //!test

    if (taille_tableau == 0) return nullptr;
    std::cout << "Choisissez une merveille parmi les suivantes: " << std::endl;
    for (int i = 0; i<taille_tableau; i++){
        if(liste_merveilles[i] != nullptr)
            std::cout << i+1 << " : " << liste_merveilles[i]->getNom() << std::endl;
    }
    int choix;
    std::cin>> choix;
    choix--;
    if(choix < 0 || choix > taille_tableau || liste_merveilles[choix]== nullptr || choix != (int)choix){
        std::cout << "Choix invalide, veuillez choisir un nombre entre 1 et " << taille_tableau << std::endl;
        return choisirCarte(liste_merveilles, taille_tableau);
    }
    // std::cout << "choisirCarte: OK " << std::endl;

    return liste_merveilles[choix];
}

//*FONCTION DE CHOIX pour les jetons science 
//! le choix doit se faire sur le nombre de Jetons qui restent sur le plateauScience et non pas sur 3 jetons seulement

//! à ne pas confondre avec le choix effectué qu'on construit une merveille spécéfique où on choisit parmi 3 jetons qui
//!ne sont pas dans le plateuScience

//généralement taille du tableau vaut un nombre entre 1 et 5
JetonScience* Joueur::choisirJetonScience(JetonScience** liste_jetons, unsigned int taille_tableau){
    std::cout << "Choisissez un jeton science parmi les suivants: " << std::endl;
    unsigned int compteur = 1; // permet de compter les jetons sciences dispo
    for (int i = 0; i<taille_tableau; i++){
        if (liste_jetons[i] != nullptr){
            std::cout << compteur << " : " << liste_jetons[i]->get_capacite() << std::endl;
            compteur++;
        }
    }
    if (compteur == 0){ //si il n'y a plus de jetons science disponibles in game 
        std::cout << "Il n'y a plus de jetons science disponibles" << std::endl;
        return nullptr;
    }
    int choix;
    std::cin >> choix;
    while (choix <= 0 || choix > taille_tableau || choix != (int)choix){
        std::cout << "Choix invalide, veuillez choisir un nombre entre 1 et "<< taille_tableau << std::endl;
        std::cin >> choix;
    }
    JetonScience* res = liste_jetons[choix-1];
    liste_jetons[choix-1] = nullptr;
    return res;
}

//Rappel : using Action = std::tuple<Carte*, std::string>; 
//! faut plutot utiliser la fonction actionsLegales du controleur, c'est plus simple et plus complète parceque ca prend
//! en compte les merveilles
Action Joueur::choisir_action(PlateauCartes* plateau_cartes){
    Carte** cartes = plateau_cartes->getCartesAccessibles();
    unsigned int taille = plateau_cartes->getNbCartesAccessibles();
    Carte* carte = choisirCarte(cartes, taille);

    std::string action;
    std::cout << "Voulez-vous construire ou defausser la carte ?" << std::endl;
    std::cin >> action;
    while (action != "construire" && action != "defausser"){
        std::cout << "Action invalide, veuillez choisir entre 'construire' et 'defausser'" << std::endl;
        std::cin >> action;
    }
    return std::make_tuple(carte, action);
}

Action Joueur::choisir_action(Action* actions){
    // std::cout<< "get Instance?" << std:: endl; //! test
    Controleur* jeu =  &Controleur::getInstance();
    // std::cout<< "get Instance ok" << std:: endl; //! test
    // std::cout<< "get adversaire?" << std:: endl; //! test
    Joueur* advers = jeu->autreJoueur(this);
    // std::cout<< "get adversaire ok" << std:: endl; //! test
    
    std::cout<< "Vous avez: "<< this->getMonnaie() << " pieces." << std::endl;
    std::cout << "Choisissez une action parmi les suivantes: " << std::endl;
    int count = 0;
    for (int i=0; i<60; i++){
        if(std::get<1>(actions[i]) != "ignore"){
            Carte* carte = std::get<0>(actions[i]);
            
            if(std::get<1>(actions[i]) == "construire"){
                std::cout << i+1 << " : construire (" << carte->get_type() << ") "<<carte->getNom() 
                    << " /Cout = " << getCout(*carte, *advers)<<std::endl;
                count++;
            }
            else{
                unsigned int cout_defauss = 2 + getNbCartesType("RessourcePrimaire") + getNbCartesType("RessourceSecondaire");
                // std::cout<< "defausserCarte: nb cartesprim: "<< getNbCartesType("RessourcePrimaire")<< std::endl; //!test
                // std::cout<< "defausserCarte: nb cartessec: "<< getNbCartesType("RessourceSecondaire")<< std::endl; //!test
                // std::cout<< "defausserCarte: cout_defauss = : "<< cout_defauss<< std::endl; //!test


                std::cout << i+1 << " : defausser (" << carte->get_type() << ") "<<carte->getNom() << " /Cout = " << cout_defauss <<std::endl;
                count++;
            }
            
        }
    }
    int choix;
    std::cin >> choix;
    while (choix <= 0 || choix > count || choix != (int)choix){
        std::cout << "Choix invalide, veuillez choisir un nombre entre 1 et " << count << std::endl;
        std::cin >> choix;
    }
    return actions[choix-1];
}

/*---------------Classe SymbolesScience----------------*/
unsigned int Joueur::getNbSymbolesScience()const{
    unsigned int res = 0;
    if(symboles_science.roue > 0) res++;
    if(symboles_science.plume > 0) res++;
    if(symboles_science.pilon > 0) res++;
    if(symboles_science.balance > 0) res++;
    if(symboles_science.globe_terrestre > 0) res++;
    if(symboles_science.fil_a_plomb > 0) res++;
    if(symboles_science.bateau > 0) res++;
    if(symboles_science.autre == true) res++;
    return res;
}

void Joueur::addSymboleScience(const SymboleScience s, PlateauScience* plateau_science){
    switch (s)
    {
    case SymboleScience::roue: 
        symboles_science.roue++;
        if(symboles_science.roue == 2) construireJeton(choisirJetonScience(plateau_science->getJetonInGame(), 5));
        break;
    case SymboleScience::plume:
        symboles_science.plume++;
        if(symboles_science.plume == 2) construireJeton(choisirJetonScience(plateau_science->getJetonInGame(), 5));
        break;
    case SymboleScience::pilon:
        symboles_science.pilon++;
        if(symboles_science.pilon == 2) construireJeton(choisirJetonScience(plateau_science->getJetonInGame(), 5));
        break;
    case SymboleScience::balance:
        symboles_science.balance++;
        if(symboles_science.balance ==2) construireJeton(choisirJetonScience(plateau_science->getJetonInGame(), 5));;
        break;
    case SymboleScience::globe_terrestre:
        symboles_science.globe_terrestre++;
        if(symboles_science.globe_terrestre == 2) construireJeton(choisirJetonScience(plateau_science->getJetonInGame(), 5));;
        break;
    case SymboleScience::fil_a_plomb:
        symboles_science.fil_a_plomb++;
        if(symboles_science.fil_a_plomb == 2) construireJeton(choisirJetonScience(plateau_science->getJetonInGame(), 5));;
        break;
    case SymboleScience::bateau:
        symboles_science.bateau++;
        if(symboles_science.bateau == 2) construireJeton(choisirJetonScience(plateau_science->getJetonInGame(), 5));;
        break;
    default:
        break;
    }
}


void Joueur::removeSymboleScience(SymboleScience& s){
        switch (s)
    {
    case SymboleScience::roue: 
        if(symboles_science.roue>0) symboles_science.roue--;
        break;
    case SymboleScience::plume:
        if(symboles_science.plume>0) symboles_science.plume--;
        break;
    case SymboleScience::pilon:
        if(symboles_science.pilon>0) symboles_science.pilon--;
        break;
    case SymboleScience::balance:
        if(symboles_science.balance>0) symboles_science.balance--;
        break;
    case SymboleScience::globe_terrestre:
        if(symboles_science.globe_terrestre>0) symboles_science.globe_terrestre--;
        break;
    case SymboleScience::fil_a_plomb:
        if(symboles_science.fil_a_plomb>0) symboles_science.fil_a_plomb--;
        break;
    case SymboleScience::bateau:
        if(symboles_science.bateau>0) symboles_science.bateau--;
        break;
    default:
        break;
    }
}

/*------------classe SymbolesChainage----------------*/
void Joueur::setSymboleChainage(SymboleChainage s, bool var) {
    switch (s) {
        case SymboleChainage::jarre: 
            symboles_chainage.jarre = var; 
            break;
        case SymboleChainage::toneau:
            symboles_chainage.toneau = var;
            break;
        case SymboleChainage::masque:
            symboles_chainage.masque = var;
            break;
        case SymboleChainage::temple:
            symboles_chainage.temple = var;
            break;
        case SymboleChainage::soleil:
            symboles_chainage.soleil = var;
            break;
        case SymboleChainage::goute:
            symboles_chainage.goute = var;
            break;
        case SymboleChainage::lune:
            symboles_chainage.lune = var;
            break;
        case SymboleChainage::pilier:
            symboles_chainage.pilier = var;
            break;
        case SymboleChainage::cible:
            symboles_chainage.cible = var;
            break;
        case SymboleChainage::casque:
            symboles_chainage.casque = var;
            break;
        case SymboleChainage::fer_a_cheval:
            symboles_chainage.fer_a_cheval = var;
            break;
        case SymboleChainage::epee:
            symboles_chainage.epee = var;
            break;
        case SymboleChainage::tour:
            symboles_chainage.tour = var;
            break;
        case SymboleChainage::lyre:
            symboles_chainage.lyre = var;
            break;
        case SymboleChainage::engrenage:
            symboles_chainage.engrenage = var;
            break;
        case SymboleChainage::livre:
            symboles_chainage.livre = var;
            break;
        case SymboleChainage::lampe:
            symboles_chainage.lampe = var;
            break;
        case SymboleChainage::none:
            break;
        default:
            SetException("erreur: Symbole de chainage non existant");
            break;
    }
}


void Joueur::addSymboleChainage(SymboleChainage s) {
    switch (s) {
        case SymboleChainage::jarre: 
            symboles_chainage.jarre = true; 
            break;
        case SymboleChainage::toneau:
            symboles_chainage.toneau = true;
            break;
        case SymboleChainage::masque:
            symboles_chainage.masque = true;
            break;
        case SymboleChainage::temple:
            symboles_chainage.temple = true;
            break;
        case SymboleChainage::soleil:
            symboles_chainage.soleil = true;
            break;
        case SymboleChainage::goute:
            symboles_chainage.goute = true;
            break;
        case SymboleChainage::lune:
            symboles_chainage.lune = true;
            break;
        case SymboleChainage::pilier:
            symboles_chainage.pilier = true;
            break;
        case SymboleChainage::cible:
            symboles_chainage.cible = true;
            break;
        case SymboleChainage::casque:
            symboles_chainage.casque = true;
            break;
        case SymboleChainage::fer_a_cheval:
            symboles_chainage.fer_a_cheval = true;
            break;
        case SymboleChainage::epee:
            symboles_chainage.epee = true;
            break;
        case SymboleChainage::tour:
            symboles_chainage.tour = true;
            break;
        case SymboleChainage::lyre:
            symboles_chainage.lyre = true;
            break;
        case SymboleChainage::engrenage:
            symboles_chainage.engrenage = true;
            break;
        case SymboleChainage::livre:
            symboles_chainage.livre = true;
            break;
        case SymboleChainage::lampe:
            symboles_chainage.lampe = true;
            break;
        case SymboleChainage::none:
            break;
        default:
            SetException("erreur: symbole chainage n'existe pas");
            break;
    }
}

void Joueur::removeSymboleChainage(SymboleChainage s) {
    switch (s) {
        case SymboleChainage::jarre: 
            symboles_chainage.jarre = false; 
            break;
        case SymboleChainage::toneau:
            symboles_chainage.toneau = false;
            break;
        case SymboleChainage::masque:
            symboles_chainage.masque = false;
            break;
        case SymboleChainage::temple:
            symboles_chainage.temple = false;
            break;
        case SymboleChainage::soleil:
            symboles_chainage.soleil = false;
            break;
        case SymboleChainage::goute:
            symboles_chainage.goute = false;
            break;
        case SymboleChainage::lune:
            symboles_chainage.lune = false;
            break;
        case SymboleChainage::pilier:
            symboles_chainage.pilier = false;
            break;
        case SymboleChainage::cible:
            symboles_chainage.cible = false;
            break;
        case SymboleChainage::casque:
            symboles_chainage.casque = false;
            break;
        case SymboleChainage::fer_a_cheval:
            symboles_chainage.fer_a_cheval = false;
            break;
        case SymboleChainage::epee:
            symboles_chainage.epee = false;
            break;
        case SymboleChainage::tour:
            symboles_chainage.tour = false;
            break;
        case SymboleChainage::lyre:
            symboles_chainage.lyre = false;
            break;
        case SymboleChainage::engrenage:
            symboles_chainage.engrenage = false;
            break;
        case SymboleChainage::livre:
            symboles_chainage.livre = false;
            break;
        case SymboleChainage::lampe:
            symboles_chainage.lampe = false;
            break;
        case SymboleChainage::none:
            break;
        default:
            SetException("erreur: symbole chainage n'existe pas");
            break;
    }
}

bool Joueur::possedeSymboleChainage(SymboleChainage s) const {
    switch (s) {
        case SymboleChainage::jarre: 
            return symboles_chainage.jarre;
        case SymboleChainage::toneau:
            return symboles_chainage.toneau;
        case SymboleChainage::masque:
            return symboles_chainage.masque;
        case SymboleChainage::temple:
            return symboles_chainage.temple;
        case SymboleChainage::soleil:
            return symboles_chainage.soleil;
        case SymboleChainage::goute:
            return symboles_chainage.goute;
        case SymboleChainage::lune:
            return symboles_chainage.lune;
        case SymboleChainage::pilier:
            return symboles_chainage.pilier;
        case SymboleChainage::cible:
            return symboles_chainage.cible;
        case SymboleChainage::casque:
            return symboles_chainage.casque;
        case SymboleChainage::fer_a_cheval:
            return symboles_chainage.fer_a_cheval;
        case SymboleChainage::epee:
            return symboles_chainage.epee;
        case SymboleChainage::tour:
            return symboles_chainage.tour;
        case SymboleChainage::lyre:
            return symboles_chainage.lyre;
        case SymboleChainage::engrenage:
            return symboles_chainage.engrenage;
        case SymboleChainage::livre:
            return symboles_chainage.livre;
        case SymboleChainage::lampe:
            return symboles_chainage.lampe;
        case SymboleChainage::none:
            return false;
            break;
        default:
            SetException("erreur: symbole chainage n'existe pas");
            return false; // Handle invalid case
    }
}

//méthodes de classe EffetsGuilde
void Joueur::addEffetGuilde(EffetGuilde effet) {
    switch(effet) {
        case EffetGuilde::guilde_armateurs:
            effets.guilde_armateurs = true;
            break;
        case EffetGuilde::guilde_batisseurs:
            effets.guilde_batisseurs = true;
            break;
        case EffetGuilde::guilde_commercants:
            effets.guilde_commercants = true;
            break;
        case EffetGuilde::guilde_magistrats:
            effets.guilde_magistrats = true;
            break;
        case EffetGuilde::guilde_tacticiens:
            effets.guilde_tacticiens = true;
            break;
        case EffetGuilde::guilde_scientifiques:
            effets.guilde_scientifiques = true;
            break;
        case EffetGuilde::guilde_usuriers:
            effets.guilde_usuriers = true;
            break;
        case EffetGuilde::none:
            break;
        default:
            SetException("erreur: effet guilde non existant!");
            break;
    }
}

void Joueur::removeEffetGuilde(EffetGuilde effet) {
    switch(effet) {
        case EffetGuilde::guilde_armateurs:
            effets.guilde_armateurs = false;
            break;
        case EffetGuilde::guilde_batisseurs:
            effets.guilde_batisseurs = false;
            break;
        case EffetGuilde::guilde_commercants:
            effets.guilde_commercants = false;
            break;
        case EffetGuilde::guilde_magistrats:
            effets.guilde_magistrats = false;
            break;
        case EffetGuilde::guilde_tacticiens:
            effets.guilde_tacticiens = false;
            break;
        case EffetGuilde::guilde_scientifiques:
            effets.guilde_scientifiques = false;
            break;
        case EffetGuilde::guilde_usuriers:
            effets.guilde_usuriers = false;
            break;
        case EffetGuilde::none:
            break;
        default:
            SetException("erreur: effet guilde non existant!");
            break;
    }
}



/*------------------classe Joueur----------------------*/
//constructeurs
Joueur::Joueur(): pt_victoire(0), monnaie(7),  nb_jetons(0), rejouer(false){

    // std::cout<< "Ici Joueur::Joueur()" <<std::endl; //! test

    ressources = Ressource();
    capacites = CapaciteJeton();
    symboles_science = SymbolesScience();
    symboles_chainage = SymbolesChainage();
    effets = Effets();
    for(int i=0; i<60; i++) cartes_construite[i] = nullptr;
    for(int i=0; i<5; i++) merveille_construite[i] = nullptr;
    for(int i=0; i<5; i++) merveille_non_construite[i] = nullptr;
    // std::cout<< "fin de Joueur::Joueur()" <<std::endl; //! test
}

Joueur::Joueur(const Joueur& j): monnaie(j.monnaie), pt_victoire(j.pt_victoire), nb_jetons(j.nb_jetons),
rejouer(j.rejouer), ressources(j.ressources), capacites(j.capacites), symboles_science(j.symboles_science),
symboles_chainage(j.symboles_chainage), effets(j.effets)
{
    // std:: cout<< "constructeur de recopie de Joueur."<< std::endl;
    for(int i=0; i<60; i++) cartes_construite[i] = j.cartes_construite[i];
    for(int i=0; i<5; i++) merveille_construite[i] = j.merveille_construite[i];
    for(int i=0; i<5; i++) merveille_non_construite[i] = j.merveille_non_construite[i];

}

//! Il semblerai qu'on en ai pas besoin
// Joueur& Joueur::operator=(const Joueur& j){
//     if(this != &j){
//         monnaie = j.monnaie;
//         pt_victoire = j.pt_victoire;
//         ressources = j.ressources;
//         rejouer = j.rejouer;
//         nb_jetons = j.nb_jetons;
//         ressources = j.ressources;
//         capacites = j.capacites;
//         symboles_science = j.symboles_science;
//         symboles_chainage = j.symboles_chainage;
//         effets = j.effets;
//         //free(cartes_construite);
//         //free(merveille_construite);
//         //free(merveille_non_construite);
////! ne pas faire de free ou de delete sur des tableau non alloué dynamiquement 
//         for(int i=0; i<60; i++) cartes_construite[i] = j.cartes_construite[i];
//         for(int i=0; i<5; i++) merveille_construite[i] = j.merveille_construite[i];
//         for(int i=0; i<5; i++) merveille_non_construite[i] = j.merveille_non_construite[i];
//     }
//     return *this;
// }

bool Joueur::operator==(const Joueur& j){
    return this == &j;
}

//destructeur
Joueur::~Joueur(){
    // std::cout << "destructeur de joueur" << std::endl;
    for(int i=0; i< getNbCartesConstruites(); i++) free(cartes_construite[i]);
    for(int i=0; i< getNbMerveillesConstruites(); i++) free(merveille_construite[i]);
    for(int i=0; i< getNbMerveillesNonConstruites(); i++) free(merveille_non_construite[i]);
}

// _____les getteurs_____//

//getteur de Nb de Cartes / jetons
unsigned int Joueur::getNbCartesConstruites() const{
    unsigned int i = 0;
    while(i<60 && cartes_construite[i]!= NULL){
        i++;
    }
    return i;
}

unsigned int Joueur::getNbMerveillesConstruites() const {
    unsigned int i = 0;
    while(i<5 && merveille_construite[i]!= NULL){
        i++;
    }
    return i;
}

unsigned int Joueur::getNbMerveillesNonConstruites()const{
    unsigned int i = 0;
    while(i<5 && merveille_non_construite[i]!= NULL){
        i++;
    }
    return i;
}
TypeCarte hashit(std::string const& type){
    if(type=="RessourcePrimaire") return TypeCarte::CarteRessourcePrimaire;
    if(type=="RessourceSecondaire") return TypeCarte::CarteRessourceSecondaire;
    if(type=="Commerce") return TypeCarte::CarteCommerce;
    if(type=="Guilde") return TypeCarte::CarteGuilde;
    if(type=="Militaire") return TypeCarte::CarteMilitaire;
    if(type=="Prestige") return TypeCarte::CartePrestige;
    if(type=="Science") return TypeCarte::CarteScience;
    else return TypeCarte::none;
 }

unsigned int Joueur::getNbCartesType(std::string type) const {
    switch (hashit(type)) {
        case TypeCarte::CarteRessourcePrimaire:
        {
            unsigned int res = 0;
            for (int i = 0; i < 60; ++i) {
                if (cartes_construite[i] != nullptr && cartes_construite[i]->get_type() == TypeCarte::CarteRessourcePrimaire) {
                    res++;
                }
            }
            return res;
        }
        case TypeCarte::CarteRessourceSecondaire:
        {
            unsigned int res = 0;
            for (int i = 0; i < 60; ++i) {
                if (cartes_construite[i] != nullptr && cartes_construite[i]->get_type() == TypeCarte::CarteRessourceSecondaire) {
                    res++;
                }
            }
            return res;
        }
        case TypeCarte::CarteCommerce:
        {
            unsigned int res = 0;
            for (int i = 0; i < 60; ++i) {
                if (cartes_construite[i] != nullptr && cartes_construite[i]->get_type() ==TypeCarte::CarteCommerce) {
                    res++;
                }
            }
            return res;
        }
        case TypeCarte::CarteGuilde:
        {
            unsigned int res = 0;
            for (int i = 0; i < 60; ++i) {
                if (cartes_construite[i] != nullptr && cartes_construite[i]->get_type() ==TypeCarte::CarteGuilde) {
                    res++;
                }
            }
            return res;
        }
        case TypeCarte::CarteMilitaire:
        {
            unsigned int res = 0;
            for (int i = 0; i < 60; ++i) {
                if (cartes_construite[i] != nullptr && cartes_construite[i]->get_type() == TypeCarte::CarteMilitaire) {
                    res++;
                }
            }
            return res;
        }
        case TypeCarte::CartePrestige:
        {
            unsigned int res = 0;
            for (int i = 0; i < 60; ++i) {
                if (cartes_construite[i] != nullptr && cartes_construite[i]->get_type() == TypeCarte::CartePrestige) {
                    res++;
                }
            }
            return res;
        }
        case TypeCarte::CarteScience:
        {
            unsigned int res = 0;
            for (int i = 0; i < 60; ++i) {
                if (cartes_construite[i] != nullptr && cartes_construite[i]->get_type() == TypeCarte::CarteScience) {
                    res++;
                }
            }
            return res;
        }
        default:
            return 0;
    }
}


bool Joueur::isInMerveillesNonConstruites(Merveille* merveille){
    for(int i=0; i< getNbMerveillesNonConstruites(); i++){
        if(merveille_non_construite[i] == merveille) return true;
    }
    return false;
}

void Joueur::setMerveille(Merveille* merveille){
    unsigned int nb = getNbMerveillesNonConstruites();
    if(nb == 5) throw SetException("erreur: impossible d'ajouter une merveille. limite atteinte");
    merveille_non_construite[nb] = merveille;
}


//d'autres méthodes utiles
void Joueur::gagnerArgent(int argent){
    unsigned int res = this->getMonnaie();
    res += argent;
    if (res < 0) res = 0;
    this->setMonnaie(res);
}

void Joueur::gagnerPtVictoire(unsigned int p){
    unsigned int res = this->getPtVictoire();
    res += p;
    this->setPtVictoire(res);
}

//méthodes qui permettent de rajouter une carte
void Joueur::updateRessourcesCarte(Carte* carte){
    unsigned int nb =0;
    if(carte->get_type() == TypeCarte::CarteCommerce){
        CarteCommerce* commerce = dynamic_cast<CarteCommerce*>(carte);
        if(commerce->get_contrepatrie()){
            if(carte->getQuantRessPrimProd(RessourcePrimaire::bois) == 1)
                effets.depot_bois = true;
            
            if(carte->getQuantRessPrimProd(RessourcePrimaire::brique) == 1)
                effets.depot_argile = true;

            if(carte->getQuantRessPrimProd(RessourcePrimaire::pierre) == 1)
                effets.depot_pierre = true;
            
            if(carte->getQuantRessSecondProd(RessourceSecondaire::verre) == 1 && carte->getQuantRessSecondProd(RessourceSecondaire::parchemin) == 1)
                effets.douanes = true;

        }
        if(commerce->get_choix()){
            if(carte->getQuantRessPrimProd(RessourcePrimaire::bois) == 1 && carte->getQuantRessPrimProd(RessourcePrimaire::brique) == 1 
            && carte->getQuantRessPrimProd(RessourcePrimaire::pierre) == 1) ressources.caravanserail = true;

            if(carte->getQuantRessSecondProd(RessourceSecondaire::verre) == 1 && carte->getQuantRessSecondProd(RessourceSecondaire::parchemin) == 1)
                ressources.forum = true;
        }

    }
    else{
        nb = carte->getQuantRessPrimProd(RessourcePrimaire::bois);
        ajouterRessource(RessourcePrimaire::bois, nb);

        nb = carte->getQuantRessPrimProd(RessourcePrimaire::brique);
        ajouterRessource(RessourcePrimaire::brique, nb);

        nb = carte->getQuantRessPrimProd(RessourcePrimaire::pierre);
        ajouterRessource(RessourcePrimaire::pierre, nb);

        nb = carte->getQuantRessSecondProd(RessourceSecondaire::verre);
        ajouterRessource(RessourceSecondaire::verre, nb);

        nb = carte->getQuantRessSecondProd(RessourceSecondaire::parchemin);
        ajouterRessource(RessourceSecondaire::parchemin, nb);
    }
}

void Joueur::updatePtVictoireCarte(Carte* carte){
    gagnerPtVictoire(carte->getPtVictoire());
}

void Joueur::updateSymbolesChainageCarte(Carte* carte){ 
    if(carte->getSymboleChainageSortie() != SymboleChainage::none){
        addSymboleChainage(carte->getSymboleChainageSortie());
    }
}


void Joueur::updateSymbolesScienceCarte(Carte* carte, PlateauScience* plateau_sciencea){
    if(carte->get_type()== TypeCarte::CarteScience){
        addSymboleScience(carte->getSymboleScience(), plateau_sciencea);
    }
}

void Joueur::updateEffetsGuilde(Carte* carte){
    if(carte->get_type() == TypeCarte::CarteGuilde){
        addEffetGuilde(carte->get_effet_guilde());
    }
}

void Joueur::addCarte(Carte* carte, PlateauScience* plateau_science){
    if( carte->get_type()==TypeCarte::Merveille){
        Merveille* merveille = dynamic_cast<Merveille*>(carte);
        bool found = false;
        unsigned int nb = getNbMerveillesNonConstruites();
        for(int i=0; i<nb; i++){
            if (merveille_non_construite[i] == merveille)
                found = true;
            
            if (found && i < nb - 1) 
                merveille_non_construite[i] = merveille_non_construite[i + 1];
        }
        if (found) {
            merveille_non_construite[nb - 1] = nullptr;
            merveille_construite[getNbMerveillesConstruites()] = merveille;
        }
        updateRessourcesCarte(carte);
    }
    else{
        unsigned int nb = getNbCartesConstruites();
        cartes_construite[nb] = carte;
        updatePtVictoireCarte(carte);
        updateSymbolesChainageCarte(carte);
        if(carte->get_type() == TypeCarte::CarteRessourcePrimaire || carte->get_type() == TypeCarte::CarteRessourceSecondaire){
            updateRessourcesCarte(carte);
        }


        if(carte->get_type() == TypeCarte::CarteScience) updateSymbolesScienceCarte(carte, plateau_science);
        if(carte->get_type()== TypeCarte::CarteGuilde) updateEffetsGuilde(carte);
    }
} 


void Joueur::retirerCarte(Carte* carte){
    if(carte->get_type() == TypeCarte::CarteRessourcePrimaire || carte->get_type() == TypeCarte::CarteRessourceSecondaire){
        unsigned int nb =0;
        nb = carte->getQuantRessPrimProd(RessourcePrimaire::bois);
        retirerRessource(RessourcePrimaire::bois, nb);

        nb = carte->getQuantRessPrimProd(RessourcePrimaire::brique);
        retirerRessource(RessourcePrimaire::brique, nb);

        nb = carte->getQuantRessPrimProd(RessourcePrimaire::pierre);
        retirerRessource(RessourcePrimaire::pierre, nb);

        nb = carte->getQuantRessPrimProd(RessourcePrimaire::bois);
        retirerRessource(RessourcePrimaire::bois, nb);

        nb = carte->getQuantRessSecondProd(RessourceSecondaire::verre);
        retirerRessource(RessourceSecondaire::verre, nb);

        nb = carte->getQuantRessSecondProd(RessourceSecondaire::parchemin);
        retirerRessource(RessourceSecondaire::parchemin, nb);
    }
}


//construire une carte
unsigned int Joueur::getCout(const Carte& carte, Joueur& adversaire) {
    if(possedeSymboleChainage(carte.getSymboleChainageEntre())){
        // std::cout<< "a symbole chainage" << std::endl; //!test
        return 0;
    }
    unsigned int cout = 0;
    bool forum = ressources.forum;
    bool caravanserail = ressources.caravanserail;

    // gérer ressources primaires
    int diff_pierre = carte.getQuantRessPrimNess(RessourcePrimaire::pierre) - getQuantiteDeRessourcePrimaire(RessourcePrimaire::pierre);
    int diff_bois = carte.getQuantRessPrimNess(RessourcePrimaire::bois) - getQuantiteDeRessourcePrimaire(RessourcePrimaire::bois);
    int diff_brique = carte.getQuantRessPrimNess(RessourcePrimaire::brique) - getQuantiteDeRessourcePrimaire(RessourcePrimaire::brique);


    if(diff_pierre > 0) {
        if(caravanserail){
            diff_pierre --;
            caravanserail = false;
        }
        if(effets.depot_pierre) cout += diff_pierre;
        else cout += diff_pierre * (2 + adversaire.getQuantiteDeRessourcePrimaire(RessourcePrimaire::pierre));
    }
    
    if(diff_bois > 0) {
        if(caravanserail){
            diff_bois --;
            caravanserail = false;
        }
        if(effets.depot_bois) cout += diff_bois;
        else cout += diff_bois * (2 + adversaire.getQuantiteDeRessourcePrimaire(RessourcePrimaire::bois));
    }

    if(diff_brique > 0) {
        if(caravanserail){
            diff_brique --;
            caravanserail = false;
        }
        if(effets.depot_argile) cout+= diff_brique;
        else cout += diff_brique * (2 + adversaire.getQuantiteDeRessourcePrimaire(RessourcePrimaire::brique));
    }

    // gérer ressources secondaires
    int diff_verre = carte.getQuantRessSecondNess(RessourceSecondaire::verre) - getQuantiteDeRessourceSecondaire(RessourceSecondaire::verre);
    int diff_parchemin = carte.getQuantRessSecondNess(RessourceSecondaire::parchemin) - getQuantiteDeRessourceSecondaire(RessourceSecondaire::parchemin);

    if(diff_verre > 0) {
        if(forum){
            diff_verre --;
            forum = false;
        }
        if(effets.douanes) cout+= diff_verre;
        else cout += diff_verre * (2 + adversaire.getQuantiteDeRessourceSecondaire(RessourceSecondaire::verre));
    }

    
    if(diff_parchemin > 0) {
        if(forum){
            diff_parchemin --;
            forum = false;
        }
        if(effets.douanes) cout+= diff_parchemin;
        else cout += diff_parchemin * (2 + adversaire.getQuantiteDeRessourceSecondaire(RessourceSecondaire::parchemin));
    }
    
    cout += carte.getPrix();
    // std::cout<< "cout de "<< carte.getNom()  << " ="<< cout << std::endl; //!test
    return cout;
}



/*-------------------------------------IARandom-------------------------------------*/

Action IARandom::choisir_action(Action* actions){
    if (std::get<1>(actions[0])== "ignore") {
        throw std::invalid_argument("The actions array is empty or invalid.");
    }
    int cmpt = 0;
    while(std::get<1>(actions[cmpt]) != "ignore"){
        cmpt++;
    }
    cmpt--;
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, cmpt);

    // Get a random index
    int randomIndex = dis(gen);
    Action resultat = actions[randomIndex];
    Controleur* jeu = &Controleur::getInstance();    

    if(std::get<1>(resultat) == "construire"){
        std::cout<<"action effectuée par l'IA: "<<std::get<1>(resultat) 
        << " ("<< std::get<0>(resultat)->get_type() << ") "
        <<std::get<0>(resultat)->getNom()<< "/ Cout = "<<
        getCout(*std::get<0>(resultat), *jeu->autreJoueur(this)) << std::endl;
    }
    else{
        unsigned int cout_defauss = 2 + getNbCartesType("RessourcePrimaire") + getNbCartesType("RessourceSecondaire");
        std::cout<<"action effectuée par l'IA: "<<std::get<1>(resultat) 
        << " ("<< std::get<0>(resultat)->get_type() << ") "
        <<std::get<0>(resultat)->getNom()<< "/ Cout = "<<
        cout_defauss << std::endl;
    }
    return actions[randomIndex];
}
 

Carte* IARandom::choisirCarte(Carte** liste_cartes, unsigned int taille_tableau){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, taille_tableau-1);

    int randomIndex = dis(gen);
    return liste_cartes[randomIndex];
}

Merveille* IARandom::choisirMerveille(Merveille** liste_merveille, unsigned int taille_tableau){
    for(int i = 0; i<taille_tableau; i++){
        if(liste_merveille[i]!= nullptr){
            return liste_merveille[i];
        }
    }
    return nullptr;

}



JetonScience* IARandom::choisirJetonScience(JetonScience** liste_jetons, unsigned int taille_tableau){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, taille_tableau-1);

    int randomIndex = dis(gen);
    return liste_jetons[randomIndex];
}

