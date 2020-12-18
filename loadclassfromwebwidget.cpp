#include "loadclassfromwebwidget.h"
#include "ui_loadclassfromwebwidget.h"

LoadClassFromWebWidget::LoadClassFromWebWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadClassFromWebWidget)
{
    ui->setupUi(this);
    Data *data=Data::getData();
    ui->spiderMsg->append(data->getCurrentTime()+"Loading...");
//    manager=new QNetworkAccessManager(this);
//    connect(manager,&QNetworkAccessManager::finished,this,&LoadClassFromWebWidget::ReplyFinished);
//    request=new QNetworkRequest();
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
    cgrade=QString::number(year-inputYearIndex);
    cterm=QString::number(inputSemesterIndex+1);
    qDebug()<<"cgrade:::"<<cgrade;
    //确定网址
    leUrl="http://elite.nju.edu.cn/jiaowu/student/teachinginfo/allCourseList.do?method=getCourseList&curTerm="
            +QString::number(year)+QString::number(inputSemesterIndex+1)+"&curSpeciality=&curGrade="+QString::number(year-inputYearIndex);
    qDebug()<<"URL::::"<<leUrl;
    //WebLogWidget *webLogWidget=new WebLogWidget();
    //webLogWidget->show();
    leCookie=data->cookie;
    if(!data->haveLoggedInSIMS) data->haveLoggedInSIMS=true;
    qDebug()<<"Cookie-->"<<leCookie;
    if(leUrl!=""&&leCookie!=""){//如果都没问题，就可以开始获取html了
        ui->spiderMsg->append(data->getCurrentTime()+"Begin request...");
        manager=new QNetworkAccessManager(this);
        connect(manager,&QNetworkAccessManager::finished,this,&LoadClassFromWebWidget::ReplyFinished);
        request=new QNetworkRequest();
        //浏览器伪装
        QString userAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.140 Safari/537.36 Edge/18.17763";
        QByteArray leCookieByte=leCookie.toUtf8();
        QList<QNetworkCookie> list;
        list.push_back(QNetworkCookie(leCookieByte));
        QVariant var;
        var.setValue(list);
        request->setUrl(QUrl(leUrl));
        request->setHeader(QNetworkRequest::ContentTypeHeader,"text/html, application/xhtml+xml, application/xml; q=0.9, */*; q=0.8");
        request->setHeader(QNetworkRequest::UserAgentHeader, userAgent);
        request->setHeader(QNetworkRequest::CookieHeader, var);
        //获取html
        manager->get(*request);
    }else{
        ui->spiderMsg->append(data->getCurrentTime()+"Geting url or cookie failed!");
    }
}

void LoadClassFromWebWidget::ReplyFinished(QNetworkReply *reply){
    //获取接收到的信息
    Data* data=Data::getData();
    qDebug()<<"gotHtml";
    ui->spiderMsg->append(data->getCurrentTime()+"Request successful!");
    ui->spiderMsg->append(data->getCurrentTime()+"Processing response information...");
    qApp->processEvents();
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
    Data* data=Data::getData();
    ui->spiderMsg->append(data->getCurrentTime()+"Extract relevant information...");
    qApp->processEvents();
    //确定正则表达式
    QRegExp re_beg(tr("课程信息"));
    QRegExp re_end(tr("</table>"));
    int index_beg = 0;
    int index_end = ori_lesson.size()-1;
    qDebug()<<"begin with "<<index_beg<<" || end with "<<index_end;
    QRegularExpression re("<!--p<tdpalign=\"center\"pvalign=\"middle\">(.*?)</td>p-->.*?le\">(.*?)</td>.*?le\">(.*?)</td>.*?le\">(.*?)</td>.*?le\">(.*?)</td>.*?le\">(.*?)</td>.*?le\">(.*?)</td>.*?le\">(.*?)</td>.*?le\">(.*?)</td>");
    QRegularExpressionMatch match;
    int count=0;
    DataQuery *iquery=DataQuery::getDataQuery();
    QString result;
    ui->spiderMsg->append(data->getCurrentTime()+"Import information into database...");
    qApp->processEvents();
    while(index_beg<index_end){
        match = re.match(ori_lesson,index_beg);
        if(match.hasMatch()){
            QString temp;
            QStringList teacher;
            QStringList courseBasicInsertParam;
            Lesson_time lt;
            for(int i=1;i<=9;i++){
                temp=match.captured(i);
                if(i==8){

                    teacher=data->getTeacherFromRawStr(temp);
                }else if(i==9){

                    lt=data->getLessonTimeFromRawStr(temp);
                }else if(i==5){
                    if(temp.size()>0){
                        courseBasicInsertParam.push_back(temp.at(0));
                    }else{
                        courseBasicInsertParam.push_back("NULL");
                    }
                }else{
                    if(temp.size()>0){
                        courseBasicInsertParam.push_back(temp);
                    }else{
                        courseBasicInsertParam.push_back("NULL");
                    }
                }
            }
            //插入院系
            result=iquery->insertDept(courseBasicInsertParam.at(3),"");
            qDebug()<<result;
            //插入课程表
            result=iquery->insertLesson(courseBasicInsertParam.at(0),courseBasicInsertParam.at(1),courseBasicInsertParam.at(2),courseBasicInsertParam.at(3),courseBasicInsertParam.at(4),this->cgrade);
            if(result=="") count++;
            qDebug()<<result;
            //插入教师
            for(int i=0;i<teacher.size();i++){
                QSqlQuery query;
                query.exec("select COUNT(tno) from Teacher");
                if(query.lastError().type()==QSqlError::NoError){
                    int teaNum=0;
                    if(query.next()){
                        teaNum=query.value(0).toInt();
                    }
                    qDebug()<<"------"<<teaNum;
                    //构建教师编号
                    QString tno=QString::number(teaNum);
                    if(tno.size()<4){
                        QString zero;
                        for(int j=0;j<4-tno.size();j++){
                            zero+="0";
                        }
                        tno=zero+tno;
                    }

                    //插入教师表
                    query.exec("select Tno from Teacher where Tname='"+teacher.at(i)+"' and Tdept='"+courseBasicInsertParam.at(3)+"'");
                    if(query.lastError().type()==QSqlError::NoError){
                        QString newTno=tno;
                        if(query.next()){ 
                            newTno=query.value(0).toString();
                        }else{
                            query.exec("insert into Teacher values('"+tno+"','"+teacher.at(i)+"','"+courseBasicInsertParam.at(3)+"')");
                            if(query.lastError().type()!=QSqlError::NoError) qDebug()<<query.lastError().text();
                        }
                        //插入教师教课表
                        query.exec("select * from Tcourse where Cno='"+courseBasicInsertParam.at(0)+"' and Tno='"+newTno+"' and Cterm="+cterm);
                        if(query.lastError().type()==QSqlError::NoError){
                            if(!query.next()){
                                query.exec("insert into Tcourse values('"+courseBasicInsertParam.at(0)+"','"+newTno+"',"+cterm+")");
                                if(query.lastError().type()!=QSqlError::NoError) qDebug()<<query.lastError().text();
                            }
                        }else{
                            QMessageBox::warning(this,"错误",query.lastError().text());
                            return;
                        }

                    }else{
                        QMessageBox::warning(this,"错误",query.lastError().text());
                        return;
                    }

                }else{
                    QMessageBox::warning(this,"错误",query.lastError().text());
                    return;
                }
            }
            //插入课程时间
            QSqlQuery query;
            query.exec("select * from CTime where Cno='"+courseBasicInsertParam.at(0)+"'");
            if(query.lastError().type()==QSqlError::NoError){
                if(!query.next()){
                    for(int i=0;i<lt.weekDay.size();i++){
                        query.exec("insert into CTime values('"+courseBasicInsertParam.at(0)+"',"+cterm+","+QString::number(lt.weekDay.at(i))+","+QString::number(lt.begin.at(i))+","+QString::number(lt.end.at(i))+")");
                        if(query.lastError().type()!=QSqlError::NoError) qDebug()<<query.lastError().text();
                    }
                }
            }else{
                QMessageBox::warning(this,"错误",query.lastError().text());
                return;
            }
//            for(int i=1;i<=9;i++){
//                temp=match.captured(i);
//                if(i==8){
//                    Data* data=Data::getData();
//                    QStringList list=data->getTeacherFromRawStr(temp);
//                    for(int j=0;j<list.size();j++) qDebug()<<list.at(j);
//                }else if(i==9){
//                    Data* data=Data::getData();
//                    Lesson_time lt=data->getLessonTimeFromRawStr(temp);
//                    for(int j=0;j<lt.weekDay.size();j++) qDebug()<<lt.weekDay.at(j)<<" "<<lt.begin.at(j)<<" "<<lt.end.at(j);
//                }else{
//                    qDebug()<<temp;
//                }
//            }
            index_beg = match.capturedEnd();        //记录目前匹配的位置
        }else{
            qDebug()<<"fail";//QString QStringList QVector<int>
            break;
        }
    }
    qDebug()<<"Regular done "<<count;
    ui->spiderMsg->append(data->getCurrentTime()+"Processing teacher information...");
    qApp->processEvents();
    QSqlQuery query;
    query.exec("select Tno from Teacher");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            QString tno=query.value(0).toString();
            QSqlQuery query2;
            qDebug()<<"tno----"<<tno;
            QStringList sqls;
            sqls<<"create login T"+tno+" with password='123456', default_database=E_Chain;";
            sqls<<"create user T"+tno+" for login T"+tno+" with default_schema=dbo";
            sqls<<"GRANT SELECT ON CourseBasic TO T"+tno+"";
            sqls<<"GRANT SELECT ON CTime TO T"+tno+"";
            sqls<<"GRANT SELECT ON Tcourse TO T"+tno+"";
            sqls<<"GRANT SELECT ON Stu_Cour TO T"+tno+"";
            sqls<<"GRANT SELECT ON Teacher TO T"+tno+"";
            sqls<<"GRANT SELECT,INSERT,DELETE ON ScholarAppli TO T"+tno+"";
            sqls<<"GRANT SELECT,INSERT,DELETE ON ScholarLst TO T"+tno+"";
            sqls<<"GRANT SELECT,INSERT,DELETE ON ProjectAppli TO T"+tno+"";
            sqls<<"GRANT SELECT,INSERT,DELETE ON ProjectLst TO T"+tno+"";
            sqls<<"GRANT SELECT ON Student TO T"+tno+"";
            sqls<<"GRANT SELECT,INSERT ON T2A TO T"+tno+"";
            sqls<<"CREATE VIEW T"+tno+"_Course AS SELECT Sno, Grade, Stu_Cour.Cno, Stu_Cour.Cterm FROM Stu_Cour, Tcourse WHERE Tcourse.Tno='"+tno+"' AND Tcourse.Cterm=Stu_Cour.Cterm AND Tcourse.Cno=Stu_Cour.Cno";
            sqls<<"GRANT SELECT, UPDATE(Grade) ON T"+tno+"_Course  TO T"+tno+"";
            sqls<<"CREATE VIEW T"+tno+"_T2A AS SELECT Rcontent, Response FROM T2A WHERE T2A.Tno='"+tno+"'";
            sqls<<"GRANT SELECT, UPDATE(Rcontent),INSERT  ON T"+tno+"_T2A TO T"+tno+"";
            sqls<<"CREATE VIEW T"+tno+"_TP AS SELECT Sno, ProjectName, Reason, Response FROM ProjectAppli, ProjectLst WHERE ProjectLst.Tno='"+tno+"' AND ProjectAppli.ProjectName=ProjectLst.ProgramName";
            sqls<<"GRANT SELECT, UPDATE(Response) ON T"+tno+"_TP TO T"+tno+"";

            QString res;
            for(int i=0;i<sqls.size();i++){
                query2.exec(sqls.at(i));
                if(query2.lastError().type()!=QSqlError::NoError){
                    qDebug()<<query2.lastError().text();
                }
            }
        }
    }else{
        QMessageBox::warning(this,"查询教师列表错误",query.lastError().text());
    }

    ui->spiderMsg->append(data->getCurrentTime()+"Successfully imported "+QString::number(count)+" courses");
}
