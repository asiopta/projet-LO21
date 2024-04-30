
#include <iostream>
#include <string>
#include "Joueur.h"
enum class CapaciteScience{
    none,
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
class JetonScience {
private:
    CapaciteScience capacite;

public:
    JetonScience();
    JetonScience(CapaciteScience capacite);
    void exec_capacite_science();

};


class JetonMalus{
private:
    unsigned int malus;
    Joueur& joueur; // je pense que c'est mieux de passer joueur comme pointeur. (ou meme int 1 ou 2)
    // on a besoin que d'identifier de quel joueur il s'agit et pas vraiment de ttes les infos 
    // que contient la classe Joueur. jsp

public:
    JetonMalus();
    JetonMalus(unsigned int m, Joueur& j);
    void exec_malus();
};


class PlateauScience{
private:
    const int Dim_jetons_in_game = 5; //est la dimension du tableau jeton_in_game
    const int Dim_liste_position = 5; //est la dimension du tableau liste_position
    const int Dim_jetons_out_game = 5; //est la dimension du tableau jeton_out_game
    JetonScience *jeton_in_game;
    unsigned int *liste_position;
    JetonScience *jeton_out_game;

public:
    PlateauScience();
    PlateauScience(JetonScience *in_game, JetonScience *out_game);
    JetonScience* tirer_jeton();
    void retirer_jeton(JetonScience& jeton);
    void ajouter_jeton_in_game(JetonScience& jeton);
    void ajouter_jeton_out_game(JetonScience& jeton);
    ~PlateauScience();
};

