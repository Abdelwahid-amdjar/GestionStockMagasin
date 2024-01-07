#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addproduit.h"
#include "addfourniseur.h"
#include "gerelentre.h"
#include "gerestock.h"
#include "verifierstock.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;

    AddProduit *ptrAddProduit;
    AddFourniseur *ptrAddFourniseur;
    GereLentre *ptrGereLentre;
    GereStock *ptrGereStock;
    verifierStock *ptrverifierStock;
};
#endif // MAINWINDOW_H
