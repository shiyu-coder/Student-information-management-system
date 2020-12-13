#ifndef DATAQUERY_H
#define DATAQUERY_H

#include <QObject>
#include<QtDebug>
#include<QtSql>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlQuery>
#include<QVariant>
#include<QSqlError>
#include<QFile>
#include<QTextStream>

//关于三种登录身份的标识,type==ADMIN
#define ADMIN 1
#define TEACHER 2
#define STUDENT 3

class DataQuery :QObject
{
    Q_OBJECT
public:
    static DataQuery* getDataQuery();
    /**
     * @brief connectToDatabase
     * 连接数据库
     * @param userName
     * 登录名
     * @param password
     * 密码
     * @return
     * 连接结果
     */
    QString connectToDatabase(QString userName,QString password);
    /**
     * @brief canLogInSIMS
     * 判断用户名和密码是否正确，是否允许登录程序
     * @param userName
     * 用户账号
     * @param password
     * 密码
     * @param type
     * 登陆类型，有三种：ADMIN,TEACHER,STUDENT
     * @return
     * 是否允许登录
     */
    bool canLogInSIMS(QString userName,QString password,int type);
    /**
     * @brief databaseOnline
     * 目前是否已连接到数据库
     */
    bool databaseOnline;
    /**
     * @brief init
     * 数据库初始化
     * @return QStirng
     */
    QString init();
    /**
     * @brief insertLesson
     * 插入学生信息
     */
    QString insertLesson(QString cno,QString cname,QString cchar,QString cdept,QString ccredit,QString cgrade);
    /**
     * @brief insertDept
     * 插入院系信息
     */
    QString insertDept(QString dname,QString dintro);
    /**
     * @brief selectDept
     * 查询院系表信息
     * @param qualificated
     * 是否有限定条件
     * @param qualificaion
     * 限定条件
     */
    //QString selectDept(bool qualificated,QString qualificaion);
private:
    /**
     * @brief db
     * 数据库实例
     */
    QSqlDatabase db;

    DataQuery();
    ~DataQuery();
};

#endif // DATAQUERY_H
