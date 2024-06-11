#include "VueMenu.h"
#include "VueJeu.h"
#include <QPainter>



VueMENU::VueMENU(QWidget *parent,QApplication* app) : QWidget(parent) {

    setWindowTitle("Menu");
    resize(1200,600);
    boutonDemarrer = new QPushButton("Commencer une nouvelle partie");
    boutonSauvegarde = new QPushButton("Demarrer une partie sauvegardee");
    boutonBibli = new QPushButton("Scores");
    boutonQuitter = new QPushButton("Quitter");

    coucheMP = new QVBoxLayout(this);
    coucheMP->addWidget(boutonDemarrer);
    coucheMP->addWidget(boutonSauvegarde);
    coucheMP->addWidget(boutonBibli);
    coucheMP->addWidget(boutonQuitter);

    setLayout(coucheMP);
    connect(getBoutonDemarrer(), &QPushButton::clicked, this, &VueMENU::BoutonDemarrer);
}

VueMENU::~VueMENU() {
    delete boutonDemarrer;
    delete boutonSauvegarde;
    delete boutonBibli;
    delete boutonQuitter;
    delete coucheMP;
}

void VueMENU::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(QColor("#252525")); //On definie la couleur du pinceau en blanc

    painter.drawPolygon(rect()); //On colorie le polygone

}

void VueMENU::BoutonDemarrer() {
    VueJeu * jeu = new VueJeu(nullptr);
    jeu->show();
    this->hide();
    qDebug() << "test";
}

