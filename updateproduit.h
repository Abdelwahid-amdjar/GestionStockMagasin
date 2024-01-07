#ifndef UPDATEPRODUIT_H
#define UPDATEPRODUIT_H

#include <QDialog>
#include "Mydb.h"

namespace Ui {
class UpdateProduit;
}

class UpdateProduit : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateProduit(QWidget *parent = nullptr);
    ~UpdateProduit();

private slots:
    void on_btnEditer_clicked();

private:
    Ui::UpdateProduit *ui;
};

#endif // UPDATEPRODUIT_H
