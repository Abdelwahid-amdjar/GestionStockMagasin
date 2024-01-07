#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptrAddProduit = new AddProduit(this);
    ptrAddFourniseur = new AddFourniseur(this);
    ptrGereLentre = new GereLentre(this);
    ptrGereStock = new GereStock(this);
    ptrverifierStock = new verifierStock(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ptrAddProduit;
    delete ptrAddFourniseur;
    delete ptrGereLentre;
    delete ptrGereStock;
    delete ptrverifierStock;
}


void MainWindow::on_pushButton_clicked()
{
    ptrAddProduit->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    ptrAddFourniseur->show();
}


void MainWindow::on_pushButton_5_clicked()
{
    ptrGereLentre->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    ptrGereStock->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    ptrverifierStock->show();
}


void MainWindow::on_pushButton_6_clicked()
{

    QString sCriteriaColum = "";

    if(ui->rdoProduit->isChecked())
        sCriteriaColum="Produit";
    else if (ui->rdoFournisseur->isChecked())
        sCriteriaColum="Fournisseur";
    else
        sCriteriaColum = "Produit";

    qDebug() << "in init()";
    QSqlQueryModel * model = new QSqlQueryModel(this);

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("C:/Users/Hp/Documents/EMSI 3IIR1/Projet c++/databases/GestionStock.db");

    if(QFile::exists("C:/Users/Hp/Documents/EMSI 3IIR1/Projet c++/databases/GestionStock.db"))
    {
        qDebug() <<"databses file exist";
    }
    else
    {
        qDebug() <<"DB file doesn't exists";
        return;
    }

    if(!database.open())
    {
        qDebug() <<"Error: Unable to open Database" ;
        return;
    }
    else
    {
        qDebug() <<" Database open successfully..";
    }

    QSqlQuery query(database);
    query.clear();
    query.prepare("select * from " +sCriteriaColum+"");

    if(!query.exec())
       qDebug() << query.lastError().text() << query.lastQuery();
    else
    {
       if(query.numRowsAffected()>0)
       qDebug() << "== success query fetch() : " << query.lastQuery();
       else {
           qDebug() << " No record ! found ";
           qDebug() << " Query is : " << query.lastQuery();
       }
    }
    while(query.next())
    qDebug()<<query.value(0).toString();

    model->setQuery(query);
    ui->tableView->setModel(model);
    qDebug() << "rows are : " << model->rowCount();
    ui->tableView->show();
}

