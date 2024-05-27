#pragma once
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

void Joueur::construireJeton(JetonScience& jeton){
    // switch (jeton)
    // {
    // case CapaciteScience::loi: symboles_science.autre = true; break;
    // case CapaciteScience::agriculture:
    //     gagnerArgent(6);
    //     gagnerPtVictoire(4);
    //     break;
    // case CapaciteScience::philosophie:
    //     gagnerPtVictoire(7);
    //     break;
    // default: addCapaciteJeton(jeton); break;
    // }
    jeton.exec_capacite_science(this);

    //! + gerer le fait que le jeton n'est plus prenable


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

void Joueur::addSymboleScience(const SymboleScience s){
    switch (s)
    {
    case SymboleScience::roue: 
        symboles_science.roue++;
        if(symboles_science.roue == 2) choisirJeton();
        break;
    case SymboleScience::plume:
        symboles_science.plume++;
        if(symboles_science.plume == 2) choisirJeton();
        break;
    case SymboleScience::pilon:
        symboles_science.pilon++;
        if(symboles_science.pilon == 2) choisirJeton();
        break;
    case SymboleScience::balance:
        symboles_science.balance++;
        if(symboles_science.balance ==2) choisirJeton();
        break;
    case SymboleScience::globe_terrestre:
        symboles_science.globe_terrestre++;
        if(symboles_science.globe_terrestre == 2) choisirJeton();
        break;
    case SymboleScience::fil_a_plomb:
        symboles_science.fil_a_plomb++;
        if(symboles_science.fil_a_plomb == 2) choisirJeton();
        break;
    case SymboleScience::bateau:
        symboles_science.bateau++;
        if(symboles_science.bateau == 2) choisirJeton();
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
            return true;
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
            effets_guilde.guilde_armateurs = true;
            break;
        case EffetGuilde::guilde_batisseurs:
            effets_guilde.guilde_batisseurs = true;
            break;
        case EffetGuilde::guilde_commercants:
            effets_guilde.guilde_commercants = true;
            break;
        case EffetGuilde::guilde_magistrats:
            effets_guilde.guilde_magistrats = true;
            break;
        case EffetGuilde::guilde_tacticiens:
            effets_guilde.guilde_tacticiens = true;
            break;
        case EffetGuilde::guilde_scientifiques:
            effets_guilde.guilde_scientifiques = true;
            break;
        case EffetGuilde::guilde_usuriers:
            effets_guilde.guilde_usuriers = true;
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
            effets_guilde.guilde_armateurs = false;
            break;
        case EffetGuilde::guilde_batisseurs:
            effets_guilde.guilde_batisseurs = false;
            break;
        case EffetGuilde::guilde_commercants:
            effets_guilde.guilde_commercants = false;
            break;
        case EffetGuilde::guilde_magistrats:
            effets_guilde.guilde_magistrats = false;
            break;
        case EffetGuilde::guilde_tacticiens:
            effets_guilde.guilde_tacticiens = false;
            break;
        case EffetGuilde::guilde_scientifiques:
            effets_guilde.guilde_scientifiques = false;
            break;
        case EffetGuilde::guilde_usuriers:
            effets_guilde.guilde_usuriers = false;
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
    ressources = Ressource();
    capacites = CapaciteJeton();
    symboles_science = SymbolesScience();
    symboles_chainage = SymbolesChainage();
    effets_guilde = EffetsGuilde();
    for(int i=0; i<60; i++) cartes_construite[i] = nullptr;
    for(int i=0; i<4; i++) merveille_construite[i] = nullptr;
    for(int i=0; i<4; i++) merveille_non_construite[i] = nullptr;
}

Joueur::Joueur(const Joueur& j): monnaie(j.monnaie), pt_victoire(j.pt_victoire), nb_jetons(j.nb_jetons),
rejouer(j.rejouer), ressources(j.ressources), capacites(j.capacites), symboles_science(j.symboles_science),
symboles_chainage(j.symboles_chainage), effets_guilde(j.effets_guilde)
{
    for(int i=0; i<60; i++) cartes_construite[i] = j.cartes_construite[i];
    for(int i=0; i<4; i++) merveille_construite[i] = j.merveille_construite[i];
    for(int i=0; i<4; i++) merveille_non_construite[i] = j.merveille_non_construite[i];

}

Joueur& Joueur::operator=(const Joueur& j){
    if(this != &j){
        monnaie = j.monnaie;
        pt_victoire = j.pt_victoire;
        ressources = j.ressources;
        rejouer = j.rejouer;
        nb_jetons = j.nb_jetons;
        ressources = j.ressources;
        capacites = j.capacites;
        symboles_science = j.symboles_science;
        symboles_chainage = j.symboles_chainage;
        effets_guilde = j.effets_guilde;
        free(cartes_construite);
        free(merveille_construite);
        free(merveille_non_construite);
        for(int i=0; i<60; i++) cartes_construite[i] = j.cartes_construite[i];
        for(int i=0; i<4; i++) merveille_construite[i] = j.merveille_construite[i];
        for(int i=0; i<4; i++) merveille_non_construite[i] = j.merveille_non_construite[i];
    }
    return *this;
}

bool Joueur::operator==(const Joueur& j){
    return this == &j;
}

//destructeur
Joueur::~Joueur(){
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
    while(i<4 && merveille_construite[i]!= NULL){
        i++;
    }
    return i;
}

unsigned int Joueur::getNbMerveillesNonConstruites()const{
    unsigned int i = 0;
    while(i<4 && merveille_non_construite[i]!= NULL){
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
void Joueur::updateRessourcesCarte(Carte* carte){ //! erreur non expliqué
    unsigned int nb =0;
    nb = carte->getQuantRessPrimProd(RessourcePrimaire::bois);
    ajouterRessource(RessourcePrimaire::bois, nb);

    nb = carte->getQuantRessPrimProd(RessourcePrimaire::brique);
    ajouterRessource(RessourcePrimaire::brique, nb);

    nb = carte->getQuantRessPrimProd(RessourcePrimaire::pierre);
    ajouterRessource(RessourcePrimaire::pierre, nb);

    nb = carte->getQuantRessPrimProd(RessourcePrimaire::bois);
    ajouterRessource(RessourcePrimaire::bois, nb);

    nb = carte->getQuantRessSecondProd(RessourceSecondaire::verre);
    ajouterRessource(RessourceSecondaire::verre, nb);

    nb = carte->getQuantRessSecondProd(RessourceSecondaire::parchemin);
    ajouterRessource(RessourceSecondaire::parchemin, nb);
}

void Joueur::updatePtVictoireCarte(Carte* carte){
    gagnerPtVictoire(carte->getPtVictoire());
}

void Joueur::updateSymbolesChainageCarte(Carte* carte){ 
    if(carte->getSymboleChainageSortie() != SymboleChainage::none){
        addSymboleChainage(carte->getSymboleChainageSortie());
    }
}


void Joueur::updateSymbolesScienceCarte(Carte* carte){
    if(carte->get_type()== TypeCarte::CarteScience){
        addSymboleScience(carte->getSymboleScience());
    }
}

void Joueur::updateEffetsGuilde(Carte* carte){
    if(carte->get_type() == TypeCarte::CarteGuilde){
        addEffetGuilde(carte->get_effet_guilde());
    }
}

void Joueur::addCarte(Carte* carte){
    updatePtVictoireCarte(carte);
    updateSymbolesChainageCarte(carte);
    if(carte->get_type() == TypeCarte::CarteRessourcePrimaire || carte->get_type() == TypeCarte::CarteRessourceSecondaire){
        updateRessourcesCarte(carte);
    }
    if(carte->get_type() == TypeCarte::CarteScience) updateSymbolesScienceCarte(carte);
    if(carte->get_type()== TypeCarte::CarteGuilde) updateEffetsGuilde(carte);
    
} 


void Joueur::retirerCarte(Carte* carte){
    if(carte->get_type() == TypeCarte::CarteRessourcePrimaire || carte->get_type() == TypeCarte::CarteRessourceSecondaire){
        unsigned int nb =0;
        nb = getQuantiteDeRessourcePrimaire(RessourcePrimaire::bois);
        retirerRessource(RessourcePrimaire::bois, nb);

        nb = getQuantiteDeRessourcePrimaire(RessourcePrimaire::brique);
        retirerRessource(RessourcePrimaire::brique, nb);

        nb = getQuantiteDeRessourcePrimaire(RessourcePrimaire::pierre);
        retirerRessource(RessourcePrimaire::pierre, nb);

        nb = getQuantiteDeRessourcePrimaire(RessourcePrimaire::bois);
        retirerRessource(RessourcePrimaire::bois, nb);

        nb = getQuantiteDeRessourceSecondaire(RessourceSecondaire::verre);
        retirerRessource(RessourceSecondaire::verre, nb);

        nb = getQuantiteDeRessourceSecondaire(RessourceSecondaire::parchemin);
        retirerRessource(RessourceSecondaire::parchemin, nb);
    }
}


//construire une carte
unsigned int Joueur::getCout(const Carte& carte, Joueur& adversaire) {
    //En cours
    //COÛT = 2 + nombre de symboles de la même ressource produite par les
    //cartes marron et grises de la cité adverse
    if(possedeSymboleChainage(carte.getSymboleChainageEntre())) return 0;
    unsigned int cout = 0;

    // gérer ressources primaires
    int diff_pierre = carte.getQuantRessPrimNess(RessourcePrimaire::pierre) - getQuantiteDeRessourcePrimaire(RessourcePrimaire::pierre);
    if(diff_pierre > 0) {
        cout += diff_pierre * (2 + adversaire.getQuantiteDeRessourcePrimaire(RessourcePrimaire::pierre));
    }

    int diff_bois = carte.getQuantRessPrimNess(RessourcePrimaire::bois) - getQuantiteDeRessourcePrimaire(RessourcePrimaire::bois);
    if(diff_bois > 0) {
        cout += diff_bois * (2 + adversaire.getQuantiteDeRessourcePrimaire(RessourcePrimaire::bois));
    }

    int diff_brique = carte.getQuantRessPrimNess(RessourcePrimaire::brique) - getQuantiteDeRessourcePrimaire(RessourcePrimaire::brique);
    if(diff_brique > 0) {
        cout += diff_brique * (2 + adversaire.getQuantiteDeRessourcePrimaire(RessourcePrimaire::brique));
    }

    // gérer ressources secondaires
    int diff_verre = carte.getQuantRessSecondNess(RessourceSecondaire::verre) - getQuantiteDeRessourceSecondaire(RessourceSecondaire::verre);
    if(diff_verre > 0) {
        cout += diff_verre * (2 + adversaire.getQuantiteDeRessourceSecondaire(RessourceSecondaire::verre));
    }

    int diff_parchemin = carte.getQuantRessSecondNess(RessourceSecondaire::parchemin) - getQuantiteDeRessourceSecondaire(RessourceSecondaire::parchemin);
    if(diff_parchemin > 0) {
        cout += diff_parchemin * (2 + adversaire.getQuantiteDeRessourceSecondaire(RessourceSecondaire::parchemin));
    }

    return cout;
}


/*
void Joueur::construireCarte(Carte& carte, PlateauCartes& p){
    Carte* c = p.trouverCarteDansPlateau(carte);
    if((c != NULL) && estConstructible(carte)){
        monnaie -= getCout(carte);
        p.enleverCarteDuPlateau(c);
        unsigned int nb = getNbCartesConstruites();
        cartes_construite[nb] = &carte;
        //addSymboleChainage(carte);
    }
    else{
        SetException("Impossible de construire la carte!");
    }
}





//méthodes de vérification 
bool Joueur::estConstructible(const Carte& carte) const{ //! erreur due à getCout() donc pas grave pour l'instant
    //!rajouter les liens de chainage.....
    SymboleChainage lien_chainage = carte.getSymboleChainageEntre();
    if(getCout(carte) < getMonnaie() || possedeSymboleChainage(lien_chainage)) return true;
    else return false;
}

*/
/*-------------------------------------PlateauCarte-------------------------------------*/
 