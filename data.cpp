#include "data.h"

Data::Data()
{

}

void Data::getFundMsgFromApi(QVector<QString> Keys){
    QEventLoop loop;
    QString httpString="https://api.doctorxiong.club/v1/fund?code=";
    if(Keys.size()>0) httpString+=Keys.at(0);
    for(int i=1;i<Keys.size();i++){
        httpString+=","+Keys.at(i);
    }
    QNetworkAccessManager manager;
    QNetworkReply *networkReply=manager.get(QNetworkRequest(QUrl(httpString)));
    connect(networkReply,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();
    QByteArray fundByte=networkReply->readAll();
    QString fundString=fundString.fromUtf8(fundByte.data());
    qDebug()<<fundString;
}
