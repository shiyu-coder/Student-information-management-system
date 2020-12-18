#ifndef DATA_H
#define DATA_H

#include <QObject>
#include<QMap>
#include<QString>
#include<QDate>
#include<cstdlib>
#include<QStringList>
#include<lesson.h>
#include<QTextCodec>

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
    /**
     * @brief haveLoggedInSIMS
     * 标记是否已经登陆过教服系统
     */
    bool haveLoggedInSIMS;
    /**
     * @brief sno
     * 当前登录学生的学生编号
     */
    QString sno;
    /**
     * @brief tno
     * 当前登录教师的学生编号
     */
    QString tno;
private:
    /**
     * @brief Data
     * 单例设计模式：将Data类的构造函数设为私有
     */
    Data();

};
/**
 * @brief checkNum
 * 用于查找给定字符串中含有多少个相同指定待查字符串（待查字符串为中文时很可能出现bug，比如“小李”和“小王”被认为是相同的字符串，这可能与编码格式有关，导致中文不能正确呈现）
 * @param rawStr
 * 源字符串
 * @param toFind
 * 待查字符串
 * @return
 * 源字符串中所含待查字符串的数量
 */
int checkNum(QString rawStr,QString toFind);
#endif // DATA_H
