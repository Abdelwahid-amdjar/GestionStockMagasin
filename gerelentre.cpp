#include "gerelentre.h"
#include "ui_gerelentre.h"

GereLentre::GereLentre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GereLentre)
{
    ui->setupUi(this);
}

GereLentre::~GereLentre()
{
    delete ui;
}

void GereLentre::on_btnAdd_clicked()
{
    ui->lblInfo->setText("");
    QString idProduit = ui->txtProduit->text();
    QString idFournisseur = ui->txtFournisseur->text();
    QString quntite = ui->txtQuntite->text();
    QString dateEntre = ui->txtDateEntre->text();

    qDebug() <<"idProduit "<<idProduit<<" idFournisseur "<<idFournisseur<<" quntite "<<quntite<<" dateEntre "<<dateEntre;

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
    query.prepare("insert into Entree (id_produit,id_fournisseur,Quntite,dateEntre) values ('" +idProduit +"','" +idFournisseur + "','"+ quntite + "','" +dateEntre + "')");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->lblInfo->setText("Unable to Add New Product Purchase");
    }
    else
    {
        if(query.numRowsAffected() > 0)
        {
            qDebug() <<"read was successful "<< query.lastQuery();
            ui->lblInfo->setText("New Product Purchase Added Successfully!");
        }
        else
            qDebug() <<"Unable to Add New Product Purchase";
     }



    database.close();

}


void GereLentre::on_btnReset_clicked()
{
    ui->lblInfo->setText("");
    ui->txtProduit->setText("");
    ui->txtFournisseur->setText("");
    ui->txtQuntite->setText("");
    ui->txtDateEntre->setText("");
}

