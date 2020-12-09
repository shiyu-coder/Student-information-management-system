#include "dataquery.h"

DataQuery::DataQuery()
{
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
        return "";
    }
}

bool DataQuery::canLogInSIMS(QString userName,QString password,int type){
    return true;
}
