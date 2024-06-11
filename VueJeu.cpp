#include "VueJeu.h"
#include <QPainter>
#include <QApplication>
#include <QScreen>
#include <QSize>
#include <iostream>
#include <string>
#include "Carte.h"
#include "Joueur.h"
#include "Plateau.h"
#include "controleur.h"
#include "const_and_enum.h"
#include "VueCarte.h"


using namespace std;

const unsigned int NB_CHOIX_MERVEILLE = 4;

VueJeu::VueJeu(QWidget *parent) : QWidget(parent) {

    setWindowTitle("7 Wonders");
    resize(1600,800);
    background = QPixmap(":/images/back.jpeg");
    plateau_militaire = QPixmap(":/images/plateau_militaire.png");




    coucheMP = new QVBoxLayout(this);

    coucheMP->setSpacing(20);


    setLayout(coucheMP);
    //connect(getBoutonDemarrer(), &QPushButton::clicked, this, &VueMENU::BoutonDemarrer);


    std::cout << "Bienvenue dans Seven Wonders Duel!" << std::endl;
    Controleur* jeu =  &Controleur::getInstance();
    //!CHOIX DES MERVEILLES
    QList<Merveille*> cards;
 /*  Merveille** merveille = jeu->getPlateau().getPlateauCartes()->getMerveilles(); //recuperation des merveilles
    Merveille** merveilles_etape_1 = new Merveille*[NB_CHOIX_MERVEILLE]; //creation du premier lot de 4 merveilles
    for (int i = 0; i < NB_CHOIX_MERVEILLE; i++){
        cout<<merveille[i]->getNom()<<endl;
        merveilles_etape_1[i] = merveille[i];
    }*/
    Merveille *mer = new Merveille({RessourcePrimaire::none, RessourcePrimaire::none,
                                RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::detruire_carte_grise, Capacite::none, Capacite::none},
                               3, 1, false, "LeCircusMaximus", 1, 0, {RessourcePrimaire::pierre, RessourcePrimaire::pierre, RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none},
                                                      {RessourceSecondaire::verre, RessourceSecondaire::none, RessourceSecondaire::none} );
    Merveille *mer2 = new Merveille({RessourcePrimaire::none, RessourcePrimaire::none,
                                               RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::choisir_jeton_science,
                                               Capacite::none, Capacite::none}, 4, 0, false, "LaGrandeBibliotheque", 1, 0, {RessourcePrimaire::bois,
                                               RessourcePrimaire::bois, RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::parchemin, RessourceSecondaire::none} );

Merveille *mer3 = new Merveille({RessourcePrimaire::none, RessourcePrimaire::none,
                   RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::jouer_carte_defausse,
                   Capacite::none, Capacite::none}, 2, 0, false, "LeMausolee", 1, 0, {RessourcePrimaire::brique,
                   RessourcePrimaire::brique, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::verre, RessourceSecondaire::parchemin});

    cards.append(mer);
    cards.append(mer2);
    cards.append(mer3);



/*
    cards.append(Merveille({RessourcePrimaire::bois, RessourcePrimaire::pierre,
               RessourcePrimaire::brique}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::none, Capacite::none, Capacite::none},
              4, 0, true, "LeGrandPhare", 1, 0, {RessourcePrimaire::pierre, RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none},
                           {RessourceSecondaire::parchemin, RessourceSecondaire::parchemin, RessourceSecondaire::none} ));

    cards.append(Merveille({RessourcePrimaire::none, RessourcePrimaire::none,
                   RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::choisir_jeton_science,
                   Capacite::none, Capacite::none}, 4, 0, false, "LaGrandeBibliotheque", 1, 0, {RessourcePrimaire::bois,
                   RessourcePrimaire::bois, RessourcePrimaire::bois, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::parchemin, RessourceSecondaire::none} ));


    cards.append(Merveille({RessourcePrimaire::none, RessourcePrimaire::none,
                   RessourcePrimaire::none}, {RessourceSecondaire::none, RessourceSecondaire::none}, {Capacite::jouer_carte_defausse,
                   Capacite::none, Capacite::none}, 2, 0, false, "LeMausolee", 1, 0, {RessourcePrimaire::brique,
                   RessourcePrimaire::brique, RessourcePrimaire::none, RessourcePrimaire::none, RessourcePrimaire::none}, {RessourceSecondaire::verre, RessourceSecondaire::verre, RessourceSecondaire::parchemin}));


*/

   for ( Merveille* card : cards) {
        CardWidget *cardWidget = new CardWidget(card);
        coucheMP->addWidget(cardWidget, 0, Qt::AlignCenter);


    }





    std::cout<<"A vous de choisir deux merveilles dans le premier lot !" <<endl;
    //choix des merveilles pour le 1er lot de 4 merveilles


}


int VueJeu::SevenWondersDuel(Controleur& controleur, Joueur* joueur_actif){ //le 1er joueur donnée en argument est le joueur qui joue
    std::cout << "debut de SevenWondersDuel" << std::endl; //!teste
    //** VERIFICATION DE LA VICTOIRE D'UN DES JOUEURS **//
    if (controleur.jeuEstFinie()) { //OK
        return controleur.gagnant(); //OK
    } //!condition d'arret de la fonction recursive SevenWondersDuel

    controleur.addTour(); //OK
    //** CHOIX D'UNE ACTION POUR LE JOUEUR ACTIF **//
    Action* actions_legales = controleur.actionsLegales();
    bool boucle = true;
    while (boucle) {
        Action action = joueur_actif->choisir_action(actions_legales);
        std::cout<< "boucle du jeu: action est choisie!" << std::endl; //!test
        if (controleur.actionEstLegale(action)){
            controleur.playAction(action);
            std::cout<< "boucle du jeu: action est exécutée!" << std::endl; //!test
            boucle = false;
        }
        else{
            cout << "Action illégale, veuillez choisir une action legale" << endl;
        }
    } //!While True tant que le joueur n'as pas choisir une action légale
    //free(actions_legales);

    //** VERIFICATION DE LA FIN DE L'AGE **//
    if (controleur.getPlateau().getPlateauCartes()->estVide()){
        //changement d'age
        controleur.getPlateau().getPlateauCartes()->addAge();
        return SevenWondersDuel(controleur, controleur.getPlateau().getPlateauMilitaire()->getJoueurDerriere());
    }
    else{
        //** PASSAGE AU TOUR SUIVANT **//
        if (joueur_actif->getRejouer() == true){ //gestion du second tour de jeu en cas de Rejouer == TRUE
            joueur_actif->setRejouerFalse();
            return SevenWondersDuel(controleur, joueur_actif); //le joueur rejoue

        }
        else{
            if(joueur_actif == controleur.getJoueur1()){ //changement de joueur actif
                return SevenWondersDuel(controleur, controleur.getJoueur2());
            }
            else{
                return SevenWondersDuel(controleur, controleur.getJoueur1());
            }
        }
    }
}

void VueJeu::choix_merveille(Controleur* jeu, Merveille** merveilles, int joueur){
    if (joueur == 1){
        Joueur* joueur1 = jeu->getJoueur1();
        Merveille* choix = joueur1->choisirCarte(merveilles, 4);
        joueur1->setMerveille(choix);
        bool found = false;
        for(int i = 0; i < NB_CHOIX_MERVEILLE; i++){
            if (merveilles[i] == choix){
                merveilles[i] = nullptr;
            }

        } //supression de la merveille de la liste donnée en argument
    }

    else{
        Joueur* joueur2 = jeu->getJoueur2();
        Merveille* choix = joueur2->choisirCarte(merveilles, 4);
        joueur2->setMerveille(choix);
        for(int i = 0; i < NB_CHOIX_MERVEILLE; i++){
            if (merveilles[i] == choix){
                merveilles[i] = nullptr;
            }
        }
    }
}



void VueJeu::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.drawPixmap(0, 0, width(), height(), background);
    int xPos = 1200;
    int yPos = 250;

    QTransform transform;
    transform.translate(xPos + plateau_militaire.width() / 2, yPos + plateau_militaire.height() / 2);
    transform.rotate(90);
    transform.translate(-(xPos + plateau_militaire.width() / 2), -(yPos + plateau_militaire.height() / 2));

    painter.setTransform(transform);
    painter.drawPixmap(xPos, yPos, plateau_militaire);



}



