#ifndef STUDENT_H
#define STUDENT_H

#include "data.h"

class Student
{
public:
    Student();
    void setSno();
    QString getSno();
    void setSname(QString name);
    QString getSname();
    void setSsex(QString sex);
    QString getSsex();
    void setSpassw(QString passw);
    QString getSpassw();
    void setSdept(QString dept);
    QString getSdept();
    void setSmajor(QString major);
    QString getSmajor();
    void setSgrade(int grade);
    int getSgrade();
    void setSadmin(QString admin);
    QString getSadmin();
private:
    Data * data;
    QString Sno;
    QString Sname;
    QString Ssex;
    QString Spassw;
    QString Sdept;
    QString Smajor;
    int Sgrade;
    QString Sadmin;
};

#endif // STUDENT_H
