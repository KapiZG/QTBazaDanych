#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTextEdit>
#include <biblioteka.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("QTProject");

    if(db.open())
    {
        qDebug() << "Opened!";
        connect(ui->Zaloguj, &QPushButton::pressed, this, &MainWindow::logowanie);
        connect(ui->Zarejestruj, &QPushButton::pressed, this, &MainWindow::rejestracja);
//        QSqlQuery query;
//        query.exec("Select * from ksiazki where id not in(Select id_ksiazki from wyporzyczenia)");
//        while(query.next())
//        {
//            int id = query.value(0).toInt();
//            QString tytul = query.value(1).toString();
//            float cena = query.value(2).toFloat();
//            qDebug() << id << " " << tytul << " " << cena << Qt::endl;
//        }
    }
    else
    {
        qDebug() << db.lastError();
    }

}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::logowanie()
{
    ui->Zaloguj->hide();
    ui->Zarejestruj->hide();
    QWidget *logowanie = new QWidget();
    QLineEdit *login = new QLineEdit("Wpisz nazwę");
    QLineEdit *haslo = new QLineEdit("Wpisz haslo");
    QPushButton *potwierdz = new QPushButton("Potwierdź");
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(login);
    layout->addWidget(haslo);
    layout->addWidget(potwierdz);
    logowanie->setLayout(layout);
    this->layout()->addWidget(logowanie);
    connect(potwierdz, &QPushButton::pressed, this, [logowanie, login, haslo, this]()
    {

        QSqlQuery sprawdzenieLogowania;

        QString nazwaUzytkownika = login->text();

        const std::string select = (std::string("Select id from users where nazwa = \"") + login->text().toStdString() + "\" and haslo = \"" + haslo->text().toStdString() + "\" ;");

        sprawdzenieLogowania.exec(select.c_str());
        if(sprawdzenieLogowania.next())
        {
            delete logowanie;
            qDebug()<<"Zalogowałeś się";
            QWidget *potwierdzenie = new QWidget;
            QTextEdit *poprawne = new QTextEdit("Udało się zalogować");
            poprawne->setReadOnly(true);
            QPushButton *zatwierdz = new QPushButton("Zatwierdź");
            QVBoxLayout *layout = new QVBoxLayout();
            layout->addWidget(poprawne);
            layout->addWidget(zatwierdz);
            potwierdzenie->setLayout(layout);
            this->layout()->addWidget(potwierdzenie);
            connect(zatwierdz, &QPushButton::pressed, this, [this, nazwaUzytkownika]()
            {
                Biblioteka *biblioteka = new Biblioteka(&nazwaUzytkownika, &this->db);
                biblioteka->show();
                this->close();
            });
        }
        else
        {
            QMessageBox::critical(this, "Error", "Nie ma takiego użytkownika");
        }
    });

}


void MainWindow::rejestracja()
{
    ui->Zaloguj->hide();
    ui->Zarejestruj->hide();

    QWidget *rejestracja = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    QLineEdit *login = new QLineEdit("Podaj Nazwę użytkownika/Email");
    QLineEdit *haslo = new QLineEdit("Podaj Hasło");
    QPushButton *zatwierdz = new QPushButton("Zatwierdż");

    QLineEdit *blad = new QLineEdit();
    blad->hide();



    layout->addWidget(login);
    layout->addWidget(haslo);
    layout->addWidget(zatwierdz);
    layout->addWidget(blad);
    rejestracja->setLayout(layout);
    this->layout()->addWidget(rejestracja);

    connect(zatwierdz, &QPushButton::pressed, this, [=]()
    {
        QString *pLogin = new QString(login->text());
        QString *pHaslo = new QString(haslo->text());
        if(pLogin->length() > 3 && pHaslo->length() > 3)
        {
            QSqlQuery insert;
            insert.prepare("Insert into users value (null, :login, :haslo);");
            insert.bindValue(":login", pLogin->toStdString().c_str());
            insert.bindValue(":haslo", pHaslo->toStdString().c_str());
            insert.exec();
            delete rejestracja;

            QWidget *udane = new QWidget();
            QVBoxLayout *layout = new QVBoxLayout();
            QTextEdit *pomyslnie = new QTextEdit((std::string("Udało się zarejestrować użytkownika: ") + pLogin->toStdString()).c_str());
            QPushButton *zatwierdz = new QPushButton("Zatwierdź");

            layout->addWidget(pomyslnie);
            layout->addWidget(zatwierdz);
            udane->setLayout(layout);
            this->layout()->addWidget(udane);

            connect(zatwierdz, &QPushButton::pressed, this, [udane, this]()
            {
                delete udane;
                this->ui->Zaloguj->show();
                this->ui->Zarejestruj->show();
            });
        }
        else if(pLogin->length() <= 3 && pHaslo->length() > 3)
        {
            blad->setText("Login jest za krótki");
            blad->show();
        }
        else if(pLogin->length() > 3 && pHaslo->length() <= 3)
        {
            blad->setText("Hasło jest za krótkie");
            blad->show();
        }
        else
        {
            blad->setText("Login i hasło są za krótkie");
            blad->show();
        }


    });




}
