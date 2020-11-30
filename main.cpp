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
#include<loginwidget.h>
#include<data.h>
#include<QVector>
#include<QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogInWidget *loginwidget=new LogInWidget();
    loginwidget->show();
    //123456
    Data *data=new Data();
    QVector<QString> keys;
    //last
    keys.push_back(QString("202015"));
    data->getFundMsgFromApi(keys);
    return a.exec();
}

/*
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("E_Chain_Database");
    db.setUserName("sa");
    db.setHostName("192.168.56.1");
    db.setPassword("9638527410.s");
    if(!db.open()){
        qDebug()<<"fail to open!"<<endl<<db.lastError();
    }else{
        qDebug()<<"successful!"<<endl;
        QSqlQuery query;
        query.exec("create table test(id integer primary key, name nvarchar(20),age int)");
        query.exec("insert into test values(1,'小明',14)");
        //此行用于测试pull功能
        db.close();
    }
*/
