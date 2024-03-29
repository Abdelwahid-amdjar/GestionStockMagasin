#include "addproduit.h"
#include "ui_addproduit.h"



AddProduit::AddProduit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddProduit)
{
    ui->setupUi(this);
}

AddProduit::~AddProduit()
{
    delete ui;
}

void AddProduit::on_btnAdd_clicked()
{
    ui->lblInfo->setText("");
    QString produitName = ui->txtName->text();
    QString code = ui->txtCode->text();
    QString description = ui->txtDescription->text();
    QString prix = ui->txtprix->text();
    QString stockInitial = ui->txtQuntiti->text();

    qDebug() <<"Produit Name "<<produitName<<" code "<<code<<" description "<<description<<" selling Price "<<prix <<" stock initial " <<stockInitial;

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
    query.prepare("insert into Produit (name,code,description,prix,stockInitial) values ('" +produitName +"','" +code + "','"+ description + "','" +prix + "','"+ stockInitial+ "')");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->lblInfo->setText("Unable to Add Product");
    }
    else
    {
        if(query.numRowsAffected() > 0)
        {
            qDebug() <<"read was successful "<< query.lastQuery();
            ui->lblInfo->setText("Product Added Successfully!");
        }
        else
            qDebug() <<"Unable to Add new Product";
     }



    database.close();

}


void AddProduit::on_btnReset_clicked()
{
    ui->lblInfo->setText("");
    ui->txtName->setText("");
    ui->txtCode->setText("");
    ui->txtDescription->setText("");
    ui->txtprix->setText("");
    ui->txtQuntiti->setText("");
}

