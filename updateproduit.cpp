#include "updateproduit.h"
#include "ui_updateproduit.h"

UpdateProduit::UpdateProduit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateProduit)
{
    ui->setupUi(this);
}

UpdateProduit::~UpdateProduit()
{
    delete ui;
}

void UpdateProduit::on_btnEditer_clicked()
{
    ui->lblInfo->setText("");
   QString ProduitId = ui->txtId->text();
   QString ProduitStockInial = ui->txtStockInial->text();

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

   query.prepare("UPDATE Produit SET stockInitial = :nouveauStockInitial WHERE id = :id");
   query.bindValue(":nouveauStockInitial", ProduitStockInial);
   query.bindValue(":id", ProduitId.toInt());

   if(!query.exec())
   {
       qDebug() << query.lastError().text() << query.lastQuery();
       ui->lblInfo->setText("Unable to Update Product");
   }
   else
   {
       if(query.numRowsAffected() > 0)
       {
           qDebug() <<"read was successful "<< query.lastQuery();
           ui->lblInfo->setText("Product Updated Successfully!");
       }
       else
           qDebug() <<"Unable to Update Product";
    }



   database.close();
}

