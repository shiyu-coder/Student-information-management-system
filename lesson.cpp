#include "lesson.h"

Lesson::Lesson()
{
    this->credit=0;
    this->class_hours=0;
}

QString Lesson::getKey(){
    return this->key;
}

void Lesson::setKey(QString key){
    this->key=key;
    return;
}

QString Lesson::getInfo(){
    return this->info;
}

void Lesson::setInfo(QString info){
    this->info = info;
    return;
}

QString Lesson::getName(){
    return this->name;
}

void Lesson::setName(QString name){
    this->name=name;
    return;
}

QString Lesson::getType(){
    return this->type;
}

void Lesson::setType(QString type){
    this->type = type;
    return;
}

int Lesson::getCredit(){
    return this->credit;
}

void Lesson::setCredit(int credit){
    this->credit = credit;
    return;
}

QString Lesson::getCampus(){
    return this->campus;
}

void Lesson::setCampus(QString campus){
    this->campus = campus;
    return;
}

int Lesson::getClass_hours(){
    return this->class_hours;
}

void Lesson::setClass_hours(int class_hours){
    this->class_hours=class_hours;
    return;
}

QString Lesson::getTeacher(){
    return this->teacher;
}

void Lesson::setTeacher(QString teacher){
    this->teacher=teacher;
    return;
}

QString Lesson::getDepartment(){
    return this->department;
}

void Lesson::setDepartment(QString department){
    this->department=department;
    return;
}

QString Lesson::getTime_location(){
    return this->time_location;
}

void Lesson::setTime_location(QString time_location){
    this->time_location=time_location;
    return;
}
