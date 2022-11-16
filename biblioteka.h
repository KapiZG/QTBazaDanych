#ifndef BIBLIOTEKA_H
#define BIBLIOTEKA_H

#include <QWidget>

namespace Ui {
class Biblioteka;
}

class Biblioteka : public QWidget
{
    Q_OBJECT

public:
    explicit Biblioteka(int *i, QString const *a, class QSqlDatabase *database, QWidget *parent = nullptr);
    ~Biblioteka();
    void wypozyczoneKsiazki();
    void tabelaDostepnychKsiazek();

private:
    Ui::Biblioteka *ui;
    int *id;
    const QString *user;
    QSqlDatabase *db;
};

#endif // BIBLIOTEKA_H
