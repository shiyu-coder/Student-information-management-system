#include "student.h"

Student::Student()
{
    this->data=Data::getData();
    this->setSno();
}

void Student::setSno(){

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
