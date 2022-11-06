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
    explicit Biblioteka(QString const *a, QWidget *parent = nullptr);
    ~Biblioteka();

private:
    Ui::Biblioteka *ui;
    const QString *user;
};

#endif // BIBLIOTEKA_H
