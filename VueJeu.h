#ifndef VUEJEU_H
#define VUEJEU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>
#include <string>
#include "Carte.h"
#include "Joueur.h"
#include "Plateau.h"
#include "controleur.h"
#include "const_and_enum.h"

class VueJeu : public QWidget {
    Q_OBJECT
private:

    QPushButton *boutonSauvegarde;

    QPixmap background;
    QPixmap plateau_militaire;


    QVBoxLayout *coucheMP;
protected:
    void paintEvent(QPaintEvent *event);

public:
    VueJeu(QWidget *parent);


    QPushButton* getBoutonSauvegarde() const { return boutonSauvegarde; }


public slots:
    void choix_merveille(Controleur* jeu, Merveille** merveilles, int joueur);
    int SevenWondersDuel(Controleur& controleur, Joueur* joueur_actif);

};



#endif // VUEJEU_H
