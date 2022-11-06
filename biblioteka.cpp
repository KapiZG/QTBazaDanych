#include "biblioteka.h"
#include "ui_biblioteka.h"

Biblioteka::Biblioteka(const QString *a, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Biblioteka)
{
    ui->setupUi(this);

    user = a;
    QString b = "Witaj z powrotem: " + *a;
    ui->NazwaUzytkownika->setText(b);
}

Biblioteka::~Biblioteka()
{
    delete ui;
}
