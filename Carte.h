
#include <iostream>
#include <string>


/*-------------------------------------CONSTANTES DE L'ENVIRONEMENT-------------------------------------*/
const unsigned int Taille_cout_primaire = 3;
const unsigned int Taille_cout_secondaire = 2;
const unsigned int Taille_prod_primaire = 3;
const unsigned int Taille_prod_secondaire = 2;
const unsigned int Taille_capacite = 3;

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
    guilde_armateurs,
    guilde_batisseurs,
    guilde_commercants,
    guilde_magistrats,
    guilde_tacticiens,
    guilde_scientifiques,
    guilde_usuriers
};


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


class Carte{
protected:
    std::string nom;
    unsigned int age;
    unsigned int cout_construction;
    RessourcePrimaire* materiaux_construction_primaires;
    RessourceSecondaire* materiaux_construction_secondaires;
    bool accessible;
    bool face_visible;
    unsigned int position; //Je propose qu'on mette la position de la carte directement dans la classCarte,
    //on met à 0 si elle n'est pas sur le plateau, et sinon, on commence à 1.
    //c'est interessent parceque du coup on peut faire une méthode qui verifie directement si la carte est dans le plateau
    //en faissant un if position:

    //attribut static pt étre à rajouter pr la taille de la liste de materiaux primaire
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
    unsigned int get_position() const {return position;}
    unsigned int getPrix() const {return cout_construction;}
    bool est_facevisible() const {return face_visible;}
    bool est_accessible() const {return accessible;}
    unsigned int getQuantiteDeRessourcePrimaire(const RessourcePrimaire& symbole,RessourcePrimaire* Resp)
    unsigned int getQuantiteDeRessourceSecondaire(const RessourcePrimaire& symbole,RessourcePrimaire* ResS)
    RessourcePrimaire* getMateriauxPrimaires()const {return materiaux_construction_primaires;}
    RessourceSecondaire* getMateriauxSecondaires()const {return materiaux_construction_secondaires;}

    // virtual std::string get_type() const = 0; //pas encore définie
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
    // std::string get_type() const override {return "CarteRessourcePrimaire";};
    //destructeur
    virtual ~CarteRessourcePrimaire();
};

class CarteRessourceSecondaire : public Carte{
private:
    RessourceSecondaire production;  //Pas de liste car produit toujours 1 seul ressource

public:
    //constructeur
    CarteRessourceSecondaire();
    CarteRessourceSecondaire(std::string n, unsigned int a, unsigned int cout, RessourceSecondaire production, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc, bool fv, unsigned int pos);
    CarteRessourceSecondaire(const CarteRessourceSecondaire &c);

    //méthodes
    RessourceSecondaire get_production() const {return production;}
    // std::string get_type() const override {return "CarteRessourceSecondaire";}
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
    CarteCommerce(std::initializer_list<RessourcePrimaire> prod_primaire, std::initializer_list<RessourceSecondaire> prod_secondaire, Capacite capa, SymboleChainage symb, bool choix, bool contrepartie, unsigned int pt_victoire,std::string n, unsigned int a, unsigned int cout,std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc, bool fv, unsigned int pos);
    CarteCommerce(const CarteCommerce& c);

    RessourcePrimaire* get_production_primaire()const {return production_primaire;}
    RessourceSecondaire* get_production_secondaire()const {return production_secondaire;}
    bool get_choix()const {return choix;}
    bool get_contrepatrie()const {return contrepartie;}
    Capacite get_capacite()const {return capacite;}
    unsigned int get_pt_victoire()const {return pt_victoire;}
    SymboleChainage get_symbole_chainage()const {return symbole;}

    void set_symbole_chainage(SymboleChainage s){symbole = s;}
    void set_choix(bool c){choix = c;}
    void set_contrepartie(bool c){contrepartie = c;}
    void set_pt_victoire(unsigned int n){pt_victoire =n;}
    void set_capacite(Capacite c){capacite = c;}
    void set_production_primaire(RessourcePrimaire* pt);
    void set_production_secondaire(RessourceSecondaire* pt);

    // std::string get_type() const override {return "CarteCommerce";};
    //destructeur
    virtual ~CarteCommerce();

};


class CarteScience : public Carte{
private:
    SymboleScience symbole_science;
    SymboleChainage symbole_chainage;
    Capacite capacite;
    unsigned int pt_victoire;
    //Capacite capacite; //il faut pt étre pas rajouter ca ici. On déclence la capacite ssi il ya deux cartes avec meme symbole scientifique
public:
    CarteScience();
    CarteScience(std::string n, unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc, bool fv, unsigned int pos, SymboleChainage& symb_chain, SymboleScience& symb_science, unsigned int pt_vict);
    //constructeur de recopie
    CarteScience(const CarteScience &c);

    unsigned int get_pt_victoire()const {return pt_victoire;}
    SymboleChainage get_symbole_chainage() const  {return symbole_chainage;}
    SymboleScience get_symbole_science() const {return symbole_science;}
    Capacite get_capacite() const {return capacite;}

    void set_symbole_chainage(SymboleChainage s){symbole_chainage = s;}
    void set_pt_victoire(unsigned int n){pt_victoire =n;}
    void set_symbole_science(SymboleScience s){symbole_science = s;}


    // std::string get_type() const override {return "CarteScience";}
    //destructeur
    virtual ~CarteScience(){};

};

class CartePrestige : public Carte{
private:
    unsigned int pt_victoire;
    SymboleChainage symbole_chainage;

public:
    CartePrestige();
    CartePrestige(std::string n, unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc, bool fv, unsigned int pos, SymboleChainage& symb_chain, unsigned int pt_vict);
    CartePrestige(const CartePrestige& c);
    unsigned int get_pt_victoire()const {return pt_victoire;}
    SymboleChainage get_symbole_chainage() const  {return symbole_chainage;}
    void set_symbole_chainage(SymboleChainage s){symbole_chainage = s;}
    void set_pt_victoire(unsigned int n){pt_victoire =n;}

    // std::string get_type() const override {return "CartePrestige";}
    //destructeur
    virtual ~CartePrestige(){};
};


class CarteMilitaire : public Carte{
private:
    unsigned int nb_symbole_militaire;
    Capacite capacite;
    SymboleChainage symbole_chainage;

public:

    CarteMilitaire();
    CarteMilitaire(std::string n, unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc, bool fv, unsigned int pos, SymboleChainage& symb_chain, unsigned int nb_militaire);
    CarteMilitaire(const CarteMilitaire& c);

    Capacite get_capacite() const {return capacite;}
    unsigned int get_nb_symbole_militaire() const {return nb_symbole_militaire;}
    SymboleChainage get_symbole_chainage() const  {return symbole_chainage;}

    void set_nb_symbole_militaire(unsigned int nb){nb_symbole_militaire=nb;}
    void set_symbole_chainage(SymboleChainage s){symbole_chainage = s;}

    // std::string get_type() const override {return "CarteMilitaire";}

    //destructeur
    virtual ~CarteMilitaire(){};
};


class CarteGuilde : public Carte{
private:
    EffetGuilde effet_guilde;
public:
    CarteGuilde();
    CarteGuilde(std::string n, unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc, bool fv, unsigned int pos, EffetGuilde effet);
    CarteGuilde(const CarteGuilde& c);

    EffetGuilde get_effet_guilde(){return effet_guilde;}
    void set_effet_guilde(EffetGuilde& effet){effet_guilde = effet;}
    //void applique_effet_guilde(Joueur& joueur1, Joueur& joueur2);//fonction et arguement a définir plus tard
    // std::string get_type() const override {return "CarteGuilde";};

    //destructeur
    virtual ~CarteGuilde(){};
};


class Merveille : public Carte{
private:
    unsigned int pt_victoire;
    unsigned int avance_militaire;
    RessourcePrimaire* production_primaire;
    RessourceSecondaire* production_secondaire;
    Capacite* capacite;

public:
    Merveille();
    Merveille(std::initializer_list<RessourcePrimaire> prod_primaire, std::initializer_list<RessourceSecondaire> prod_secondaire, std::initializer_list<Capacite> capa, unsigned int pt_victoire, unsigned int av_milit, std::string n, unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc, bool fv, unsigned int pos);
    Merveille(const Merveille& c);

    // std::string get_type() const override {return "Merveille";};

    //destructeur
    virtual ~Merveille();
};










