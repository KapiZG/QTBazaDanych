#include "biblioteka.h"

#include "ui_biblioteka.h"
#include <QtSql>
#include <QStandardItemModel>
#include <QPushButton>

Biblioteka::Biblioteka(const QString *a, QSqlDatabase *database,  QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Biblioteka)
{
    ui->setupUi(this);

    user = a;
    db = database;
    ui->NazwaUzytkownika->setText(QString("Witaj z powrotem: ") + *a);

//Tworzenie rabeli z dostępnymi książkami
    widokTabeli = new QStandardItemModel(ui->Ksiazki);
    ui->Ksiazki->setModel(widokTabeli);

    widokTabeli->setColumnCount(3);
    widokTabeli->setHorizontalHeaderLabels({"Tytuł", "Cena", "Wypożycz"});

    QSqlQuery query;
    query.exec("Select * from ksiazki where id not in(Select id_ksiazki from wyporzyczenia)");
    while(query.next())
    {


        QList lista = {new QStandardItem(query.value(1).toString()), new QStandardItem(QString(query.value(2).toString()) + QString("zł"))};

        widokTabeli->appendRow(lista);
    }


}

Biblioteka::~Biblioteka()
{
    delete ui;
}

//Funkcja służąca wyświetleniu tabeli, która zawiera książki jakie dany użytkownik wypożyczył
void Biblioteka::wypozyczoneKsiazki()
{
    QSqlQuery query;
    query.exec(QString("Select tytul from ksiazki where id in(Select id_ksiazki from wyporzyczenia where id_usera = (Select id from users where nazwa =") + *user  + QString("));"));

}
