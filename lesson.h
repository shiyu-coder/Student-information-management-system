#ifndef LESSON_H
#define LESSON_H
#include<QString>

/**
 * @brief The Lesson class
 * 课程类：每个课程存放于一个课程类中
 */
class Lesson
{
private:
    /**
     * @brief key
     * 课程编号
     */
    QString key;
    /**
     * @brief name
     * 课程名称
     */
    QString name;
    /**
     * @brief type
     * 课程类型（性质）
     */
    QString type;
    /**
     * @brief department
     * 开课院系
     */
    QString department;
    /**
     * @brief credit
     * 课程学分
     */
    int credit;
    /**
     * @brief class_hours
     * 课程学时
     */
    int class_hours;
    /**
     * @brief campus
     * 校区
     */
    QString campus;
    /**
     * @brief teacher
     * 教师
     */
    QString teacher;
    /**
     * @brief time_location
     * 上课时间及地点
     */
    QString time_location;
    /**
     * @brief info
     * 详细信息（html）
     */
    QString info;

public:
    Lesson();
    void setKey(QString key);
    void setName(QString name);
    void setType(QString type);
    void setDepartment(QString department);
    void setCredit(int credit);
    void setClass_hours(int class_hours);
    void setCampus(QString campus);
    void setTeacher(QString teacher);
    void setTime_location(QString time_location);
    void setInfo(QString info);
    QString getKey();
    QString getName();
    QString getType();
    QString getDepartment();
    int getCredit();
    int getClass_hours();
    QString getCampus();
    QString getTeacher();
    QString getTime_location();
    QString getInfo();
};

#endif // LESSON_H
