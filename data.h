#ifndef DATA_H
#define DATA_H

#include <QObject>
#include<QMap>
#include<QString>
#include<QDate>
#include<cstdlib>
#include<QStringList>
#include<lesson.h>

class Data
{
public://函数区域
    /**
     * @brief getData
     * 获取data类指针
     */
    static Data* getData();
    /**
     * @brief getCurrentTime
     * 返回当前时间，格式：[yyyy-MM-dd hh:mm:ss]
     * @return QString
     */
    QString getCurrentTime();
    /**
     * @brief splitTeacherFromRawStr
     * 将html中提取的课程教师信息进行处理得到教师列表
     * @param rawStr 从html中提取的未处理的课程教师信息
     * @return QStringList 分割得到的教师姓名的字符串列表
     */
    QStringList getTeacherFromRawStr(QString rawStr);
    /**
     * @brief getLessonTimeFromRawStr
     * 将html中提取的课程时间信息进行处理
     * @param rawStr 从html中提取的未处理的课程时间及地点信息
     * @return QStringList 分割得到的课程时间信息
     */
    Lesson_time getLessonTimeFromRawStr(QString rawStr);
public://变量区域
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
