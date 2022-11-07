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
    explicit Biblioteka(QString const *a, class QSqlDatabase *database, QWidget *parent = nullptr);
    ~Biblioteka();
    void wypozyczoneKsiazki();

private:
    Ui::Biblioteka *ui;
    const QString *user;
    QSqlDatabase *db;
    class QStandardItemModel *widokTabeli;
};

#endif // BIBLIOTEKA_H
