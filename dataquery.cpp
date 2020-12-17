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
    if(type==1){
        //教师
        if(connectToDatabase("T"+userName,password)==""){
            return true;
        }else{
            return false;
        }
    }else if(type==2){
        //学生
        if(connectToDatabase("S"+userName,password)==""){
            return true;
        }else{
            return false;
        }
    }
    return false;
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

QString DataQuery::insertDept(QString dname,QString dintro){
    if(dname==""){
        return "";
    }
    db.exec("insert into Dept values('"+dname+"','"+dintro+"')");
    if(db.lastError().type()==QSqlError::NoError){
        return "";
    }else{
        return db.lastError().text();
    }
}

QString DataQuery::insertLesson(QString cno,QString cname,QString cchar,QString cdept,QString ccredit,QString cgrade){
    //确定选课人数上限
    QString climit = "50";
    QString ccur="0";
    QString sql="insert into CourseBasic values('"+cno+"'";
    if(cchar.size()>0) sql+=",'"+cname+"'";
    else sql+=",NULL";

    sql+=","+climit+","+ccur;

    if(cchar.size()>0) sql+=",'"+cchar+"'";
    else sql+=",NULL";

    if(cdept.size()>0) sql+=",'"+cdept+"'";
    else sql+=",NULL";

    if(ccredit.size()>0) sql+=",'"+ccredit+"'";
    else sql+=",NULL";

    sql+=",'"+cgrade+"')";
    qDebug()<<sql;
    db.exec(sql);
    if(db.lastError().type()==QSqlError::NoError){
        return "";
    }else{
        return db.lastError().text();
    }
}
