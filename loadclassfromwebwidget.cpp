#include "loadclassfromwebwidget.h"
#include "ui_loadclassfromwebwidget.h"

LoadClassFromWebWidget::LoadClassFromWebWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadClassFromWebWidget)
{
    ui->setupUi(this);
    Data *data=Data::getData();
    ui->spiderMsg->append(data->getCurrentTime()+"Loading...");
    manager=new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,&LoadClassFromWebWidget::ReplyFinished);
    ui->spiderMsg->append(data->getCurrentTime()+"Ready");
    QApplication::setQuitOnLastWindowClosed(true);
}

LoadClassFromWebWidget::~LoadClassFromWebWidget()
{
    delete ui;
}

void LoadClassFromWebWidget::on_getLessonButton_clicked()
{
    //先获取学年，学期信息
    Data* data=Data::getData();
    int inputYearIndex=ui->yearBox->currentIndex();
    int inputSemesterIndex=ui->semesterBox->currentIndex();
    QDate date(QDate::currentDate());
    int year = date.year();
    int month=date.month();
    if(month<=6){//如果是上半年，则课表是去年的
        year--;
    }
    //确定网址
    leUrl="http://elite.nju.edu.cn/jiaowu/student/teachinginfo/allCourseList.do?method=getCourseList&curTerm="
            +QString::number(year)+QString::number(inputSemesterIndex+1)+"&curSpeciality=&curGrade="+QString::number(year-inputYearIndex);
    qDebug()<<"URL::::"<<leUrl;
    //WebLogWidget *webLogWidget=new WebLogWidget();
    //webLogWidget->show();

    leCookie=data->cookie;
    qDebug()<<"Cookie-->"<<leCookie;
    if(leUrl!=""&&leCookie!=""){//如果都没问题，就可以开始获取html了
        ui->spiderMsg->append(data->getCurrentTime()+"Begin request...");
        //浏览器伪装
        QString userAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.140 Safari/537.36 Edge/18.17763";
        QByteArray leCookieByte=leCookie.toUtf8();
        QList<QNetworkCookie> list;
        list.push_back(QNetworkCookie(leCookieByte));
        QVariant var;
        var.setValue(list);
        request.setUrl(QUrl(leUrl));
        request.setHeader(QNetworkRequest::ContentTypeHeader,"text/html, application/xhtml+xml, application/xml; q=0.9, */*; q=0.8");
        request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);
        request.setHeader(QNetworkRequest::CookieHeader, var);
        //获取html
        manager->get(request);
    }else{
        ui->spiderMsg->append(data->getCurrentTime()+"Geting url or cookie failed!");
    }
}

void LoadClassFromWebWidget::ReplyFinished(QNetworkReply *reply){
    //获取接收到的信息
    Data* data=Data::getData();
    qDebug()<<"gotHtml";
    ori_lesson=reply->readAll();
    ori_lesson.replace('\n','p');
    ori_lesson.replace(' ','p');
    ori_lesson.replace('\t','p');
    QFile out_file("result.txt");
    if(out_file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&out_file);
        out<<ori_lesson;
    }
    if(ori_lesson!=""){
        getLessonMsgFromHtml();
    }else{
        ui->spiderMsg->append(data->getCurrentTime()+"Lesson information request failed!");
    }
}

void LoadClassFromWebWidget::getLessonMsgFromHtml(){
    qDebug()<<"Begin regular";
    //确定正则表达式
    QRegExp re_beg(tr("课程信息"));
    QRegExp re_end(tr("</table>"));
    int index_beg = 0;
    int index_end = ori_lesson.size()-1;
    qDebug()<<"begin with "<<index_beg<<" || end with "<<index_end;
    QRegularExpression re("<!--p<tdpalign=\"center\"pvalign=\"middle\">(.*?)</td>p-->.*?le\">(.*?)</td>.*?le\">(.*?)</td>.*?le\">(.*?)</td>.*?le\">(.*?)</td>.*?le\">(.*?)</td>.*?le\">(.*?)</td>.*?le\">(.*?)</td>.*?le\">(.*?)</td>");
    QRegularExpressionMatch match;
    int count=0;
    while(index_beg<index_end){
        match = re.match(ori_lesson,index_beg);
        if(match.hasMatch()){
            QString temp;
            for(int i=1;i<=9;i++){
                temp=match.captured(i);
                if(i==8){
                    Data* data=Data::getData();
                    QStringList list=data->getTeacherFromRawStr(temp);
                    for(int i=0;i<list.size();i++) qDebug()<<list.at(i);
                }else if(i==9){
                    Data* data=Data::getData();
                    Lesson_time lt=data->getLessonTimeFromRawStr(temp);
                    for(int i=0;i<lt.weekDay.size();i++) qDebug()<<lt.weekDay.at(i)<<" "<<lt.begin.at(i)<<" "<<lt.end.at(i);
                }else{
                    qDebug()<<temp;
                }
            }
            count++;
            index_beg = match.capturedEnd();        //记录目前匹配的位置
        }else{
            qDebug()<<"fail";//QString QStringList QVector<int>
            break;
        }
    }
    qDebug()<<"Regular done "<<count;
}
