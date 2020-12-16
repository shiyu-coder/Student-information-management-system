#include "data.h"

Data::Data()
{
    haveLoggedInSIMS=false;
}

Data* Data::getData(){
    static Data* data_ptr=nullptr;
    if(data_ptr==nullptr){
        data_ptr=new Data();
    }
    return data_ptr;
}
int checkNum(QString rawStr,QString toFind)
{
    int flag = 0;
    int length = toFind.length();  //确定待查字符串的长度
    QChar firstCharacter = toFind.at(0); //确定待查字符串的首字母
    int num = 0; //待查字符串出现的次数
    QString workStr = rawStr;
    while(workStr.contains(toFind))
    {
        while(flag == 0)
        {
            int loc = 0;
            for(;workStr.at(loc)!=firstCharacter;loc++); //确定待查字符串首字母第一次出现的下标
            workStr.remove(0,loc); //此时loc前的部分一定不含有待查字符串，可删除；然后判断剩下的部分是否含有待查字符串
            flag = (workStr.startsWith(toFind)==true) ? 1 : 0; //判断loc开始的字符串是否是待查字符串
            if(flag == 0)
                workStr.remove(0,1);
        }
        workStr.remove(0,length);
        num++;
        flag=0;
    }
    return num;
}

QString Data::getCurrentTime(){
    QDateTime dateTime(QDateTime::currentDateTime());
    QString time = dateTime.toString("[yyyy-MM-dd hh:mm:ss] ");
    return time;
}

QStringList Data::getTeacherFromRawStr(QString rawStr){
    if(rawStr.size()<=0) return QStringList();
    QStringList teacherList= rawStr.split(",p");
    return teacherList;
}

Lesson_time Data::getLessonTimeFromRawStr(QString rawStr){
    if(rawStr.size()<=0) return Lesson_time();
    Lesson_time lessonTime;
    int numOfWeekday = checkNum(rawStr,"<br/>")+1;
    QString workStr = rawStr;
    for(int i = 0; i <numOfWeekday;i++)
    {
        int loc = workStr.indexOf("周"); //“周”的后面就是星期几
        QString day = workStr.at(loc + 1);
        if(day == "一") lessonTime.weekDay.append(1);
        else if(day == "二") lessonTime.weekDay.append(2);
        else if(day == "三") lessonTime.weekDay.append(3);
        else if(day == "四") lessonTime.weekDay.append(4);
        else if(day == "五") lessonTime.weekDay.append(5);
        else if(day == "六") lessonTime.weekDay.append(6);
        else if(day == "七") lessonTime.weekDay.append(7);
        loc = workStr.indexOf("第"); //"第"的后面是课程开始时间
        QChar begin = workStr.at(loc + 1);
        QChar begin2 = workStr.at(loc + 2);//‘1’可能是第一节课，也可能是第十节课，故需要第二位数字判断
        if(begin == '1'&&begin2!='0'&&begin2!='1'&&begin2!='2'&begin2!='3' ) lessonTime.begin.append(1);
        else if(begin == '2') lessonTime.begin.append(2);
        else if(begin == '3') lessonTime.begin.append(3);
        else if(begin == '4') lessonTime.begin.append(4);
        else if(begin == '5') lessonTime.begin.append(5);
        else if(begin == '6') lessonTime.begin.append(6);
        else if(begin == '7') lessonTime.begin.append(7);
        else if(begin == '8') lessonTime.begin.append(8);
        else if(begin == '9') lessonTime.begin.append(9);
        else if(begin == '1' && begin2 == '0') lessonTime.begin.append(10);
        else if(begin == '1' && begin2 == '1') lessonTime.begin.append(11);
        else if(begin == '1' && begin2 == '2') lessonTime.begin.append(12);
        else if(begin == '1' && begin2 == '3') lessonTime.begin.append(13);
        loc = workStr.indexOf('-'); //第一个'-'的后面就是结束时间
        QChar end = workStr.at(loc + 1);
        QChar end2 = workStr.at(loc + 2);
        if(end == '1'&&end2!='0'&&end2!='1'&&end2!='2'&end2!='3' ) lessonTime.end.append(1);
        else if(end == '2') lessonTime.end.append(2);
        else if(end == '3') lessonTime.end.append(3);
        else if(end == '4') lessonTime.end.append(4);
        else if(end == '5') lessonTime.end.append(5);
        else if(end == '6') lessonTime.end.append(6);
        else if(end == '7') lessonTime.end.append(7);
        else if(end == '8') lessonTime.end.append(8);
        else if(end == '9') lessonTime.end.append(9);
        else if(end == '1' && end2 == '0') lessonTime.end.append(10);
        else if(end == '1' && end2 == '1') lessonTime.end.append(11);
        else if(end == '1' && end2 == '2') lessonTime.end.append(12);
        else if(end == '1' && end2 == '3') lessonTime.end.append(13);
        loc = workStr.indexOf("<br/>");
        workStr.remove(0,loc + 5);
    }
    return lessonTime;
}
