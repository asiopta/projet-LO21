#ifndef VUEMENU_H
#define VUEMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class VueMENU : public QWidget {
    Q_OBJECT
private:
    QPushButton *boutonDemarrer;
    QPushButton *boutonSauvegarde;
    QPushButton *boutonBibli;
    QPushButton *boutonQuitter;

    QVBoxLayout *coucheMP;
protected:
    void paintEvent(QPaintEvent *event);

public:
    VueMENU(QWidget *parent,QApplication* app);
    ~VueMENU();
    QPushButton* getBoutonQuitter() const { return boutonQuitter; }
    QPushButton* getBoutonSauvegarde() const { return boutonSauvegarde; }
    QPushButton* getBoutonBibli() const { return boutonBibli; }
    QPushButton* getBoutonDemarrer() const { return boutonDemarrer; }

public slots:
    void BoutonDemarrer();
};



#endif // VUEMENU_H
