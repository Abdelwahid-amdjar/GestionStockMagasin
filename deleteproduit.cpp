#include "deleteproduit.h"
#include "ui_deleteproduit.h"

DeleteProduit::DeleteProduit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteProduit)
{
    ui->setupUi(this);
}

DeleteProduit::~DeleteProduit()
{
    delete ui;
}

void DeleteProduit::on_btnDelete_clicked()
{
    ui->lblInfo->setText("");
    QString ProduitId = ui->txtId->text();

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

    query.prepare("DELETE FROM Produit WHERE id = :id");
    query.bindValue(":id", ProduitId.toInt());

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->lblInfo->setText("Unable to Delete Product");
    }
    else
    {
        if(query.numRowsAffected() > 0)
        {
            qDebug() <<"read was successful "<< query.lastQuery();
            ui->lblInfo->setText("Product Deleted Successfully!");
        }
        else
            qDebug() <<"Unable to Delete Product";
     }



    database.close();
}

