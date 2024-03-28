#pragma once
#include <iostream>
#include <string>

enum class RessourcePrimaire {
    none,
    pierre,
    bois,
    brique
};

std::ostream& operator<<(std::ostream& f, const RessourcePrimaire& r){
    switch (r){
        case RessourcePrimaire::bois: f<<"bois"; break;
        case RessourcePrimaire::pierre: f<<"pierre"; break;
        case RessourcePrimaire::brique: f<<"brique"; break;
        case RessourcePrimaire::none: f<<"none"; break;
    }
    return f;
}

enum class RessourceSecondaire {
    none,
    verre,
    parchemin
};

std::ostream& operator<<(std::ostream& f, const RessourceSecondaire& r){
    switch (r){
        case RessourceSecondaire::verre: f<<"verre"; break;
        case RessourceSecondaire::parchemin: f<<"parchemin"; break;
        case RessourceSecondaire::none: f<<"none"; break;
    }
    return f;
}

enum class SymboleChainage{
    none,
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

std::ostream& operator<<(std::ostream& f, const SymboleChainage& symbole) {
    switch (symbole) {
        case SymboleChainage::none:f << "Pas de symbole Chainage";
        case SymboleChainage::jarre:f << "Jarre"; break;
        case SymboleChainage::toneau:f << "Tonneau"; break;
        case SymboleChainage::masque:f << "Masque"; break;
        case SymboleChainage::temple: f << "Temple"; break;
        case SymboleChainage::soleil: f << "Soleil"; break;
        case SymboleChainage::goute: f << "Goutte"; break;
        case SymboleChainage::lune: f << "Lune"; break;
        case SymboleChainage::pilier: f << "Pilier"; break;
        case SymboleChainage::cible: f << "Cible"; break;
        case SymboleChainage::casque: f << "Casque"; break;
        case SymboleChainage::fer_a_cheval: f << "Fer à Cheval";break;
        case SymboleChainage::epee: f << "Epée"; break;
        case SymboleChainage::tour: f << "Tour"; break;
        case SymboleChainage::lyre: f << "Lyre"; break;
        case SymboleChainage::engrenage: f << "Engrenage"; break;
        case SymboleChainage::livre: f << "Livre"; break;
        case SymboleChainage::lampe: f << "Lampe"; break;
        default:
            f.setstate(std::ios_base::failbit);
    }
    return f;
}



enum class SymboleScience{
    roue, 
    plume, 
    pilon,
    balance, 
    globe_terrestre, 
    fil_a_plomb,
    bateau, 
};

std::ostream& operator<<(std::ostream& f, const SymboleScience& symbole) {
    switch (symbole) {
        case SymboleScience::roue: f << "Roue"; break;
        case SymboleScience::plume: f << "Plume"; break;
        case SymboleScience::pilon: f << "Pilon"; break;
        case SymboleScience::balance: f << "Balance"; break;
        case SymboleScience::globe_terrestre: f << "Globe terrestre"; break;
        case SymboleScience::fil_a_plomb: f << "Fil à plomb"; break;
        case SymboleScience::bateau: f << "Bateau"; break;
        default:
            f.setstate(std::ios_base::failbit);
    }
    return f;
}

enum class EffetGuilde{
    guilde_armateurs,
    guilde_batisseurs,
    guilde_commercants,
    guilde_magistrats,
    guilde_tacticiens,
    guilde_scientifiques,
    guilde_usuriers
};

std::ostream& operator<<(std::ostream& f, const EffetGuilde& effet) {
    switch (effet) {
        case EffetGuilde::guilde_armateurs: f << "Guilde des Armateurs"; break;
        case EffetGuilde::guilde_batisseurs: f << "Guilde des Bâtisseurs"; break;
        case EffetGuilde::guilde_commercants: f << "Guilde des Commerçants"; break;
        case EffetGuilde::guilde_magistrats: f << "Guilde des Magistrats"; break;
        case EffetGuilde::guilde_tacticiens: f << "Guilde des Tacticiens"; break;
        case EffetGuilde::guilde_scientifiques: f << "Guilde des Scientifiques"; break;
        case EffetGuilde::guilde_usuriers: f << "Guilde des Usuriers"; break;
        default:
            f.setstate(std::ios_base::failbit);
    }
    return f;
}

enum class Capacite{
    none, 
    rejouer,
    detruire_carte_marron,
    detruire_carte_grise,
    jouer_carte_defausse,
    gagner_monnaie,
    avancee_militaire,
    choisir_jeton_science,
    ajouter_symbole_science    
};

std::ostream& operator<<(std::ostream& f, const Capacite& capacite) {
    switch (capacite) {
        case Capacite::none: f<<"Pas de capacité"; break;
        case Capacite::rejouer: f << "Rejouer"; break;
        case Capacite::detruire_carte_marron: f << "Détruire une carte marron"; break;
        case Capacite::detruire_carte_grise: f << "Détruire une carte grise"; break;
        case Capacite::jouer_carte_defausse: f << "Jouer une carte de la défausse"; break;
        case Capacite::gagner_monnaie: f << "Gagner de la monnaie"; break;
        case Capacite::avancee_militaire: f << "Avancée militaire"; break;
        case Capacite::choisir_jeton_science: f << "Choisir un jeton science"; break;
        case Capacite::ajouter_symbole_science: f << "Ajouter un symbole science"; break;
        default:
            f.setstate(std::ios_base::failbit);
    }
    return f;
}

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

    std::ostream& operator<<(std::ostream f) const;
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

class CarteRessourcePrimaire : public Carte{
private:
    RessourcePrimaire* production;

public:
    //constructeur
    CarteRessourcePrimaire();
    CarteRessourcePrimaire(unsigned int cout, RessourcePrimaire* production, RessourcePrimaire* pt_primaire, RessourceSecondaire* pt_secondaire, bool acc, bool fv, unsigned int pos);
    CarteRessourcePrimaire(const CarteRessourcePrimaire &c);
    RessourcePrimaire* get_production() const {return production;}
    void set_production(RessourcePrimaire r); //def in cpp
    // les cartes marron ne peuvent étre construites qu'avec la monnaie
    std::string gettype() const override;
    //destructeur
    virtual ~CarteRessourcePrimaire();
};

class CarteRessourceSecondaire : public Carte{
private:
    RessourceSecondaire production;  //Pas de liste car produit toujours 1 seul ressource

public:
    //constructeur
    CarteRessourceSecondaire();
    CarteRessourceSecondaire(unsigned int cout, RessourceSecondaire production, RessourcePrimaire* pt_primaire, RessourceSecondaire* pt_secondaire, bool acc, bool fv, unsigned int pos);
    CarteRessourceSecondaire(const CarteRessourceSecondaire &c);

    //méthodes
    RessourceSecondaire get_production() const {return production;}
    std::string gettype() const override;
    void set_production(RessourceSecondaire r); //def in cpp

    //destructeur
    virtual  ~CarteRessourceSecondaire(){};
};

class CarteCommerce : public Carte{
private:
    RessourcePrimaire* production_primaire; //taille3
    RessourceSecondaire* production_secondaire; //taille 2
    Capacite capacite;
    SymboleChainage symbole;
    bool choix;
    bool contrepartie;
    unsigned int pt_victoire;

public:
    CarteCommerce();
    CarteCommerce(RessourcePrimaire* prod_primaire, RessourceSecondaire*prod_secondaire, Capacite capa, SymboleChainage symb, bool choix, bool contrepartie, unsigned int pt_victoire, unsigned int cout,RessourcePrimaire* pt_primaire, RessourceSecondaire* pt_secondaire, bool acc, bool fv, unsigned int pos);
    CarteCommerce(const CarteCommerce& c);

    RessourcePrimaire* get_production_primaire(){return production_primaire;}
    RessourceSecondaire* get_production_secon(){return production_secondaire;}
    bool get_choix(){return choix;}
    bool get_contrepatrie(){return contrepartie;}
    Capacite get_capacite(){return capacite;}
    unsigned int get_pt_victoire(){return pt_victoire;}
    SymboleChainage get_symbole_chainage(){return symbole;}

    void set_symbole_chainage(SymboleChainage s){symbole = s;}
    void set_choix(bool c){choix = c;}
    void set_contrepartie(bool c){contrepartie = c;}
    void set_pt_victoire(unsigned int n){pt_victoire =n;}
    void set_capacite(Capacite c){capacite = c;}
    void set_production_primaire(RessourcePrimaire* pt);
    void set_production_secondaire(RessourceSecondaire* pt);

    std::string gettype() const override;
    //destructeur
    virtual ~CarteCommerce();

};









