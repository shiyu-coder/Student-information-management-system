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
