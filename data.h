#ifndef DATA_H
#define DATA_H
#include<QString>
#include<QVector>
#include<QEventLoop>
#include<QProcess>
#include<QJsonParseError>
#include<QJsonObject>
#include<QJsonArray>
#include <QEventLoop>
#include<QHostInfo>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QByteArray>
#include<QNetworkRequest>
#include<QUrl>
#include<QDebug>
/**
 * @brief The Data class
 * 核心数据操作类——Data
 * 包含对基金信息的获取（通过网络api）、更新、查询、删除、插入等数据处理操作
 * 主要通过对数据库的sql语句的嵌入实现
 */
class Data :QObject
{
    Q_OBJECT
public:
    Data();
    /**
     * @brief getFundFromApi
     * 根据基金代码查询相关基金的基本信息，不包含历史信息
     * @param Keys
     * 所有要查询的基金的代码
     */
    void getFundMsgFromApi(QVector<QString> Keys);
};

#endif // DATA_H
