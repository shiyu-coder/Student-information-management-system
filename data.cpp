#include "data.h"

Data::Data()
{
}

Data* Data::getData(){
    static Data* data_ptr=nullptr;
    if(data_ptr==nullptr){
        data_ptr=new Data();
    }
    return data_ptr;
}

QString Data::getCurrentTime(){
    QDateTime dateTime(QDateTime::currentDateTime());
    QString time = dateTime.toString("[yyyy-MM-dd hh:mm:ss] ");
    return time;
}
