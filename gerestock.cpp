#include "gerestock.h"
#include "ui_gerestock.h"

GereStock::GereStock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GereStock)
{
    ui->setupUi(this);
}

GereStock::~GereStock()
{
    delete ui;
}

void GereStock::on_btnAdd_clicked()
{
    ui->lblInfo->setText("");
    QString idProduit = ui->txtProduit->text();
    QString idClient = ui->txtClient->text();
    QString quntiti = ui->txtQuntite->text();
    QString dateSortie = ui->txtDateSortie->text();

    qDebug() <<"idProduit "<<idProduit<<" idClient "<<idClient<<" quntite "<<quntiti<<" dateSortie "<<dateSortie;

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
    query.prepare("insert into Sortie (id_produit,id_client,Quntite,dateSortie) values ('" +idProduit +"','" +idClient + "','"+ quntiti + "','" +dateSortie + "')");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->lblInfo->setText("Unable to Add product sales ?");
    }
    else
    {
        if(query.numRowsAffected() > 0)
        {
            qDebug() <<"read was successful "<< query.lastQuery();
            ui->lblInfo->setText("product sales Added Successfully!");
        }
        else
            qDebug() <<"Unable to Add product sales !";
     }



    database.close();

}

