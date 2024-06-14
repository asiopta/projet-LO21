
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include "controleur.h"




/*---------------------classe Controleur-----------------------------------*/
Controleur::Controleur(): joueur1(new Joueur()), joueur2(new Joueur()), plateau(Plateau(joueur1, joueur2)){
    // std::cout << "Ici Controleur::Controleur() : construction du controleur pour cette partie" << std::endl; //!test
    // plateau = Plateau(joueur1, joueur2);
    // std:: cout <<"Constructeur Controleur: joueur1: "<< joueur1 << " /joueur2: " << joueur2 << std::endl;

    // std::cout << "Ici Controleur::Controleur : fin de la construction" << std::endl ;//! test
}

Controleur::Controleur(std::string player):joueur1(new Joueur()), joueur2(new IARandom()), plateau(Plateau(joueur1, joueur2)){

}


bool Controleur::gagne(Joueur* joueur){
    bool victoireMilitaire = plateau.getPlateauMilitaire()->gagneMilitairement(joueur); 
    bool victoireScience = joueur1->gagneScientifiquement(); 
    // std::cout<< "victoire militaire:"<<victoireMilitaire << " victoire science:" << victoireScience << std::endl; //!test
    return victoireMilitaire || victoireScience;
}


bool Controleur::jeuEstFinie(){
    // std::cout<< "plateau etat final:"<<plateau.isEtatFinal()<< std::endl; //!test
    // std::cout<< " j1 GAGNE:" << gagne(joueur1)  << std::endl; //!test
    // std::cout<< " j2 GAGNE:" << gagne(joueur2)  << std::endl; //!test
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

Controleur& Controleur::getInstance(const std::string p){
    if(handler.instance == nullptr) handler.instance = new Controleur("IA");
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
    if(jeuEstFinie() == false) throw SetException("erreur: jeu pas fini"); return 0;

    if(joueur1->gagneScientifiquement() || plateau.getPlateauMilitaire()->gagneMilitairement(joueur1)) return 1;
    if(joueur2->gagneScientifiquement() || plateau.getPlateauMilitaire()->gagneMilitairement(joueur2)) return 2;
    else{
        if(joueur1->getPtVictoire() > joueur2->getPtVictoire()) return 1;
        else return 2;
    }

 }

Joueur* Controleur::autreJoueur(Joueur* j){
    // std::cout<< "autreJoueur?" << std::endl; //! test
    // std::cout<< "autreJoueur: " << j<<std::endl; //! test
    if(j == joueur1){
        // std::cout<< "c'est joueur 2" << std::endl; //! test
        return joueur2;
    }
    if(j == joueur2){
        // std::cout<< "c'est joueur 1" << std::endl; //! test
        return joueur1;
    }
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
    if(carte->get_type() == TypeCarte::Merveille){
        Joueur* j = quiJoue();
        int diff = j->getMonnaie() - j->getCout(*carte, *autreJoueur(j));
        if(diff < 0) throw SetException(" erreur: joueur n'a pas assez d'argent et de ressources");
        // std::cout<< "argent joueur avant: "<< j->getMonnaie() << std::endl; //!test
        j->setMonnaie(diff);
        // std::cout<< "argent joueur apres: "<< j->getMonnaie() << std::endl; //!test

        j->addCarte(carte, plateau.getPlateauScience());

        Merveille* merveille = dynamic_cast<Merveille*>(carte);
        plateau.getPlateauCartes()->prendreMerveille(merveille);

        merveille->exec_capacite(quiJoue(), autreJoueur(quiJoue()), *plateau.getPlateauCartes(), *plateau.getPlateauMilitaire(), *plateau.getPlateauScience()); 
        //* erreur corrigée

    }
    else{
        if(plateau.getPlateauCartes()->estAccessible(carte)){
            //niveau argent joueur
            Joueur* j = quiJoue();
            int diff = j->getMonnaie() - j->getCout(*carte, *autreJoueur(j));
            if(diff < 0) throw SetException(" erreur: joueur n'a pas assez d'argent et de ressources");
            // std::cout<< "argent joueur avant construire: "<< j->getMonnaie() << std::endl; //!test
            j->setMonnaie(diff);
            // std::cout<< "argent joueur apres construire: "<< j->getMonnaie() << std::endl; //!test
            //rajouter la carte aux cartes_construites de joueur et l'enlever du plateau
            j->addCarte(carte, plateau.getPlateauScience());
            plateau.getPlateauCartes()->prendreCarte(carte); //si c'est carteScience ou CarteRessource ou Prestige ou CarteGuilde c bon
            // leurs effets se fait au niveau de classe Joueur

            //si c'est une carteMilitaire
            if(carte->get_type() == TypeCarte::CarteMilitaire){
                CarteMilitaire* carte_militaire = dynamic_cast<CarteMilitaire*>(carte);
                carte_militaire->exec_capacite(autreJoueur(j), *plateau.getPlateauMilitaire()); //* erreur corrigée
            }

            if(carte->get_type() == TypeCarte::CarteCommerce){
                CarteCommerce* carte_commerce = dynamic_cast<CarteCommerce*>(carte);
                //carte_commerce->exec_capacite(*j); //! exec_capacite à DEFINIR
            }
        }
        else SetException("erreur: carte non accessible!");
    }
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
        // std::cout<< "argent joueur avant defausser: "<< j->getMonnaie() << std::endl; //!test
        // std::cout<< "cout carte: "<< j->getCout(*carte, *autreJoueur(j))<< std::endl; //!test
        unsigned int cout_defauss = 2;
        cout_defauss += j->getNbCartesType("RessourcePrimaire");
        cout_defauss += j->getNbCartesType("RessourceSecondaire");
        j->gagnerArgent(cout_defauss);
        // std::cout<< "argent joueur apres defausser: "<< j->getMonnaie() << std::endl; //!test

        //rajouter la carte aux cartes_construites de joueur et l'enlever du plateau
        if(carte->get_type() == TypeCarte::Merveille) throw SetException("erreur: impossible de défausser une merveille");
        else{
            plateau.getPlateauCartes()->prendreCarte(carte); 
            plateau.getPlateauCartes()->defausserCarte(carte);
            return;
        }

    }
    else throw SetException("erreur: carte non accessible!");
}


void Controleur::playAction(Action& action){
    Carte* carte = std::get<0>(action);
    if(carte->get_type() == TypeCarte::Merveille){
        construireCarte(carte);
        return;
    } 
    else{
        if(plateau.getPlateauCartes()->estAccessible(carte)){
            if(std::get<1>(action) == "defausser"){
                defausserCarte(carte);
                return;
            }
            if(std::get<1>(action) == "construire"){
                construireCarte(carte);
                return;
            }

            else 
                throw SetException("erreur: action non reconnue;");
        }
        else throw SetException("erreur: carte non acessible");
    }
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
    Action* res = new Action[60];
    int j = 0;
    for(int i= 0; i<TAILLE_CARTE_EN_JEU-1; i++){
        Carte* carte= plateau.getPlateauCartes()->getCartesEnJeu()[i];
        if(carte != nullptr){
            if(carte->est_accessible()){
                if(estConstructible(carte)){
                    
                    res[j] = std::make_tuple( carte , "construire");
                    j++;
                }

                res[j] = std::make_tuple( carte , "defausser");
                j++;

            }
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


    for(j; j<60; j++) {res[j] = std::make_tuple( nullptr , "ignore");}
    return res;
}

Joueur* Controleur::determineGagnant(){

    //! point  de victoires provenant des cartes 
    unsigned int pt_vict_1 = joueur1->getPtVictoire(); //points de victoires provenant des cartes 
    unsigned int pt_vict_2 = joueur2->getPtVictoire();

    //! points de victoires provenant du militaire
    unsigned int avance = plateau.getPlateauMilitaire()->getAvance();
    Joueur* joueur_derriere = plateau.getPlateauMilitaire()->getJoueurDerriere();

    if (avance >= 1 and avance < 3) {
        if (joueur_derriere == joueur1) {pt_vict_2 += 2;}
        else {pt_vict_1 += 2;}
    }
    else if (avance >= 3 and avance < 6) {
        if (joueur_derriere == joueur1) {pt_vict_2 += 5;}
        else {pt_vict_1 += 5;}
    }
    else if (avance >= 6) {
        if (joueur_derriere == joueur1) {pt_vict_2 += 10;}
        else {pt_vict_1 += 10;}
    }

    //!point de victoire des pièces de monnaie
    unsigned int monnaie = joueur1->getMonnaie();
    monnaie = monnaie / 3;
    pt_vict_1 += monnaie;
    monnaie = joueur2->getMonnaie();
    monnaie = monnaie / 3;
    pt_vict_2 += monnaie;

    //!point de victoire des effets de cartes guildes : 
    unsigned int nb_max_Armateurs = std::max(joueur1->getNbCartesType("CarteRessourcePrimaire")+joueur1->getNbCartesType("CarteRessourceSecondaire"), joueur2->getNbCartesType("CarteRessourcePrimaire")+joueur2->getNbCartesType("CarteRessourceSecondaire"));
    unsigned int nb_max_Batisseurs = std::max(2*joueur1->getNbCartesType("CarteMerveille"), 2*joueur2->getNbCartesType("CarteMerveille"));
    unsigned int nb_max_Commercant = std::max(joueur1->getNbCartesType("CarteCommerce"), joueur2->getNbCartesType("CarteCommerce"));
    unsigned int nb_max_Magistrat = std::max(joueur1->getNbCartesType("CartePrestige"), joueur2->getNbCartesType("CartePrestige"));
    unsigned int nb_max_Tacticiens = std::max(joueur1->getNbCartesType("CarteMilitaire"), joueur2->getNbCartesType("CarteMilitaire"));
    unsigned int nb_max_Scientifiques = std::max(joueur1->getNbCartesType("CarteScience"), joueur2->getNbCartesType("CarteScience"));
    unsigned int nb_max_Usuriers = std::max(joueur1->getMonnaie(), joueur2->getMonnaie());

    if(joueur1->getEffetsGuilde().guilde_armateurs){pt_vict_1 = nb_max_Armateurs;}
    if(joueur1->getEffetsGuilde().guilde_batisseurs){pt_vict_1 += nb_max_Batisseurs;}
    if(joueur1->getEffetsGuilde().guilde_commercants){pt_vict_1 += nb_max_Commercant;}
    if(joueur1->getEffetsGuilde().guilde_magistrats){pt_vict_1 += nb_max_Magistrat;}
    if(joueur1->getEffetsGuilde().guilde_tacticiens){pt_vict_1 += nb_max_Tacticiens;}
    if(joueur1->getEffetsGuilde().guilde_scientifiques){pt_vict_1 += nb_max_Scientifiques;}
    if(joueur1->getEffetsGuilde().guilde_usuriers){pt_vict_1 += nb_max_Usuriers;}

    if(joueur2->getEffetsGuilde().guilde_armateurs){pt_vict_2 = nb_max_Armateurs;}
    if(joueur2->getEffetsGuilde().guilde_batisseurs){pt_vict_2 += nb_max_Batisseurs;}
    if(joueur2->getEffetsGuilde().guilde_commercants){pt_vict_2 += nb_max_Commercant;}
    if(joueur2->getEffetsGuilde().guilde_magistrats){pt_vict_2 += nb_max_Magistrat;}
    if(joueur2->getEffetsGuilde().guilde_tacticiens){pt_vict_2 += nb_max_Tacticiens;}
    if(joueur2->getEffetsGuilde().guilde_scientifiques){pt_vict_2 += nb_max_Scientifiques;}
    if(joueur2->getEffetsGuilde().guilde_usuriers){pt_vict_2 += nb_max_Usuriers;}

    std::cout << "Point de victoire du joueur 1 : " << pt_vict_1 << std::endl;
    std::cout << "Point de victoire du joueur 2 : " << pt_vict_2 << std::endl;

    if (pt_vict_1 > pt_vict_2) {return joueur1;}
    else if (pt_vict_1 < pt_vict_2) {return joueur2;}
    else {
        if (joueur1->getNbCartesType("CartePrestige")> joueur2->getNbCartesType("CartePrestige")){
            return joueur1;
        }
        else if (joueur1->getNbCartesType("CartePrestige")< joueur2->getNbCartesType("CartePrestige")){
            return joueur2;
        }
        else {
            return nullptr;
        }
    }
}

Controleur::~Controleur(){
    delete joueur1;
    delete joueur2;
    // delete &plateau; 
    //! changment à venir : modif le plateau en Plateau* plateau dans Controleur car je pense que l'erreur d'allocation memoir vient de la. 
}



/*-------------------------------------Plateau-------------------------------------*/


Plateau::Plateau(Joueur* joueur1, Joueur* joueur2){
    // std:: cout <<"Constructeur Plateau: joueur1: "<< joueur1 << " /joueur2: " << joueur2 << std::endl;

    plateau_cartes = new PlateauCartes();
    plateau_cartes->addAge(); //! la fonction addage set a initialiser les cartes en jeu
    plateau_science = new PlateauScience();
    plateau_militaire = new PlateauMilitaire(0, joueur1, joueur2);
    // std:: cout <<"Constructeur Plateau: joueur1: "<< joueur1 << " /joueur2: " << joueur2 << std::endl;
}

Plateau::~Plateau(){
    delete plateau_cartes;
    delete plateau_science;
    delete plateau_militaire;
}

bool Plateau::isEtatFinal() {
    // std::cout << "plateau vide: "<<plateau_cartes->estVide()<< std::endl; //!teste
    // unsigned int age = plateau_cartes->getAge(); //!teste
    // std:: cout << "dernier age: "<< (age == 3); //!teste
    return (plateau_cartes->estVide() && plateau_cartes->getAge() == 3 );
        
}

void Controleur::showStatePlayer(Joueur* joueur){
    std::cout <<"*---------------------------------------------*"<<std::endl;
    std::cout <<"monnaie de joueur: "<< joueur->getMonnaie() <<std::endl;
    std::cout <<"cartes construites par le joueur: " <<std::endl;

    for(int i=0; i<60; i++){
        Carte* carte = joueur->getCartesConstruites()[i];
        if(carte!= nullptr){
            std::cout <<"(" << carte->get_type() << ") "<<carte->getNom() <<std::endl;
        }
    }
    std::cout <<"*---------------------------------------------*"<<std::endl;

}

void Controleur::showStatePlateauMilitaire(){
    std::cout<<"*-------------- Plateau Militaire------------*" << std::endl;
    std::cout<< "avancee militaire: " << plateau.getPlateauMilitaire()->getAvance() << std::endl;
    
    plateau.getPlateauMilitaire()->getJoueurDerriere();
    int der;
    if(plateau.getPlateauMilitaire()->getJoueurDerriere() == joueur1){
        der = 1;
    }
    else if(plateau.getPlateauMilitaire()->getJoueurDerriere() == joueur2){
        der = 2;
    }
    else throw SetException("joueur inconnue!");
    std::cout<< "joueur derriere: joueur" << der<<std::endl;
    std::cout <<"*---------------------------------------------*"<<std::endl;


}

void Controleur::showStatePlateauScience(){
    std::cout<<"*-------------- Plateau Science------------*" << std::endl;
    std::cout<< "jetons disponibles: " << std::endl;

    for(int i=0; i<5; i++){
        JetonScience* jeton = plateau.getPlateauScience()->getJetonInGame()[i];
        if(jeton!= nullptr){
            std::cout<< jeton->get_capacite() << std::endl;
        }
    }
    std::cout <<"*---------------------------------------------*"<<std::endl;


}

