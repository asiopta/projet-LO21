#ifndef VUECARTE_H
#define VUECARTE_H
#include <QtWidgets>
#include <iostream>
#include <string>
#include "Carte.h"




class CardWidget : public QWidget {


public:
    CardWidget(Merveille* Merveille, QWidget *parent = nullptr) : QWidget(parent), mCard(Merveille) {
        setFixedSize(100, 150); // Set fixed size for each card widget
    }

protected:

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            qDebug() << mCard->getNom();        }
    }

    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Draw card background
        QRectF cardRect(0, 0, width(), height());
        painter.setBrush(Qt::white);
        painter.drawRoundedRect(cardRect, 10, 10);

        // Draw card image
       /* QPixmap pixmap(mCard.imagePath());
        if (!pixmap.isNull()) {
            painter.drawPixmap(cardRect, pixmap, pixmap.rect());
        }*/

        // Draw card name
       /* painter.setPen(Qt::black);
        QFont font("Arial", 10);
        painter.setFont(font);
        painter.drawText(cardRect, Qt::AlignCenter, "test");*/
    }

private:
    Merveille* mCard;
};
#endif // VUECARTE_H
