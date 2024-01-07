#include "verifierstock.h"
#include "ui_verifierstock.h"



verifierStock::verifierStock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::verifierStock)
{
    ui->setupUi(this);

    ptrUpdateProduit = new UpdateProduit(this);
    ptrDeleteProduit = new DeleteProduit(this);
}

verifierStock::~verifierStock()
{
    delete ui;
    delete ptrUpdateProduit;
    delete ptrDeleteProduit;
}

void verifierStock::on_btnFind_clicked()
{

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

    //QSqlQuery query(database);
    //query.clear();
    //query.prepare("select * from Produit where " +sCriteriaColum+" like '%" + sValue + "%'");
    //query.prepare("select * from Produit , Entree where Produit.id = Entree.id_produit and " + sCriteriaColum + " like '%" + sValue + "%'");

    QSqlQuery query(database);
    query.exec("SELECT Produit.name AS nom_produit, "
                   "Produit.stockInitial, "
                   "COALESCE(SUM(Entree.Quntite), 0) AS total_entrees, "
                   "COALESCE(SUM(Sortie.Quntite), 0) AS total_sorties, "
                   "Produit.stockInitial + COALESCE(SUM(Entree.Quntite), 0) - COALESCE(SUM(Sortie.Quntite), 0) AS stock_disponible "
                   "FROM Produit "
                   "LEFT JOIN Entree ON produit.id = Entree.id_produit "
                   "LEFT JOIN Sortie ON produit.id = Sortie.id_produit "
                   "GROUP BY Produit.id, Produit.name, Produit.stockInitial");


    while (query.next())
        {
            QString nomProduit = query.value("nom_produit").toString();
            int stockInitial = query.value("stock_initial").toInt();
            int totalEntrees = query.value("total_entrees").toInt();
            int totalSorties = query.value("total_sorties").toInt();
            int stockDisponible = query.value("stock_disponible").toInt();

            qDebug() << "Produit : " << nomProduit;
            qDebug() << "Stock Initial : " << stockInitial;
            qDebug() << "Total Entrées : " << totalEntrees;
            qDebug() << "Total Sorties : " << totalSorties;
            qDebug() << "Stock Disponible : " << stockDisponible;
            qDebug() << "------------------------";
        }
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

    database.close();

}





void verifierStock::on_Editebts_clicked()
{
    ptrUpdateProduit->show();
}


void verifierStock::on_deletebtn_clicked()
{
    ptrDeleteProduit->show();
}

