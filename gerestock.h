#ifndef GERESTOCK_H
#define GERESTOCK_H

#include <QDialog>
#include "Mydb.h"

namespace Ui {
class GereStock;
}

class GereStock : public QDialog
{
    Q_OBJECT

public:
    explicit GereStock(QWidget *parent = nullptr);
    ~GereStock();

private slots:
    void on_btnAdd_clicked();

    void on_btnReset_clicked();

    void on_btnReset_2_clicked();

private:
    Ui::GereStock *ui;
};

#endif // GERESTOCK_H
