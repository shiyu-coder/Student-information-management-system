#include "mainwindow.h"

#include <QApplication>
#include<QtDebug>
#include<QtSql>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlQuery>
#include<QVariant>
#include<QSqlError>
#include<QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("E_Chain_Database");
    db.setUserName("sa");
    db.setHostName("192.168.56.1");
    db.setPassword("9638527410.s");
    if(!db.open()){
        qDebug()<<"fail to open!"<<endl<<db.lastError();
    }else{
        qDebug()<<"successful!"<<endl;
        db.close();
    }
    return a.exec();
}
