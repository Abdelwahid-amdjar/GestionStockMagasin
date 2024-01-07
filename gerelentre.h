#ifndef GERELENTRE_H
#define GERELENTRE_H

#include <QDialog>
#include "Mydb.h"

namespace Ui {
class GereLentre;
}

class GereLentre : public QDialog
{
    Q_OBJECT

public:
    explicit GereLentre(QWidget *parent = nullptr);
    ~GereLentre();

private slots:
    void on_btnAdd_clicked();

private:
    Ui::GereLentre *ui;
};

#endif // GERELENTRE_H
