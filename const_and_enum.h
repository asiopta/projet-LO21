#ifndef CONST_AND_ENUM_H
#define CONST_AND_ENUM_H

const unsigned int Taille_cout_primaire = 5;
const unsigned int Taille_cout_secondaire = 3;
const unsigned int Taille_prod_primaire = 3;
const unsigned int Taille_prod_secondaire = 2;
const unsigned int Taille_capacite = 3;

enum class TypeCarte{
    none,
    CarteRessourcePrimaire,
    CarteRessourceSecondaire,
    CarteCommerce,
    CarteGuilde,
    CarteMilitaire,
    CartePrestige, 
    CarteScience,
    Merveille
};

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
    none,
    roue,
    plume,
    pilon,
    balance,
    globe_terrestre,
    fil_a_plomb,
    bateau,
};


enum class EffetGuilde{
    none,
    guilde_armateurs,
    guilde_batisseurs,
    guilde_commercants,
    guilde_magistrats,
    guilde_tacticiens,
    guilde_scientifiques,
    guilde_usuriers
};


enum class Capacite{
    none, //pas de capacité
    rejouer, //reservé à Merveille
    detruire_carte_marron, //reservé à Merveille
    detruire_carte_grise, //reservé à Merveille
    jouer_carte_defausse, //reservé à Merveille
    gagner_monnaie_3, //reservé à Merveille
    gagner_monnaie_4, //reserve à CarteCommerce
    gagner_monnaie_6, //reservé à CarteCommerce et Merveille
    gagner_monnaie_12, //reservé à Merveille
    gagner_monnaie_2_par_merveille, //reservé à CarteCommerce
    gagner_monnaie_carte_marron, //reservé à CarteCommerce
    gagner_monnaie_carte_grise, //reservé à CarteCommerce
    gagner_monnaie_carte_rouge, //reservé à CarteCommerce
    gagner_monnaie_carte_jaune, //reservé à CarteCommerce
    perdre_monnaie_3, //reservé à Merveille
    avancee_militaire, //pour Merveille et CarteMilitaire
    choisir_jeton_science, //pour Merveille
    ajouter_symbole_science //pour CarteScience
};


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


std::ostream& operator<<(std::ostream& f,CapaciteScience capacite_science);




#endif // CONST_AND_ENUM_H