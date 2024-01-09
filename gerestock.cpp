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


void GereStock::on_btnReset_clicked()
{
    ui->ValueStock->setText("");
    QString idProduit = ui->idValue->text();

    if (idProduit.isEmpty())
    {
        qDebug() << "ID is empty";
        // Handle the case where the ID is empty (e.g., show an error message)
        return;
    }
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

    query.prepare("SELECT Produit.id,"
                  "Produit.stockInitial ,"
                  "COALESCE(SUM(Entree.Quntite), 0) AS total_entrees, "
                  "COALESCE(SUM(Sortie.Quntite), 0) AS total_sorties, "
                  "Produit.stockInitial + COALESCE(SUM(Entree.Quntite), 0) - COALESCE(SUM(Sortie.Quntite), 0) AS stock_disponible "
                  "FROM Produit "
                  "LEFT JOIN Entree ON produit.id = Entree.id_produit "
                  "LEFT JOIN Sortie ON produit.id = Sortie.id_produit "
                  "WHERE Produit.id = :idProduit");
    query.bindValue(":idProduit", idProduit);

    if (!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->lblInfo->setText("NO");
        ui->ValueStock->setText("Error");
        qDebug() << "Nothing!";
    }
    else
    {
        if (query.next())
            {
                QString stockDisponible = query.value("stock_disponible").toString();
                ui->ValueStock->setText(stockDisponible);
                qDebug() << "Good";
                if (stockDisponible.isEmpty())
                {
                    qDebug() << "stockDisponible is empty";
                    ui->ValueStock->setText("Error");
                    ui->lblInfo->setText("cette produit n'est pa la !!!");
                    return;
                }
            }
        else
            {
                qDebug() << "No data found for the given ID";
                // Handle the case where no data is found for the given ID (e.g., show an error message)
                ui->ValueStock->setText("N/A");
            }
    }

    database.close();

}


void GereStock::on_btnReset_2_clicked()
{
    ui->lblInfo->setText("");
    ui->txtProduit->setText("");
    ui->txtClient->setText("");
    ui->txtQuntite->setText("");
    ui->txtDateSortie->setText("");
}

