
#include <iostream>
#include <string>
#include "Joueur.h"
#include "Plateau.h"
#include "Carte.h"


//génération des cartes
//? Carte(std::string n,unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc, bool fv, unsigned int pos);
//CarteRessourcePrimaire(std::string nom, unsigned int a, unsigned int cout, std::initializer_list<RessourcePrimaire> production, std::initializer_list<RessourcePrimaire> pt_primaire, std::initializer_list<RessourceSecondaire> pt_secondaire, bool acc = false, bool fv = false, unsigned int pos = 0)
CarteRessourcePrimaire chantier = CarteRessourcePrimaire("Chantier", 1, 0, {RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none},{RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, false, false, 0);
//c'est un exemple 
//des que vous voulez mettre des tableau mettez des {element1, element2 ...}
//! Ne pas depasser la taille du tableau !!
//! Vous pouvez donner un tableau plus petit que la taille max mais c'est pas recommendé, c'est pour ca que j'ai mis des none


//génération des jetons science
JetonScience jetonAgriculture(CapaciteScience::agriculture);
JetonScience jetonArchitecture(CapaciteScience::architecture);
JetonScience jetonEconomie(CapaciteScience::economie);
JetonScience jetonLoi(CapaciteScience::loi);
JetonScience jetonMaconnerie(CapaciteScience::maconnerie);
JetonScience jetonUrbanisme(CapaciteScience::urbanisme);
JetonScience jetonTheologie(CapaciteScience::theologie);
JetonScience jetonStrategie(CapaciteScience::strategie);
JetonScience jetonPhilosophie(CapaciteScience::philosophie);
JetonScience jetonMathematique(CapaciteScience::mathematique);

//génération des joueurs
Joueur joueur1;
Joueur joueur2;

//génération des jetons malus
JetonMalus jetonMalus1(2, joueur1);
JetonMalus jetonMalus2(5, joueur1);
JetonMalus jetonMalus3(2, joueur2);
JetonMalus jetonMalus3(5, joueur2);