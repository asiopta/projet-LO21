#include <QtWidgets>
#include <iostream>
#include <string>
#include "VueMenu.h"




/*-------------------------------------CONSTANTES DE L'ENVIRONEMENT-------------------------------------*/
const unsigned int Taille_cout_primaire = 3;
const unsigned int Taille_cout_secondaire = 2;
const unsigned int Taille_prod_primaire = 3;
const unsigned int Taille_prod_secondaire = 2;
const unsigned int Taille_capacite = 3;

enum class RessourcePrimaire {
    none,
    pierre,
    bois,
    brique
};


enum class RessourceSecondaire {
    none,
    verre,
    parchemin
};


enum class SymboleChainage{
    none,
    jarre,
    toneau,
    masque,
    temple,
    soleil,
    goute,
    lune,
    pilier,
    cible,
    casque,
    fer_a_cheval,
    epee,
    tour,
    lyre,
    engrenage,
    livre,
    lampe
};


enum class SymboleScience{
    roue,
    plume,
    pilon,
    balance,
    globe_terrestre,
    fil_a_plomb,
    bateau,
};


enum class EffetGuilde{
    guilde_armateurs,
    guilde_batisseurs,
    guilde_commercants,
    guilde_magistrats,
    guilde_tacticiens,
    guilde_scientifiques,
    guilde_usuriers
};


enum class Capacite{
    none,
    rejouer,
    detruire_carte_marron,
    detruire_carte_grise,
    jouer_carte_defausse,
    gagner_monnaie,
    avancee_militaire,
    choisir_jeton_science,
    ajouter_symbole_science
};


class Card {


private:
    std::string nom;
    unsigned int age;
    unsigned int cout_construction;
    RessourcePrimaire* materiaux_construction_primaires;
    RessourceSecondaire* materiaux_construction_secondaires;
    bool accessible;
    bool face_visible;
    unsigned int position;
    QString mImagePath;


public:


    Card(std::string n,unsigned int a, unsigned int cout,const QString &imagePath): nom(n),age(a),cout_construction(cout),mImagePath(imagePath) {}
    std::string getnom() const {return nom;}

    QString imagePath() const { return mImagePath; }


};

class CardWidget : public QWidget {


public:
    CardWidget(const Card& card, QWidget *parent = nullptr) : QWidget(parent), mCard(card) {
        setFixedSize(100, 150); // Set fixed size for each card widget
    }

protected:

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            qDebug() << mCard.getnom();        }
    }

    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Draw card background
        QRectF cardRect(0, 0, width(), height());
        painter.setBrush(Qt::white);
        painter.drawRoundedRect(cardRect, 10, 10);

        // Draw card image
        QPixmap pixmap(mCard.imagePath());
        if (!pixmap.isNull()) {
            painter.drawPixmap(cardRect, pixmap, pixmap.rect());
        }

        // Draw card name
        painter.setPen(Qt::black);
        QFont font("Arial", 10);
        painter.setFont(font);
        //painter.drawText(cardRect, Qt::AlignCenter, mCard.name());
    }

private:
    Card mCard;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


   /* QWidget window;
    window.setWindowTitle("Exemple liste de cartes");
    window.resize(1200,600);

    QVBoxLayout layout(&window);

    QList<Card> cards;



    cards.append(Card("Scierie",2,3,":/images/card_test.jpeg"));
    cards.append(Card("Google",2,3,":/images/test1.png"));




    for (const Card &card : cards) {
        CardWidget *cardWidget = new CardWidget(card);
        layout.addWidget(cardWidget, 0, Qt::AlignCenter);


    }

    window.setLayout(&layout);*/
    VueMENU menu = VueMENU(nullptr, &app);
    menu.show();
    return app.exec();
}


