#pragma once
#include <iostream>
#include <string>
#include "Joueur.h"
#include "Carte.h"
#include "Plateau.h"


//génération des cartes
//? Carte(std::string n,unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc, bool fv, unsigned int pos);
//CarteRessourcePrimaire(std::string nom, unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> production, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc = false, bool fv = false, unsigned int pos = 0)
//CarteRessourcePrimaire chantier = CarteRessourcePrimaire("Chantier", 1, 0, {RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none},{RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none} );

//c'est un exemple 
//des que vous voulez mettre des tableau mettez des {element1, element2 ...}
//! Ne pas depasser la taille du tableau !!
//! Vous pouvez donner un tableau plus petit que la taille max mais c'est pas recommandé, c'est pour ca que j'ai mis des none



// age 1

/*CarteRessourcePrimaire(std::string nom, unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> production, 
std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc = false, 
bool fv = false, unsigned int pos = 0);*/

CarteRessourcePrimaire chantier = CarteRessourcePrimaire("Chantier", 1, 0, {RessourcePrimaire::bois, 
RessourcePrimaire::none, RessourcePrimaire::none},{RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none});

CarteRessourcePrimaire exploitation = CarteRessourcePrimaire("Exploitation", 1, 1, {RessourcePrimaire::bois, 
RessourcePrimaire::none, RessourcePrimaire::none},{RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none});

CarteRessourcePrimaire bassinArgileux = CarteRessourcePrimaire("BassinArgileux", 1, 0, {RessourcePrimaire::brique, 
RessourcePrimaire::none, RessourcePrimaire::none},{RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none});

CarteRessourcePrimaire cavite = CarteRessourcePrimaire("Cavite", 1, 1, {RessourcePrimaire::brique, 
RessourcePrimaire::none, RessourcePrimaire::none},{RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none});

CarteRessourcePrimaire gisement = CarteRessourcePrimaire("Gisement", 1, 0, {RessourcePrimaire::pierre, 
RessourcePrimaire::none, RessourcePrimaire::none},{RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none} );

CarteRessourcePrimaire mine = CarteRessourcePrimaire("Mine", 1, 1, {RessourcePrimaire::pierre, 
RessourcePrimaire::none, RessourcePrimaire::none},{RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none} );


/*CarteRessourceSecondaire(std::string n, unsigned int a, unsigned int cout, RessourceSecondaire production, 
std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc = false, 
bool fv = false, unsigned int pos = 0);*/

CarteRessourceSecondaire verrerie = CarteRessourceSecondaire("Verrerie", 1, 1, RessourceSecondaire::verre,
{RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none} );

CarteRessourceSecondaire presse = CarteRessourceSecondaire("Presse", 1, 1, RessourceSecondaire::parchemin,
{RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none} );


/*CarteCommerce(std::initializer_list<RessourcePrimaire> prod_primaire, std::initializer_list<RessourceSecondaire> prod_secondaire, 
Capacite capa, SymboleChainage symb_entre,SymboleChainage symb_sortie, bool choix, bool contrepartie, unsigned int pt_victoire,std::string n, 
unsigned int a, unsigned int cout,std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, 
bool acc = false, bool fv = false, unsigned int pos = 0);*/

CarteCommerce depotDePierre = CarteCommerce({RessourcePrimaire::pierre, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::none, Capacite::none, Capacite::none}, 
SymboleChainage::none, SymboleChainage::none, false, true, 0, "DepotDePierre", 1, 3, {RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none} );

CarteCommerce depotdArgile = CarteCommerce({RessourcePrimaire::brique, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::none, Capacite::none, Capacite::none}, 
SymboleChainage::none, SymboleChainage::none, false, true, "DepotDArgile", 1, 3, {RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none} );

CarteCommerce depotDeBois = CarteCommerce({RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::none, Capacite::none, Capacite::none}, 
SymboleChainage::none, SymboleChainage::none, false, true, "DepotDeBois", 1, 3, {RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none} );

CarteCommerce taverne = CarteCommerce({RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::gagner_monnaie_4, Capacite::none, Capacite::none}, SymboleChainage::none, 
SymboleChainage::jarre, false, false, "Taverne", 1, 0, {RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none} );


/*CartePrestige(std::string n,unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, 
std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc = false, bool fv = false, unsigned int pos = 0, 
SymboleChainage symb_chain_entre,SymboleChainage symb_chain_sortie, unsigned int pt_vict);*/

CartePrestige theatre = CartePrestige("Theatre", 1, 0, {RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::masque, 3);

CartePrestige autel = CartePrestige("Autel", 1, 0, {RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::lune, 3);

CartePrestige bains = CartePrestige("Bains", 1, 0, {RessourcePrimaire::pierre, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::goute, 3);


/*CarteMilitaire(std::string n, unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, 
std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc = false, bool fv = false, unsigned int pos = 0, 
SymboleChainage symb_chain_entre, SymboleChainage symb_chain_sortie, unsigned int nb_militaire);*/

CarteMilitaire tourDeGarde = CarteMilitaire("TourDeGarde", 1, 0, {RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, 
RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::none, 1);

CarteMilitaire ecuries = CarteMilitaire("Ecuries", 1, 0, {RessourcePrimaire::bois, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, 
RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::fer_a_cheval, 1);

CarteMilitaire caserne = CarteMilitaire("Caserne", 1, 0, {RessourcePrimaire::brique, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, 
RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::epee, 1);

CarteMilitaire palissade = CarteMilitaire("Palissade", 1, 2, {RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, 
RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::tour, 1);


/*CarteScience(std::string n,unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, 
std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc = false, bool fv = false, unsigned int pos = 0, 
SymboleChainage symb_chain_entre, SymboleChainage symb_chain_sortie, SymboleScience symb_science, unsigned int pt_vict);*/

CarteScience atelier = CarteScience("Atelier", 1, 0, {RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::parchemin, 
RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::none, SymboleScience::fil_a_plomb, 1);

CarteScience apothicaire = CarteScience("Apothicaire", 1, 0, {RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, 
RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::none, SymboleScience::roue, 1);

CarteScience scriptorium = CarteScience("Scriptorium", 1, 2, {RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, 
RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::livre, SymboleScience::plume, 0);

CarteScience officine = CarteScience("Officine", 1, 2, {RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, 
RessourceSecondaire::none}, SymboleChainage::none, SymboleChainage::engrenage, SymboleScience::pilon, 0);




// age 2

/*CarteRessourcePrimaire(std::string nom, unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> production, 
std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc = false, 
bool fv = false, unsigned int pos = 0);*/

CarteRessourcePrimaire scierie = CarteRessourcePrimaire("Scierie", 2, 2, {RessourcePrimaire::bois, 
RessourcePrimaire::bois, RessourcePrimaire::none}, {RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, 
RessourceSecondaire::none} );

CarteRessourcePrimaire briqueterie = CarteRessourcePrimaire("Briqueterie", 2, 2, {RessourcePrimaire::brique, 
RessourcePrimaire::brique, RessourcePrimaire::none},{RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, 
RessourceSecondaire::none} );

CarteRessourcePrimaire carriere = CarteRessourcePrimaire("Carriere", 2, 2, {RessourcePrimaire::pierre, 
RessourcePrimaire::pierre, RessourcePrimaire::none},{RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none,
 RessourceSecondaire::none} );


/*CarteRessourceSecondaire(std::string n, unsigned int a, unsigned int cout, RessourceSecondaire production, 
std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc = false, 
bool fv = false, unsigned int pos = 0);*/

CarteRessourceSecondaire soufflerie = CarteRessourceSecondaire("Soufflerie", 2, 0, RessourceSecondaire::verre,
{RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none} );

CarteRessourceSecondaire sechoir = CarteRessourceSecondaire("Sechoir", 2, 0, RessourceSecondaire::parchemin,
{RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none} );


/*CarteCommerce(std::initializer_list<RessourcePrimaire> prod_primaire, std::initializer_list<RessourceSecondaire> prod_secondaire, 
Capacite capa, SymboleChainage symb_entre,SymboleChainage symb_sortie, bool choix, bool contrepartie, unsigned int pt_victoire,std::string n, 
unsigned int a, unsigned int cout,std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, 
bool acc = false, bool fv = false, unsigned int pos = 0);*/

CarteCommerce forum = CarteCommerce({RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::verre, RessourceSecondaire::parchemin}, {Capacite::none, Capacite::none, Capacite::none}, 
SymboleChainage::none, SymboleChainage::none, true, false, 0, "Forum", 2, 3, {RessourcePrimaire::brique, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none} );

CarteCommerce caravanserail = CarteCommerce({RessourcePrimaire::bois, RessourcePrimaire::brique, RessourcePrimaire::pierre}, 
{RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::none, Capacite::none, Capacite::none}, 
SymboleChainage::none, SymboleChainage::none, true, false, 0, "Caravanserail", 2, 2, {RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::verre, RessourceSecondaire::parchemin} );

CarteCommerce douanes = CarteCommerce({RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::verre, RessourceSecondaire::parchemin}, {Capacite::none, Capacite::none, Capacite::none}, SymboleChainage::none, SymboleChainage::none, false, true, 
0, "Douanes", 2, 4, {RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none} );

CarteCommerce brasserie = CarteCommerce({RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::gagner_monnaie_6, Capacite::none, Capacite::none}, 
SymboleChainage::none, SymboleChainage::toneau, false, false, 0, "Brasserie", 2, 0, {RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none} );


/*CartePrestige(std::string n,unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, 
std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc = false, bool fv = false, unsigned int pos = 0, 
SymboleChainage symb_chain_entre,SymboleChainage symb_chain_sortie, unsigned int pt_vict);*/

CartePrestige tribunal = CartePrestige("Tribunal", 2, 0, {RessourcePrimaire::bois, RessourcePrimaire::bois, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::none}, 
SymboleChainage::none, SymboleChainage::none, 5);

CartePrestige statue = CartePrestige("Statue", 2, 0, {RessourcePrimaire::brique, RessourcePrimaire::brique, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, 
SymboleChainage::masque, SymboleChainage::pilier, 4);

CartePrestige temple = CartePrestige("Temple", 2, 0, {RessourcePrimaire::bois, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::none}, 
SymboleChainage::lune, SymboleChainage::soleil, 4);

CartePrestige aqueduc = CartePrestige("Aqueduc", 2, 0, {RessourcePrimaire::pierre, RessourcePrimaire::pierre, 
RessourcePrimaire::pierre, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, 
SymboleChainage::goute, SymboleChainage::none, 5);

CartePrestige rostres = CartePrestige("Rostres", 2, 0, {RessourcePrimaire::pierre, RessourcePrimaire::bois, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, 
SymboleChainage::none, SymboleChainage::temple, 4);


/*CarteMilitaire(std::string n, unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, 
std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc = false, bool fv = false, unsigned int pos = 0, 
SymboleChainage symb_chain_entre, SymboleChainage symb_chain_sortie, unsigned int nb_militaire);*/

CarteMilitaire muraille = CarteMilitaire("Muraille", 2, 0, {RessourcePrimaire::pierre, RessourcePrimaire::pierre, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, 
SymboleChainage::none, SymboleChainage::none, 2);

CarteMilitaire haras = CarteMilitaire("Haras", 2, 0, {RessourcePrimaire::brique, RessourcePrimaire::bois, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, 
SymboleChainage::fer_a_cheval, SymboleChainage::none, 1);

CarteMilitaire baraquements = CarteMilitaire("Baraquements", 2, 3, {RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, 
SymboleChainage::epee, SymboleChainage::none, 1);

CarteMilitaire champDeTir = CarteMilitaire("ChampDeTir", 2, 0, {RessourcePrimaire::pierre, RessourcePrimaire::bois, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::none}, 
SymboleChainage::none, SymboleChainage::cible, 2);

CarteMilitaire placedArmes = CarteMilitaire("PlaceDArmes", 2, 0, {RessourcePrimaire::brique, RessourcePrimaire::brique, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::none}, 
SymboleChainage::none, SymboleChainage::casque, 2);


/*CarteScience(std::string n,unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, 
std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc = false, bool fv = false, unsigned int pos = 0, 
SymboleChainage symb_chain_entre, SymboleChainage symb_chain_sortie, SymboleScience symb_science, unsigned int pt_vict);*/

CarteScience bibliotheque = CarteScience("Bibliotheque", 2, 0, {RessourcePrimaire::pierre, RessourcePrimaire::bois, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::none}, 
SymboleChainage::livre, SymboleChainage::none, SymboleScience::plume, 2);

CarteScience dispensaire = CarteScience("Dispensaire", 2, 0, {RessourcePrimaire::brique, RessourcePrimaire::brique, 
RessourcePrimaire::pierre, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, 
SymboleChainage::engrenage, SymboleChainage::none, SymboleScience::pilon, 2);

CarteScience ecole = CarteScience("Ecole", 2, 0, {RessourcePrimaire::bois, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, SymboleChainage::none,
{RessourceSecondaire::parchemin, RessourceSecondaire::parchemin}, 
SymboleChainage::lyre, SymboleScience::roue, 1);

CarteScience laboratoire = CarteScience("Laboratoire", 2, 0, {RessourcePrimaire::bois, RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::verre}, SymboleChainage::none,
SymboleChainage::lampe, SymboleScience::fil_a_plomb, 1);










// age 3

////////////// COMMENT GERER LES RECOMPENSES ?
CarteCommerce chambreDeCommerce = CarteCommerce({RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::none, Capacite::none, Capacite::none}, SymboleChainage::none, false, false, 
3, "ChambreDeCommerce", 3, 0, {RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::parchemin, RessourceSecondaire::parchemin} );
CarteCommerce port = CarteCommerce({RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::none, Capacite::none, Capacite::none}, SymboleChainage::none, false, false, 
3, "Port", 3, 0, {RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::verre, RessourceSecondaire::parchemin} );
CarteCommerce armurerie = CarteCommerce({RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::none, Capacite::none, Capacite::none}, SymboleChainage::none, false, false, 
3, "Armurerie", 3, 0, {RessourcePrimaire::pierre, RessourcePrimaire::pierre, RessourcePrimaire::none}, 
{RessourceSecondaire::verre, RessourceSecondaire::none} );
CarteCommerce phare = CarteCommerce({RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::none, Capacite::none, Capacite::none}, SymboleChainage::none, false, false, 
3, "Phare", 3, 0, {RessourcePrimaire::brique, RessourcePrimaire::brique, RessourcePrimaire::none}, 
{RessourceSecondaire::verre, RessourceSecondaire::none} );
CarteCommerce arene = CarteCommerce({RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::none, Capacite::none, Capacite::none}, SymboleChainage::none, false, false, 
3, "Arene", 3, 0, {RessourcePrimaire::brique, RessourcePrimaire::pierre, RessourcePrimaire::bois}, 
{RessourceSecondaire::none, RessourceSecondaire::none} );
////////////////////////


CartePrestige palace = CartePrestige("Palace", 3, 0, {RessourcePrimaire::brique, RessourcePrimaire::pierre, 
RessourcePrimaire::bois}, {RessourceSecondaire::verre, RessourceSecondaire::verre} , 
SymboleChainage::none, 7);
//////////////// PROBLEME : IL FAUT 5 RESSOURCES PRIMAIRES
CartePrestige hotelDeVille = CartePrestige("HotelDeVille", 3, 0, {RessourcePrimaire::pierre, RessourcePrimaire::pierre, 
RessourcePrimaire::pierre}, {RessourceSecondaire::none, RessourceSecondaire::none} , 
SymboleChainage::none, 7);
//////////
CartePrestige obelisque = CartePrestige("Obelisque", 3, 0, {RessourcePrimaire::pierre, RessourcePrimaire::pierre, 
RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::none} , 
SymboleChainage::none, 5);
//////////////// PROBLEME : IL FAUT 4 RESSOURCES PRIMAIRES
CartePrestige jardins = CartePrestige("Jardins", 3, 0, {RessourcePrimaire::brique, RessourcePrimaire::brique, 
RessourcePrimaire::bois}, {RessourceSecondaire::none, RessourceSecondaire::none} , 
SymboleChainage::none, 6);
//////////
CartePrestige pantheon = CartePrestige("Pantheon", 3, 0, {RessourcePrimaire::brique, RessourcePrimaire::bois, 
RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::parchemin} , 
SymboleChainage::none, 6);
CartePrestige senat = CartePrestige("Senat", 3, 0, {RessourcePrimaire::brique, RessourcePrimaire::brique, 
RessourcePrimaire::pierre}, {RessourceSecondaire::parchemin, RessourceSecondaire::none} , 
SymboleChainage::none, 5);


//////////////// PROBLEME : IL FAUT 5 RESSOURCES PRIMAIRES
CarteMilitaire arsenal = CarteMilitaire("Arsenal", 3, 0, {RessourcePrimaire::brique, RessourcePrimaire::brique, 
RessourcePrimaire::brique}, {RessourceSecondaire::none, RessourceSecondaire::none} , 
SymboleChainage::none, 3);
//////////
CarteMilitaire pretoire = CarteMilitaire("Pretoire", 3, 8, {RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none} , 
SymboleChainage::none, 3);
CarteMilitaire fortifications = CarteMilitaire("Fortifications", 3, 0, {RessourcePrimaire::pierre, RessourcePrimaire::pierre, 
RessourcePrimaire::brique}, {RessourceSecondaire::parchemin, RessourceSecondaire::none} , 
SymboleChainage::none, 2);
CarteMilitaire atelierDeSiege = CarteMilitaire("AtelierDeSiege", 3, 0, {RessourcePrimaire::bois, RessourcePrimaire::bois, 
RessourcePrimaire::bois}, {RessourceSecondaire::verre, RessourceSecondaire::none} , 
SymboleChainage::none, 2);
//////////////// PROBLEME : IL FAUT 4 RESSOURCES PRIMAIRES
CarteMilitaire cirque = CarteMilitaire("Cirque", 3, 0, {RessourcePrimaire::brique, RessourcePrimaire::brique, 
RessourcePrimaire::pierre}, {RessourceSecondaire::none, RessourceSecondaire::none} , 
SymboleChainage::none, 2);
//////////


CarteScience academie = CarteScience("Academie", 3, 0, {RessourcePrimaire::pierre, RessourcePrimaire::bois, 
RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::verre} , 
SymboleChainage::none, SymboleScience::balance, 3);
CarteScience etude = CarteScience("Etude", 3, 0, {RessourcePrimaire::bois, RessourcePrimaire::bois, 
RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::parchemin} , 
SymboleChainage::none, SymboleScience::balance, 3);
CarteScience universite = CarteScience("Universite", 3, 0, {RessourcePrimaire::brique, RessourcePrimaire::none, 
RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::parchemin} , 
SymboleChainage::none, SymboleScience::globe_terrestre, 2);
CarteScience observatoire = CarteScience("Observatoire", 3, 0, {RessourcePrimaire::pierre, RessourcePrimaire::none, 
RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::parchemin} , 
SymboleChainage::none, SymboleScience::globe_terrestre, 2);


// guildes

//////////// RETIRER L'AGE POUR LES CARTES GUILDES ? Probleme c'est un argument de carte

////////////  verifier que les effets guildes sont définis dans le code --> je crois pas 
CarteGuilde guildeDesCommercants = CarteGuilde("GuildeDesCommercants", 0, 0, {RessourcePrimaire::brique, 
RessourcePrimaire::bois, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::parchemin},
false, false, 0, EffetGuilde::guilde_commercants);
CarteGuilde guildeDesArmateurs = CarteGuilde("GuildeDesArmateurs", 0, 0, {RessourcePrimaire::brique, 
RessourcePrimaire::pierre, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::parchemin},
false, false, 0, EffetGuilde::guilde_armateurs);
//////////////// PROBLEME : IL FAUT 4 RESSOURCES PRIMAIRES
CarteGuilde guildeDesBatisseurs = CarteGuilde("GuildeDesBatisseurs", 0, 0, {RessourcePrimaire::pierre, 
RessourcePrimaire::pierre, RessourcePrimaire::brique}, {RessourceSecondaire::verre, RessourceSecondaire::none},
false, false, 0, EffetGuilde::guilde_batisseurs);
//////////
CarteGuilde guildeDesMagistrats = CarteGuilde("GuildeDesMagistrats", 0, 0, {RessourcePrimaire::bois, 
RessourcePrimaire::bois, RessourcePrimaire::brique}, {RessourceSecondaire::parchemin, RessourceSecondaire::none},
false, false, 0, EffetGuilde::guilde_magistrats);
//////////////// PROBLEME : IL FAUT 4 RESSOURCES PRIMAIRES
CarteGuilde guildeDesScientifiques = CarteGuilde("GuildeDesScientifiques", 0, 0, {RessourcePrimaire::brique, 
RessourcePrimaire::brique, RessourcePrimaire::bois}, {RessourceSecondaire::none, RessourceSecondaire::none},
false, false, 0, EffetGuilde::guilde_scientifiques);
//////////
//////////////// PROBLEME : IL FAUT 4 RESSOURCES PRIMAIRES
CarteGuilde guildeDesUsuriers = CarteGuilde("GuildeDesUsuriers", 0, 0, {RessourcePrimaire::pierre, 
RessourcePrimaire::pierre, RessourcePrimaire::bois}, {RessourceSecondaire::none, RessourceSecondaire::none},
false, false, 0, EffetGuilde::guilde_usuriers);
//////////
CarteGuilde guildeDesTacticiens = CarteGuilde("GuildeDesTacticiens", 0, 0, {RessourcePrimaire::pierre, 
RessourcePrimaire::pierre, RessourcePrimaire::brique}, {RessourceSecondaire::parchemin, RessourceSecondaire::none},
false, false, 0, EffetGuilde::guilde_tacticiens);
////////////////



// merveilles

////////////// RETIRER L'AGE POUR LES CARTES MERVEILLES ? Probleme c'est un argument de carte

////////////// VERIFIER LE COUT DES CARTES ET LES RESSOURCES NECESSAIRES

////////////// VERIFIER LA CAPACITE AVANCEE MILITAIRE : C'EST QUOI

CarteMerveille leCircusMaximus = CarteMerveille({RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::detruire_carte_grise, Capacite::none, Capacite::none}, 
3, 1, "LeCircusMaximus", 0, 0, {RessourcePrimaire::pierre, RessourcePrimaire::pierre, RessourcePrimaire::bois}, 
{RessourceSecondaire::verre, RessourceSecondaire::none} );
CarteMerveille leColosse = CarteMerveille({RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::none, Capacite::none, Capacite::none}, 
3, 2, "LeColosse", 0, 0, {RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none} );
//////////// gerer la recompense
CarteMerveille leGrandPhare = CarteMerveille({RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::none, Capacite::none, Capacite::none}, 
4, 0, "LeGrandPhare", 0, 0, {RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, 
{RessourceSecondaire::none, RessourceSecondaire::none} );
////////////
//////////// gerer la recompense de 6 pieces
CarteMerveille lesJardinsSuspendus = CarteMerveille({RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::gagner_monnaie, 
Capacite::rejouer, Capacite::none}, 3, 0, "LesJardinsSuspendus", 0, 0, {RessourcePrimaire::bois, 
RessourcePrimaire::bois, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::parchemin} );
////////////
//////////// gerer la recompense de jeton progres
CarteMerveille laGrandeBibliotheque = CarteMerveille({RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::none, 
Capacite::none, Capacite::none}, 4, 0, "LaGrandeBibliotheque", 0, 0, {RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none} );
////////////
CarteMerveille leMausolee = CarteMerveille({RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::jouer_carte_defausse, 
Capacite::none, Capacite::none}, 2, 0, "LeMausolee", 0, 0, {RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none} );
//////////// gerer la recompense de ressources secondaires (choix)
//////////// besoin de 4 ressources primaires
arteMerveille lePiree = CarteMerveille({RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none}, {RessourceSecondaire::parchemin, RessourceSecondaire::verre}, {Capacite::rejouer, 
Capacite::none, Capacite::none}, 2, 0, "LePiree", 0, 0, {RessourcePrimaire::bois, 
RessourcePrimaire::bois, RessourcePrimaire::pierre}, {RessourceSecondaire::none, RessourceSecondaire::none} );
////////////
CarteMerveille lesPyramides = CarteMerveille({RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::none, 
Capacite::none, Capacite::none}, 9, 0, "LesPyramides", 0, 0, {RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none} );
CarteMerveille leSphynx = CarteMerveille({RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::rejouer, 
Capacite::none, Capacite::none}, 6, 0, "LeSphynx", 0, 0, {RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none} );
CarteMerveille laStatueDeZeus = CarteMerveille({RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::detruire_carte_marron, 
Capacite::none, Capacite::none}, 3, 1, "LaStatueDeZeus", 0, 0, {RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none} );
//////////// gerer la recompense de 12 pieces
CarteMerveille leTempledArtemis = CarteMerveille({RessourcePrimaire::none, RessourcePrimaire::none, 
RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::gagner_monnaie, 
Capacite::rejouer, Capacite::none}, 0, 0, "LeTempleDArtemis", 0, 0, {RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none} );
////////////
//////////// gerer la recompense de 3 pieces + l'adversaire perd 3 pieces
//////////// besoin de 4 ressources primaires 
CarteMerveille laViaAppia = CarteMerveille({RessourcePrimaire::pierre, RessourcePrimaire::pierre, 
RessourcePrimaire::brique}, {RessourceSecondaire::parchemin, RessourceSecondaire::none}, {Capacite::gagner_monnaie, 
Capacite::rejouer, Capacite::none}, 3, 0, "LaViaAppia", 0, 0, {RessourcePrimaire::none, 
RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none} );
//////////



//génération des jetons science

JetonScience** liste_jetons_science = new JetonScience*[10];
liste_jetons_science[0] = nullptr;
// JetonScience* jetonAgriculture= new JetonScience(CapaciteScience::agriculture);
// JetonScience* jetonArchitecture= new JetonScience(CapaciteScience::architecture);
// JetonScience* jetonEconomie= new JetonScience(CapaciteScience::economie);
// JetonScience* jetonLoi= new JetonScience(CapaciteScience::loi);
// JetonScience* jetonMaconnerie= new JetonScience(CapaciteScience::maconnerie);
// JetonScience* jetonUrbanisme= new JetonScience(CapaciteScience::urbanisme);
// JetonScience* jetonTheologie= new JetonScience(CapaciteScience::theologie);
// JetonScience* jetonStrategie= new JetonScience(CapaciteScience::strategie);
// JetonScience* jetonPhilosophie= new JetonScience(CapaciteScience::philosophie);
// JetonScience* jetonMathematique= new JetonScience(CapaciteScience::mathematique);







//génération des jetons malus



const int NB_CARTES_AGE_1 = 23;
const int NB_CARTES_AGE_2 = 23;
const int NB_CARTES_AGE_3 = 23;
const int NB_MERVEILLES = 10;
const int NB_GUILDES = 7;

Carte* LISTE_CARTES_AGE_1 = new Carte[NB_CARTES_AGE_1];
Carte* LISTE_CARTES_AGE_2 = new Carte[NB_CARTES_AGE_2];
Carte* LISTE_CARTES_AGE_3 = new Carte[NB_CARTES_AGE_3];
Carte* LISTE_MERVEILLES = new Carte[NB_MERVEILLES];
Carte* LISTE_GUILDES = new Carte[NB_GUILDES];



