#ifndef CARTE_H
#define CARTE_H

#pragma once
#include "Joueur.h"
#include "Plateau.h"
#include <iostream>
#include <string>
#include "const_and_enum.h"

//! Predeclaration de classe
class Joueur;
class PlateauMilitaire;
class PlateauScience;
class PlateauCartes;



class Carte{

protected:
    std::string nom;
    unsigned int age;
    unsigned int cout_construction;
    RessourcePrimaire* materiaux_construction_primaires;
    RessourceSecondaire* materiaux_construction_secondaires;
    bool accessible;
    bool face_visible;
    unsigned int position;
public:
    //constructeur
    Carte();
    Carte(std::string n,unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc, bool fv, unsigned int pos);
    //constructeur de recopie
    Carte(const Carte &c);

    //methodes
    void set_position(unsigned int pos); //def in cpp
    void set_materiaux_construction_primaire(RessourcePrimaire r); //def in cpp
    void set_materiaux_construction_secondaire(RessourceSecondaire r); //def in cpp
    void set_accessible(); //def in cpp
    void set_face_visible(); //def in cpp

    std::ostream& operator<<(std::ostream& f) const;
    std::string getNom() const {return nom;}
    unsigned int get_position() const {return position;}
    unsigned int getPrix() const {return cout_construction;}
    bool est_facevisible() const {return face_visible;}
    bool est_accessible() const {return accessible;}

    unsigned int getQuantiteDeRessourcePrimaire(const RessourcePrimaire& symbole,RessourcePrimaire* Resp) const;
    unsigned int getQuantiteDeRessourceSecondaire(const RessourceSecondaire& symbole,RessourceSecondaire* ResS) const;
    RessourcePrimaire* getMateriauxPrimaires()const {return materiaux_construction_primaires;}
    RessourceSecondaire* getMateriauxSecondaires()const {return materiaux_construction_secondaires;}
    virtual EffetGuilde get_effet_guilde() const {return EffetGuilde::none;}
    virtual TypeCarte get_type() const = 0;
    virtual unsigned int getPtVictoire() const {return 0;}
    virtual SymboleScience getSymboleScience() const {return SymboleScience::none;}
    virtual SymboleChainage getSymboleChainageEntre() const {return SymboleChainage::none;}
    virtual SymboleChainage getSymboleChainageSortie() const {return SymboleChainage::none;}
    virtual unsigned int getQuantRessPrimProd(RessourcePrimaire rp) const {return 0;}
    virtual unsigned int getQuantRessSecondProd(RessourceSecondaire rs) const {return 0;}
    unsigned int getQuantRessPrimNess(RessourcePrimaire rp) const ;
    unsigned int getQuantRessSecondNess(RessourceSecondaire rs) const ;

    //destructeur
    virtual ~Carte();
};

class CarteRessourcePrimaire : public Carte{
private:
    RessourcePrimaire* production;

public:
    //constructeur
    CarteRessourcePrimaire();
    CarteRessourcePrimaire(std::string nom, unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> production, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc = false, bool fv = false, unsigned int pos = 0);
    CarteRessourcePrimaire(const CarteRessourcePrimaire &c);
    RessourcePrimaire* get_production() const {return production;}
    void set_production(RessourcePrimaire r); //def in cpp
    // les cartes marron ne peuvent étre construites qu'avec la monnaie
    TypeCarte get_type() const override {return TypeCarte::CarteRessourcePrimaire;};
    unsigned int getQuantRessPrimProd(RessourcePrimaire rp) const override;
    //destructeur
    virtual ~CarteRessourcePrimaire();
};

class CarteRessourceSecondaire : public Carte{
private:
    RessourceSecondaire production;  //Pas de liste car produit toujours 1 seul ressource

public:
    //constructeur
    CarteRessourceSecondaire();
    CarteRessourceSecondaire(std::string n, unsigned int a, unsigned int cout, RessourceSecondaire production, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc = false, bool fv = false, unsigned int pos = 0);
    CarteRessourceSecondaire(const CarteRessourceSecondaire &c);

    //méthodes
    RessourceSecondaire get_production() const {return production;}
    TypeCarte get_type() const override {return TypeCarte::CarteRessourceSecondaire;};
    void set_production(RessourceSecondaire r); //def in cpp
    unsigned int getQuantRessSecondProd(RessourceSecondaire rs) const override;

    //destructeur
    virtual  ~CarteRessourceSecondaire(){};
};

class CarteCommerce : public Carte{
private:
    RessourcePrimaire* production_primaire; //taille3
    RessourceSecondaire* production_secondaire; //taille 2
    Capacite capacite;
    SymboleChainage symbole_chainage_entre;
    SymboleChainage symbole_chainage_sortie;
    bool choix;
    bool contrepartie;
    unsigned int pt_victoire;

public:
    CarteCommerce();
    CarteCommerce(std::initializer_list<RessourcePrimaire> prod_primaire, std::initializer_list<RessourceSecondaire> prod_secondaire, Capacite capa, SymboleChainage symb_entre,SymboleChainage symb_sortie, bool choix, bool contrepartie, unsigned int pt_victoire,std::string n, unsigned int a, unsigned int cout,std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc = false, bool fv = false, unsigned int pos = 0);
    CarteCommerce(const CarteCommerce& c);

    RessourcePrimaire* get_production_primaire()const {return production_primaire;}
    RessourceSecondaire* get_production_secondaire()const {return production_secondaire;}
    bool get_choix()const {return choix;}
    bool get_contrepatrie()const {return contrepartie;}
    Capacite get_capacite()const {return capacite;}
    unsigned int getPtVictoire()const override{return pt_victoire;}
    SymboleChainage getSymboleChainageEntre() const override {return symbole_chainage_entre;}
    SymboleChainage getSymboleChainageSortie() const override {return symbole_chainage_sortie;}
    unsigned int getQuantRessPrimProd(RessourcePrimaire rp) const override;
    unsigned int getQuantRessSecondProd(RessourceSecondaire rs) const override;

    void set_choix(bool c){choix = c;}
    void set_contrepartie(bool c){contrepartie = c;}
    void set_pt_victoire(unsigned int n){pt_victoire =n;}
    void set_capacite(Capacite c){capacite = c;}
    void set_production_primaire(RessourcePrimaire* pt);
    void set_production_secondaire(RessourceSecondaire* pt);

    void exec_capacite(Joueur& joueur1) const;
    TypeCarte get_type() const override {return TypeCarte::CarteCommerce;};

    //destructeur
    virtual ~CarteCommerce();

};


class CarteScience : public Carte{
private:
    SymboleScience symbole_science;
    SymboleChainage symbole_chainage_entre;
    SymboleChainage symbole_chainage_sortie;
    Capacite capacite;
    unsigned int pt_victoire;
    //Capacite capacite; //il faut pt étre pas rajouter ca ici. On déclence la capacite ssi il ya deux cartes avec meme symbole scientifique
public:
    CarteScience();
    CarteScience(std::string n,unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, SymboleChainage symb_chain_entre, SymboleChainage symb_chain_sortie, SymboleScience symb_science, unsigned int pt_vict);
    
    //constructeur de recopie
    CarteScience(const CarteScience &c);

    unsigned int getPtVictoire()const override{return pt_victoire;}
    SymboleChainage getSymboleChainageEntre() const override {return symbole_chainage_entre;}
    SymboleChainage getSymboleChainageSortie() const override {return symbole_chainage_sortie;}
    SymboleScience getSymboleScience() const override {return symbole_science;}
    Capacite get_capacite() const {return capacite;}


    void set_pt_victoire(unsigned int n){pt_victoire =n;}
    void set_symbole_science(SymboleScience s){symbole_science = s;}

    void exec_capacite(Joueur* joueur1, PlateauScience* plateau_science) const; //
    TypeCarte get_type() const override {return TypeCarte::CarteScience;};
    //destructeur
    virtual ~CarteScience(){};

};

class CartePrestige : public Carte{
private:
    unsigned int pt_victoire;
    SymboleChainage symbole_chainage_entre;
    SymboleChainage symbole_chainage_sortie;

public:
    CartePrestige();
    CartePrestige(std::string n,unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, SymboleChainage symb_chain_entre,SymboleChainage symb_chain_sortie, unsigned int pt_vict);
    CartePrestige(const CartePrestige& c);
    unsigned int getPtVictoire()const override{return pt_victoire;}
    SymboleChainage getSymboleChainageEntre() const override {return symbole_chainage_entre;}
    SymboleChainage getSymboleChainageSortie() const override {return symbole_chainage_sortie;}
    void set_pt_victoire(unsigned int n){pt_victoire =n;}

    TypeCarte get_type() const override {return TypeCarte::CartePrestige;};
    //destructeur
    virtual ~CartePrestige(){};
};


class CarteMilitaire : public Carte{
private:
    unsigned int nb_symbole_militaire;
    Capacite capacite;
    SymboleChainage symbole_chainage_entre;
    SymboleChainage symbole_chainage_sortie;

public:

    CarteMilitaire();
    CarteMilitaire(std::string n, unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, SymboleChainage symb_chain_entre, SymboleChainage symb_chain_sortie, unsigned int nb_militaire);
    CarteMilitaire(const CarteMilitaire& c);

    unsigned int get_nb_symbole_militaire() const {return nb_symbole_militaire;}
    SymboleChainage getSymboleChainageEntre() const override {return symbole_chainage_entre;}
    SymboleChainage getSymboleChainageSortie() const override {return symbole_chainage_sortie;}

    

    void set_nb_symbole_militaire(unsigned int nb){nb_symbole_militaire=nb;}


    void exec_capacite(Joueur* joueur_adverse, PlateauMilitaire& plateau_militaire) ;
    TypeCarte get_type() const override {return TypeCarte::CarteMilitaire;}; 

    //destructeur
    virtual ~CarteMilitaire(){};
};




class CarteGuilde : public Carte{
private:
    EffetGuilde effet_guilde;
public:
    CarteGuilde();
    CarteGuilde(std::string n, unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, EffetGuilde effet);
    CarteGuilde(const CarteGuilde& c);

    EffetGuilde get_effet_guilde(){return effet_guilde;}
    void set_effet_guilde(EffetGuilde& effet){effet_guilde = effet;};
    void exec_effet_guilde(Joueur& joueur1, Joueur& joueur2) const;
    TypeCarte get_type() const override {return TypeCarte::CarteGuilde;}; 

    //destructeur
    virtual ~CarteGuilde(){};
};


class Merveille : public Carte{
private:
    unsigned int pt_victoire;
    unsigned int avance_militaire;
    bool choix;
    RessourcePrimaire* production_primaire;
    RessourceSecondaire* production_secondaire;
    Capacite* capacite;

public:
    Merveille();
    Merveille(std::initializer_list<RessourcePrimaire> prod_primaire, std::initializer_list<RessourceSecondaire> prod_secondaire, std::initializer_list<Capacite> capa, unsigned int pt_victoire, unsigned int av_milit, bool choix, std::string n, unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire);
    Merveille(const Merveille& c);

    bool get_choix()const {return choix;}
    void addCapacite(Capacite c); 
    
    void set_choix(bool c){choix = c;}
    void exec_capacite(Joueur* joueur1, Joueur* joueur2, PlateauCartes& plateau_carte, PlateauMilitaire& plateau_militaire, PlateauScience& plateau_science) const;
    void exec_rejouer(Joueur* joueur1) const;
    void exec_detruire_carte_marron(Joueur* joueur1, Joueur* joueur2) const;
    void exec_detruire_carte_grise(Joueur* joueur1, Joueur* joueur2) const;
    void exec_jouer_carte_defausse(Joueur* joueur1, PlateauCartes& plateau_carte) const;
    void exec_gagner_monnaie_12(Joueur* joueur1) const;
    void exec_gagner_monnaie_3(Joueur* joueur1) const;
    void exec_gagner_monnaie_6(Joueur* joueur1) const;
    void exec_perdre_monnaie_3(Joueur* joueur1) const;
    void exec_avancee_militaire(Joueur* joueur1, PlateauMilitaire& plateau_militaire) const;
    void exec_choisir_jeton_science(Joueur* joueur1, PlateauScience& plateau_science) const;

    unsigned int getPtVictoire()const override{return pt_victoire;}
    unsigned int getQuantRessPrimProd(RessourcePrimaire rp) const override;
    unsigned int getQuantRessSecondProd(RessourceSecondaire rs) const override;

    TypeCarte get_type() const override {return TypeCarte::Merveille;}; 

    //destructeur
    virtual ~Merveille();
};


std::ostream& operator<<(std::ostream& f, TypeCarte type);







#endif