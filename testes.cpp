
#include <iostream>
#include <string>
#include "Carte.h"
#include "Joueur.h"
#include "Plateau.h"
#include "controleur.h"
#include "const_and_enum.h"

using namespace std;

int main(){
    Controleur* jeu =  &Controleur::getInstance();// initialisation du jeu via le controleur
    Merveille** merveille = jeu->getPlateau().getPlateauCartes()->getMerveilles(); //recuperation des merveilles
    Carte** cartes = jeu->getPlateau().getPlateauCartes()->getCartesEnJeu(); //recuperation des cartes en jeu
    for (unsigned int i=0; i<8; i++){
        cout << "Merveille: " << merveille[i]->getNom() << endl;
    }
    for (unsigned int i=0; i<20; i++){
        cout << "Carte: " << cartes[i]->getNom() << endl;
    }
    for(unsigned int i=0; i<10; i++){
        if (merveille[i]->getNom() == "LeMausolee"){
            jeu->getJoueur1()->setMonnaie(1000);
            cout << "Mausolee trouve" << endl;
            Carte* carte_a_defauser = cartes[0];
            // Carte* carte_a_defauser2 = jeu->getPlateau().getPlateauCartes()->getCartesEnJeu()[1];
            // Carte* carte_a_defauser3 = jeu->getPlateau().getPlateauCartes()->getCartesEnJeu()[2];
            cout << "Carte a defausser: " << carte_a_defauser->getNom() << endl;
            // cout << "Carte a defausser: " << carte_a_defauser2->getNom() << endl;
            // cout << "Carte a defausser: " << carte_a_defauser3->getNom() << endl;
            jeu->getPlateau().getPlateauCartes()->defausserCarte(carte_a_defauser);
            // jeu->getPlateau().getPlateauCartes()->defausserCarte(carte_a_defauser2);
            // jeu->getPlateau().getPlateauCartes()->defausserCarte(carte_a_defauser3);

            cout << "Carte defaussee" << endl;
            jeu->construireCarte(merveille[i]);
            cout << "Mausolee construit" << endl;

            cout << "Carte construite 1: " << jeu->getJoueur1()->getCartesConstruites()[0]->getNom();
            cout << "Carte construite 2: " << jeu->getJoueur1()->getCartesConstruites()[1]->getNom();
            cout << "Carte construite 3: " << jeu->getJoueur1()->getCartesConstruites()[2]->getNom();
            cout << "Carte construite 4: " << jeu->getJoueur1()->getCartesConstruites()[3]->getNom();

        }
    }
    return 0;
}