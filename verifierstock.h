#ifndef VERIFIERSTOCK_H
#define VERIFIERSTOCK_H

#include <QDialog>
#include "Mydb.h"
#include "updateproduit.h"
#include "deleteproduit.h"

namespace Ui {
class verifierStock;
}

class verifierStock : public QDialog
{
    Q_OBJECT

public:
    explicit verifierStock(QWidget *parent = nullptr);
    ~verifierStock();

private slots:
    void on_btnFind_clicked();

    void on_Editebts_clicked();

    void on_deletebtn_clicked();

private:
    Ui::verifierStock *ui;

    UpdateProduit * ptrUpdateProduit;
    DeleteProduit * ptrDeleteProduit;
};

#endif // VERIFIERSTOCK_H
