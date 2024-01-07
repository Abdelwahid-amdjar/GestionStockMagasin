#ifndef DELETEPRODUIT_H
#define DELETEPRODUIT_H

#include <QDialog>
#include "Mydb.h"

namespace Ui {
class DeleteProduit;
}

class DeleteProduit : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteProduit(QWidget *parent = nullptr);
    ~DeleteProduit();

private slots:
    void on_btnDelete_clicked();

private:
    Ui::DeleteProduit *ui;
};

#endif // DELETEPRODUIT_H
