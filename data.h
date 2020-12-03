#ifndef DATA_H
#define DATA_H

#include <QObject>
#include<QMap>
#include<QString>
#include<QDate>
#include<cstdlib>

class Data
{
public:
    static Data* getData();
    /**
     * @brief cookie
     * 管理员登录教务系统后将更新此cookie
     */
    QString cookie;
    QString getCurrentTime();
    int stuNum = 1;
private:
    /**
     * @brief Data
     * 单例设计模式：将Data类的构造函数设为私有
     */
    Data();

};

#endif // DATA_H
