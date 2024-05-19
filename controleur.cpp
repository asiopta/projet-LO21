#include "Joueur.h"
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include "controleur.h"



/*-------------------------------------Plateau-------------------------------------*/


Plateau::Plateau(Joueur& joueur1, Joueur& joueur2){
    plateau_cartes = new PlateauCartes();
    plateau_science = new PlateauScience();
    plateau_militaire = new PlateauMilitaire(0, joueur1, joueur2);
}

Plateau::~Plateau(){
    delete plateau_cartes;
    delete plateau_science;
    delete plateau_militaire;
}
bool Controleur::gagne(Joueur& joueur){
    bool victoireMilitaire = plateau.getPlateauMilitaire()->gagneMilitairement(joueur);
    bool victoireScience = 0 ;
    return victoireMilitaire || victoireScience;
}


bool Controleur::jeuEstFinie(){
    return plateau.isEtatFinal() || gagne(joueur1) || gagne(joueur2);
}


//méthodes utiles
Joueur& Controleur::quiJoue(){
    if(tour == 1) return joueur1;
    if(tour == 2) return joueur2;
    else SetException("erreur: joueur non reconnu!");
}


 bool Controleur::jeuEstFinie(){
    return (plateau.isEtatFinal() || joueur1.gagneScientifiquement() || joueur2.gagneScientifiquement() ||
        plateau.getPlateauMilitaire()->gagneMilitairement(joueur1) || plateau.getPlateauMilitaire()->gagneMilitairement(joueur2));

 }


 unsigned int Controleur::gagnant(){
    if(jeuEstFinie() == false) SetException("erreur: jeu pas fini"); return 0;

    if(joueur1.gagneScientifiquement() || plateau.getPlateauMilitaire()->gagneMilitairement(joueur1)) return 1;
    if(joueur2.gagneScientifiquement() || plateau.getPlateauMilitaire()->gagneMilitairement(joueur2)) return 2;
    else{
        if(joueur1.getPtVictoire() > joueur2.getPtVictoire()) return 1;
        else return 2;
    }

 }

Joueur& Controleur::autreJoueur(Joueur& j){
    if(j == joueur1) return joueur2;
    if(j == joueur2) return joueur1;
    else SetException("erreur: joueur non reconnu");
}



 void Controleur::contruireCarte(Carte* carte){
    //si la carte est accessible
    if(plateau.getPlateauCartes()->estAccessible(carte)){
        //niveau ressources joueur
        Joueur& j = quiJoue();
        int diff = j.getMonnaie() - j.getCout(*carte, autreJoueur(j));
        if(diff < 0) SetException(" erreur: joueur n'a pas assez d'argent et de ressources");
        j.setMonnaie(diff);

        //rajouter la carte aux cartes_construites de joueur et l'enlever du plateau
        j.addCarte(carte);
        plateau.getPlateauCartes()->defausserCarte(carte); //si c'est carteScience ou CarteRessource ou Prestige ou CarteGuilde c bon
        // leurs effets se fait au niveau de classe Joueur

        //si c'est une carteMilitaire
        if(carte->get_type() == TypeCarte::CarteMilitaire){
            CarteMilitaire* carte_militaire = dynamic_cast<CarteMilitaire*>(carte);
            carte_militaire->exec_capacite(j, *plateau.getPlateauMilitaire());
        }

        //si c'est une merveille
        if(carte->get_type() == TypeCarte::CarteMilitaire){
            Merveille* merveille = dynamic_cast<Merveille*>(carte);
            merveille->exec_capacite(joueur1, joueur2, *plateau.getPlateauCartes(), *plateau.getPlateauMilitaire(), *plateau.getPlateauScience());
            
        }
    }
    else SetException("erreur: carte non accessible!");
 }
