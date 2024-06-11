#include "vuecarte.h"
#include "ui_vuecarte.h"

VueCarte::VueCarte(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VueCarte)
{
    ui->setupUi(this);
}

VueCarte::~VueCarte()
{
    delete ui;
}
