#ifndef DATA_H
#define DATA_H

#include <QObject>
#include<QMap>
#include<QString>

class Data
{
public:
    static Data* getData();
    /**
     * @brief cookie
     * 管理员登录教务系统后将更新此cookie
     */
    QString cookie;
private:
    /**
     * @brief Data
     * 单例设计模式：将Data类的构造函数设为私有
     */
    Data();

};

#endif // DATA_H
