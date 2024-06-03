
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include "controleur.h"




/*---------------------classe Controleur-----------------------------------*/
Controleur::Controleur(): plateau(Plateau(joueur1, joueur2)){
    std::cout << "Ici Controleur::Controleur() : construction du controleur pour cette partie" << std::endl;
    joueur1 = new Joueur();
    joueur2 = new Joueur();
    std::cout << "Ici Controleur::Controleur : fin de la construction" << std::endl ;//! test
}



bool Controleur::gagne(Joueur* joueur){
    bool victoireMilitaire = plateau.getPlateauMilitaire()->gagneMilitairement(joueur);
    bool victoireScience = joueur1->gagneScientifiquement();
    return victoireMilitaire || victoireScience;
}


bool Controleur::jeuEstFinie(){
    return plateau.isEtatFinal() || gagne(joueur1) || gagne(joueur2);
}

unsigned int Controleur::getTotalCartesAccessibles(){
    unsigned int res = plateau.getPlateauCartes()->getNbCartesAccessibles();
    res += quiJoue()->getNbMerveillesNonConstruites();
    return res;
}

//méthodes de handler
Controleur::Handler Controleur::handler = Handler(); 

Controleur& Controleur::getInstance(){
    if(handler.instance == nullptr) handler.instance = new Controleur;
    return *handler.instance;
}
void Controleur::libererInstance(){
    delete handler.instance;
    handler.instance = nullptr;
}

//méthodes utiles
Joueur* Controleur::quiJoue(){
    if(tour == 1) return joueur1;
    if(tour == 2) return joueur2;
    else throw SetException("erreur: joueur non reconnu!");
}




 unsigned int Controleur::gagnant(){
    if(jeuEstFinie() == false) SetException("erreur: jeu pas fini"); return 0;

    if(joueur1->gagneScientifiquement() || plateau.getPlateauMilitaire()->gagneMilitairement(joueur1)) return 1;
    if(joueur2->gagneScientifiquement() || plateau.getPlateauMilitaire()->gagneMilitairement(joueur2)) return 2;
    else{
        if(joueur1->getPtVictoire() > joueur2->getPtVictoire()) return 1;
        else return 2;
    }

 }

Joueur* Controleur::autreJoueur(Joueur* j){
    if(j == joueur1) return joueur2;
    if(j == joueur2) return joueur1;
    else throw SetException("erreur: joueur non reconnu");
}

bool Controleur::estConstructible(Carte* carte){
    Joueur* j = quiJoue();
    int diff = j->getMonnaie() - j->getCout(*carte, *autreJoueur(j));
    if(diff< 0) return false;
    else return true;
}


 void Controleur::construireCarte(Carte* carte){
    //si la carte est accessible
    if(plateau.getPlateauCartes()->estAccessible(carte)){
        //niveau argent joueur
        Joueur* j = quiJoue();
        int diff = j->getMonnaie() - j->getCout(*carte, *autreJoueur(j));
        if(diff < 0) SetException(" erreur: joueur n'a pas assez d'argent et de ressources");
        j->setMonnaie(diff);

        //rajouter la carte aux cartes_construites de joueur et l'enlever du plateau
        j->addCarte(carte, plateau.getPlateauScience());
        if(carte->get_type() == TypeCarte::Merveille) plateau.getPlateauCartes()->prendreMerveille(dynamic_cast<Merveille*>(carte));
        else plateau.getPlateauCartes()->prendreCarte(carte); //si c'est carteScience ou CarteRessource ou Prestige ou CarteGuilde c bon
        // leurs effets se fait au niveau de classe Joueur

        //si c'est une carteMilitaire
        if(carte->get_type() == TypeCarte::CarteMilitaire){
            CarteMilitaire* carte_militaire = dynamic_cast<CarteMilitaire*>(carte);
            carte_militaire->exec_capacite(j, *plateau.getPlateauMilitaire());
        }

        //si c'est une merveille
        if(carte->get_type() == TypeCarte::Merveille){
            Merveille* merveille = dynamic_cast<Merveille*>(carte);
            merveille->exec_capacite(joueur1, joueur2, *plateau.getPlateauCartes(), *plateau.getPlateauMilitaire(), *plateau.getPlateauScience());

        }
    }
    else SetException("erreur: carte non accessible!");
 }


void Controleur::addTour() {
    if(tour == 1){
        if(joueur1->getRejouer()) return ;
        else{
            tour = 2;
            return;
        }
    } 
    if(tour==2){
        if(joueur2->getRejouer()) return;
        else{
            tour = 1;
            return;
        }
    }
};


void Controleur::defausserCarte(Carte* carte){
    if(plateau.getPlateauCartes()->estAccessible(carte)){

        //niveau argent joueur
        Joueur* j = quiJoue();
        j->setMonnaie(j->getMonnaie() + j->getCout(*carte, *autreJoueur(j)));

        //rajouter la carte aux cartes_construites de joueur et l'enlever du plateau
        if(carte->get_type() == TypeCarte::Merveille) SetException("erreur: impossible de défausser une merveille");
        else{
            plateau.getPlateauCartes()->prendreCarte(carte); 
            plateau.getPlateauCartes()->defausserCarte(carte);
        }

    }
    else SetException("erreur: carte non accessible!");
}

void Controleur::playAction(Action& action){
    Carte* carte = std::get<0>(action);
    if(plateau.getPlateauCartes()->estAccessible(carte)){
        if(std::get<1>(action) == "defausser")
            defausserCarte(carte);

        if(std::get<1>(action) == "construire")
            construireCarte(carte);

        else 
            throw SetException("erreur: action non reconnue;");
    }
    else throw SetException("erreur: carte non acessible");
}

bool Controleur::actionEstLegale(Action& action){
    Carte* carte = std::get<0>(action);
    if(plateau.getPlateauCartes()->estAccessible(carte)){
        if(std::get<1>(action) == "defausser")
            return true;

        if(std::get<1>(action) == "construire")
            return estConstructible(carte);

        else 
            throw SetException("erreur: action non reconnue;");
    }
    if(carte->get_type() == TypeCarte::Merveille){
        if(std::get<1>(action) == "construire"){
            Merveille* merveille = dynamic_cast<Merveille*>(carte);
            return quiJoue()->isInMerveillesNonConstruites(merveille) && estConstructible(carte);
        }
        else return false;
    }
    else return false;
}


Action* Controleur::actionsLegales(){
    std::cout << "Ici Controleur::actionsLegales() : initialisation des actions légales" << std::endl; //!teste
    Action* res = new Action[60];
    int j = 0;
    for(int i= 0; i<TAILLE_CARTE_EN_JEU; i++){
        Carte* carte= plateau.getPlateauCartes()->getCartesEnJeu()[i];
        std::cout << "Nom : " << carte->getNom() << std::endl; //!teste
        std::cout << "Ici Controleur::actionsLegales() : carte en jeu" << std::endl; //!teste
        if(carte->est_accessible()){
            std::cout << "Ici Controleur::actionsLegales() : carte accessible" << std::endl; //!teste
            if(estConstructible(carte)){
                std::cout << "Ici Controleur::actionsLegales() : carte constructible" << std::endl; //!teste
                
                res[j] = std::make_tuple( carte , "construire");
                j++;
                std::cout << "J" << j << std::endl; //!teste
            }
            res[j] = std::make_tuple( carte , "defausser");
            j++;
            std::cout << "J" << j << std::endl; //!teste

        }
    }
    //merveilles
    Joueur* joueur = quiJoue();
    Merveille** liste = joueur->getMerveillesNonConstruites();
    for(int i =0; i<joueur->getNbMerveillesNonConstruites(); i++){
        if(estConstructible(liste[i])){
            res[j] = std::make_tuple(liste[i], "construire");
            j++;
        }
    }


    for(j; j<=60; j++) {res[j] = std::make_tuple( nullptr , "ignore");}
    return res;
}

Controleur::~Controleur(){
    delete joueur1;
    delete joueur2;
    // delete &plateau; 
    //! changment à venir : modif le plateau en Plateau* plateau dans Controleur car je pense que l'erreur d'allocation memoir vient de la. 
}




/*-------------------------------------Plateau-------------------------------------*/


Plateau::Plateau(Joueur* joueur1, Joueur* joueur2){
    plateau_cartes = new PlateauCartes();
    plateau_cartes->addAge(); //! la fonction addage set a initialiser les cartes en jeu
    plateau_science = new PlateauScience();
    plateau_militaire = new PlateauMilitaire(0, joueur1, joueur2);
}

Plateau::~Plateau(){
    delete plateau_cartes;
    delete plateau_science;
    delete plateau_militaire;
}

bool Plateau::isEtatFinal() {
    return (plateau_cartes->estVide() && plateau_cartes->getAge() == 3 );
        
}



