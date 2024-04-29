
#include <iostream>
#include <string>
#include "Joueur.h"
#include "Plateau.h"

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
JetonMalus jetonMalus3(2, joueur3);
JetonMalus jetonMalus3(5, joueur3);