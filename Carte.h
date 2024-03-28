#pragma once
#include <iostream>
#include <string>


enum class RessourcePrimaire {
    none,
    pierre,
    bois,
    brique
};

enum class RessourceSecondaire {
    none,
    verre,
    parchemin
};

enum class SymboleChainage{
    jarre,
    toneau,
    masque,
    temple, 
    soleil, 
    goute, 
    lune, 
    pilier, 
    cible, 
    casque, 
    fer_a_cheval, 
    epee, 
    tour, 
    lyre, 
    engrenage, 
    livre, 
    lampe 
};

enum class SymboleScience{
    roue, 
    plume, 
    pilon,
    balance, 
    globe_terrestre, 
    fil_a_plomb,
    bateau, 
};

enum class EffetGuilde{
    guilde_Armateurs,
    guilde_Batisseurs,
    guilde_Commercants,
    guilde_Magistrats,
    guilde_Tacticiens,
    guilde_Scientifiques,
    guilde_Usuriers
};

enum class Capacite{
    rejouer,
    detruire_carte_marron,
    detruire_carte_grise,
    jouer_carte_defausse,
    gagner_monnaie,
    avancee_militaire,
    choisir_jeton_science,
    ajouter_symbole_science    
};

enum class CapaciteScience{
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



class Carte{
protected:
    unsigned int cout_construction;
    RessourcePrimaire* materiaux_construction_primaires;
    RessourceSecondaire* materiaux_construction_secondaires;
    bool accessible;
    bool face_visible;
    unsigned int position; //Je propose qu'on mette la position de la carte directement dans la classCarte, 
    //on met à 0 si elle n'est pas sur le plateau, et sinon, on commence à 1.
    //c'est interessent parceque du coup on peut faire une méthode qui verifie directement si la carte est dans le plateau
    //en faissant un if position:

public:
    //constructeur
    Carte();
    Carte(unsigned int cout, RessourcePrimaire* pt_primaire, RessourceSecondaire* pt_secondaire, bool acc, bool fv, unsigned int pos);
    //constructeur de recopie 
    Carte(const Carte &c);

    //methodes
    void set_position(unsigned int pos); //def in cpp
    void set_materiaux_construction_primaire(RessourcePrimaire r); //def in cpp 
    void set_materiaux_construction_secondaire(RessourceSecondaire r); //def in cpp
    void set_accessible(); //def in cpp
    void set_face_visible(); //def in cpp

    unsigned int get_position() const {return position;}
    unsigned int getPrix() const {return cout_construction;}
    bool est_facevisible() const {return face_visible;}
    bool est_accessible() const {return accessible;}
    RessourcePrimaire* getMateriauxPrimaires()const {return materiaux_construction_primaires;}
    RessourceSecondaire* getMateriauxSecondaires()const {return materiaux_construction_secondaires;}
    
    virtual std::string gettype() const = 0; //pas encore définie
    //destructeur
    virtual ~Carte();
};
