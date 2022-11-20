#include "biblioteka.h"

#include "ui_biblioteka.h"
#include <QtSql>
#include <QStandardItemModel>
#include <QPushButton>
#include "mainwindow.h"

Biblioteka::Biblioteka(int *idd, const QString *a, QSqlDatabase *database,  QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Biblioteka)
{
    ui->setupUi(this);

    id = idd;
    user = a;
    db = database;
    ui->NazwaUzytkownika->setText(QString("Witaj z powrotem: ") + *a);

//Tworzenie tabeli z dostępnymi książkami
   tabelaDostepnychKsiazek();
   wypozyczoneKsiazki();

   connect(ui->Wyloguj, &QPushButton::pressed, this, [this]()
   {
       MainWindow *menu = new MainWindow();
       menu->show();
       this->close();
   });

}

Biblioteka::~Biblioteka()
{
    delete ui;
}

//Funkcja służąca wyświetleniu tabeli, która zawiera książki jakie dany użytkownik wypożyczył
void Biblioteka::wypozyczoneKsiazki()
{
    QSqlQuery query;
    QStandardItemModel *widokTabeli = new QStandardItemModel(ui->Wypozyczone);

    ui->Wypozyczone->setModel(widokTabeli);

    widokTabeli->setColumnCount(2);
    widokTabeli->setHorizontalHeaderLabels({"Tytuł", "Zwróć"});

    int i = 0;
    query.exec(QString("Select id, tytul from ksiazki where id in(Select id_ksiazki from wyporzyczenia where id_usera = (Select id from users where nazwa = \"") + *user  + QString("\"));"));
    while(query.next())
    {

        int *idKsiazki = new int(query.value(0).toInt());

        QList lista = {new QStandardItem(query.value(1).toString())};
        widokTabeli->appendRow(lista);
        QPushButton *przyciskZwroc = new QPushButton("Zwróć");
        ui->Wypozyczone->setIndexWidget(widokTabeli->index(i, 1), przyciskZwroc);
        connect(przyciskZwroc, &QPushButton::pressed, this, [=]()
        {
            qDebug() << i << " " << widokTabeli->rowCount();

            QSqlQuery insert;
            qDebug() << insert.exec(QString("Delete from wyporzyczenia where id_usera = ") + QString::number(*id) + QString(" and id_ksiazki = ") + QString::number(*idKsiazki));
            qDebug () << QString("Delete from wyporzyczenia where id_usera = ") + QString::number(*id) + QString(" and id_ksiazki = ") + QString::number(*idKsiazki);

            delete widokTabeli;
            wypozyczoneKsiazki();
            tabelaDostepnychKsiazek();

        });

        i++;
    }
}


void Biblioteka::tabelaDostepnychKsiazek()
{
    QStandardItemModel *widokTabeli = new QStandardItemModel(ui->Ksiazki);
    ui->Ksiazki->setModel(widokTabeli);

    widokTabeli->setColumnCount(3);
    widokTabeli->setHorizontalHeaderLabels({"Tytuł", "Cena", "Wypożycz"});

    QSqlQuery query;
    query.exec("Select * from ksiazki where id not in(Select id_ksiazki from wyporzyczenia)");
    int i = 0;
    while(query.next())
    {

        int *idKsiazki = new int(query.value(0).toInt());

        QList lista = {new QStandardItem(query.value(1).toString()), new QStandardItem(QString(query.value(2).toString()) + QString("zł"))};
        widokTabeli->appendRow(lista);
        QPushButton *przyciskWyporzycz = new QPushButton("Wypożycz");
        ui->Ksiazki->setIndexWidget(widokTabeli->index(i, 2), przyciskWyporzycz);
        connect(przyciskWyporzycz, &QPushButton::pressed, this, [=]()
        {
            qDebug() << i << " " << widokTabeli->rowCount();

            QSqlQuery insert;
            qDebug() << insert.exec(QString("Insert into wyporzyczenia value (null, ") + QString::number(*id) + QString(", ") + QString::number(*idKsiazki) + QString(", null);"));
            qDebug () << QString("Insert into wyporzyczenia value (null, (Select id from users where id=") + QString::number(*id) + QString("), ") + QString::number(*idKsiazki) + QString(", null);");

            delete widokTabeli;
            wypozyczoneKsiazki();
            tabelaDostepnychKsiazek();

        });

        i++;
    }
}
