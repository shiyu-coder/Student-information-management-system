#include "student.h"

Student::Student()
{
    this->data=Data::getData();
    this->setSno();
}

void Student::setSno() // 以data类中的当前学生数目作为学号
{
    char charSno[9];
    int key = data->stuNum;
    char charKey[9];
    itoa(key,charKey,10); // 数字转字符数组
    int lengthOfKey = strlen(charKey);
    for(int i = 0; i <= 7 - lengthOfKey; i++) // 在字符串前面填充0
        charSno[i] = '0';
    for(int i = 0; i <= lengthOfKey - 1; i++) // 在字符串后面填充学生数目
        charSno[8-lengthOfKey+i]=charKey[i];
    charSno[8] = '\0';
    this->Sno = QString::fromLocal8Bit(charSno,512); //字符数组转化为QString
    data->stuNum++;
}

QString Student::getSno(){
    return this->Sno;
}

void Student::setSname(QString name){
    this->Sname = name;
}

QString Student::getSname(){
    return this->Sname;
}

void Student::setSsex(QString sex){
    this->Ssex = sex;
}

QString Student::getSsex(){
    return this->Ssex;
}

void Student::setSpassw(QString passw){
    this->Spassw = passw;
}

QString Student::getSpassw(){
    return this->Spassw;
}

void Student::setSdept(QString dept){
    this->Sdept = dept;
}

QString Student::getSdept(){
    return this->Sdept;
}

void Student::setSmajor(QString major){
    this->Smajor = major;
}

QString Student::getSmajor(){
    return this->Smajor;
}

void Student::setSgrade(int grade){
    this->Sgrade = grade;
}

int Student::getSgrade(){
    return this->Sgrade;
}

void Student::setSadmin(QString admin){
    this->Sadmin = admin;
}

QString Student::getSadmin(){
    return this->Sadmin;
}
