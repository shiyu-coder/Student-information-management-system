#include "dataquery.h"

DataQuery::DataQuery()
{
    this->databaseOnline=false;
}

DataQuery::~DataQuery(){
    db.close();
}

DataQuery* DataQuery::getDataQuery(){
    static DataQuery* dataQuery=nullptr;
    if(dataQuery==nullptr){
        dataQuery=new DataQuery();
    }
    return dataQuery;
}

QString DataQuery::connectToDatabase(QString userName,QString password){
    db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("E_Chain_Database");
    db.setUserName(userName);
    db.setHostName("192.168.56.1");
    db.setPassword(password);
    if(!db.open()){
        return "数据库连接失败！";
    }else{
        databaseOnline=true;
        return "";
    }
}

bool DataQuery::canLogInSIMS(QString userName,QString password,int type){
    return true;
}

QString DataQuery::init(){
    QFile init_file("SqlCode/CreateTable_New.sql");
    if(init_file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString sql=init_file.readAll().data();
        this->db.exec(sql);
        if(db.lastError().type()==QSqlError::NoError){
            return "数据库初始化成功！";
        }else{
            return db.lastError().text();
        }
    }else{
        return "初始化sql文件读取失败！";
    }
}
