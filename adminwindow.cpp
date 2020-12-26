#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    QApplication::setQuitOnLastWindowClosed(true);

//    pd=new QProgressDialog("初始化...","取消",0,100,this);
//    pd->setWindowModality(Qt::WindowModal);
//    pd->setMinimumDuration(5);
//    pd->setWindowTitle("请稍后");
//    pd->setFixedWidth(300);
//    pd->setValue(currentValue);
//    pd->show();
//    timer=new QTimer(this);
//    connect(timer,SIGNAL(timeout()),this,SLOT(updateProgressDialog()));
//    timer->start(100);

    //Data* data=Data::getData();
    //ui->MsgBoard->append(data->getCurrentTime()+"管理员登录成功");
    //登陆后首先需要连接数据库
    DataQuery *query=DataQuery::getDataQuery();
    QString result=query->connectToDatabase("sa","9638527410.s");
    if(result==""){
        //QMessageBox::information(this,"连接到数据库","数据库连接成功！");
    }else{
        QMessageBox::warning(this,"连接到数据库",result);
    }


//    timer->stop();//停止定时器
//    if(currentValue != 100)
//        currentValue = 100;
//    pd->setValue(currentValue);//进度达到最大值
//    delete pd;//关闭进度对话框
}

void AdminWindow::updateProgressDialog(){
    currentValue++;
    if( currentValue == 100 )
        currentValue = 0;
    pd ->setValue(currentValue);
    QCoreApplication::processEvents();//避免界面冻结
    if(pd->wasCanceled())
        pd->setHidden(true);//隐藏对话框
}


AdminWindow::~AdminWindow()
{
    delete ui;
}
//导入课程触发函数
void AdminWindow::on_actionLoadClassFromWeb_triggered()
{
    LoadClassFromWebWidget *loadWidget=new LoadClassFromWebWidget();
    loadWidget->show();
    Data *data=Data::getData();
    if(!data->haveLoggedInSIMS){
        WebLogWidget *webLogWidget=new WebLogWidget();
        webLogWidget->show();
    }
}

void AdminWindow::closeEvent(QCloseEvent *event){
    qApp->quit();
    event->accept();
}


void AdminWindow::on_actionInit_triggered()
{
    DataQuery *query=DataQuery::getDataQuery();
    if(!query->databaseOnline){
        ConnectDabaseWidget *cdwidget=new ConnectDabaseWidget();
        cdwidget->show();
    }else{
        QString result=query->init();
        QMessageBox::information(this,"数据库初始化",result);
    }
}

void AdminWindow::on_actionAbout_triggered()
{
    AboutWidget *aboutwidget=new AboutWidget();
    aboutwidget->show();
}

void AdminWindow::on_actionDeptManagement_triggered()
{
    DeptWidget *deptwdiget=new DeptWidget();
    deptwdiget->show();
}

void AdminWindow::on_actionDatabaseRenew_triggered()
{
    QSqlQuery query;
    query.exec("drop table S2A;drop table T2A;drop table Systbl;drop table ScholarAppli;drop table ScholarLst;drop table ProjectAppli;drop table ProjectLst;drop table CTime;drop table Tcourse;drop table Teacher;drop table Stu_Cour;drop table CourseBasic;drop table Student;drop table Dept");
    if(query.lastError().type()==QSqlError::NoError){
        QMessageBox::information(this,"数据库重置","数据库重置成功！");
    }else{
        QMessageBox::warning(this,"错误",query.lastError().text());
    }

}

void AdminWindow::on_FlushButton_clicked()
{
    ui->LessonWidget->clearContents();
    ui->LessonWidget->setRowCount(0);
    QSqlQuery query;
    query.exec("select * from CourseBasic");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
//            ui->DeptMsgWidget->setRowCount(ui->DeptMsgWidget->rowCount()+1);
//            ui->DeptMsgWidget->setItem(ui->DeptMsgWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            QString teacher1,teacher2;
            Lesson_time lt1,lt2;
            bool term1=false,term2=false;
//            ui->LessonWidget->setRowCount(ui->LessonWidget->rowCount()+1);
//            ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
//            ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
            QSqlQuery teacherQuery;
            teacherQuery.exec("select Cterm,Tname from Tcourse,Teacher where Tcourse.Tno=Teacher.Tno and Cno='"+query.value(0).toString()+"'");
            if(teacherQuery.lastError().type()==QSqlError::NoError){
                while(teacherQuery.next()){
                    if(teacherQuery.value(0).toInt()==1){
                        term1=true;
                        teacher1+=teacherQuery.value(1).toString()+" ";
                    }else if(teacherQuery.value(0).toInt()==2){
                        term2=true;
                        teacher2+=teacherQuery.value(1).toString()+" ";
                    }
                }
            }else{
                QMessageBox::warning(this,"错误",teacherQuery.lastError().text());
                return;
            }
            QSqlQuery ltQuery;
            ltQuery.exec("select * from CTime where Cno='"+query.value(0).toString()+"'");
            if(ltQuery.lastError().type()==QSqlError::NoError){
                while(ltQuery.next()){
                    if(ltQuery.value(1).toInt()==1){
                        term1=true;
                        lt1.weekDay.push_back(ltQuery.value(2).toInt());
                        lt1.begin.push_back(ltQuery.value(3).toInt());
                        lt1.end.push_back(ltQuery.value(4).toInt());
                    }else if(ltQuery.value(1).toInt()==2){
                        term2=true;
                        lt2.weekDay.push_back(ltQuery.value(2).toInt());
                        lt2.begin.push_back(ltQuery.value(3).toInt());
                        lt2.end.push_back(ltQuery.value(4).toInt());
                    }
                }
            }else{
                QMessageBox::warning(this,"错误",ltQuery.lastError().text());
                return;
            }
            //开始展示课程
            QStringList timeThansfer;
            timeThansfer<<"一"<<"二"<<"三"<<"四"<<"五"<<"六"<<"日";
            //updateProgress();
            if(term1){
                //处理课程时间
                QString time;
                for(int i=0;i<lt1.weekDay.size();i++){
                    time+="周"+timeThansfer.at(lt1.weekDay.at(i)-1)+"第"+QString::number(lt1.begin.at(i))+"-"+QString::number(lt1.end.at(i))+"节 ";
                }
                //显示课程
                ui->LessonWidget->setRowCount(ui->LessonWidget->rowCount()+1);
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,2,new QTableWidgetItem(query.value(4).toString()));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,3,new QTableWidgetItem(teacher1));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,4,new QTableWidgetItem(query.value(2).toString()));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,5,new QTableWidgetItem(query.value(3).toString()));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,6,new QTableWidgetItem(query.value(5).toString()));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,7,new QTableWidgetItem(query.value(6).toString()));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,8,new QTableWidgetItem(query.value(7).toString()));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,9,new QTableWidgetItem("第一学期"));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,10,new QTableWidgetItem(time));
            }
            if(term2){
                //处理课程时间
                QString time;
                for(int i=0;i<lt2.weekDay.size();i++){
                    time+="周"+timeThansfer.at(lt2.weekDay.at(i)-1)+"第"+QString::number(lt2.begin.at(i))+"-"+QString::number(lt2.end.at(i))+"节 ";
                }
                //显示课程
                ui->LessonWidget->setRowCount(ui->LessonWidget->rowCount()+1);
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,2,new QTableWidgetItem(query.value(4).toString()));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,3,new QTableWidgetItem(teacher2));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,4,new QTableWidgetItem(query.value(2).toString()));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,5,new QTableWidgetItem(query.value(3).toString()));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,6,new QTableWidgetItem(query.value(5).toString()));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,7,new QTableWidgetItem(query.value(6).toString()));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,8,new QTableWidgetItem(query.value(7).toString()));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,9,new QTableWidgetItem("第二学期"));
                ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,10,new QTableWidgetItem(time));
            }
        }
    }else{
        QMessageBox::warning(this,"查询全校课程错误",query.lastError().text());
    }
}

void AdminWindow::on_FlushButton_2_clicked()
{
    ui->TeacherWidget->clearContents();
    ui->TeacherWidget->setRowCount(0);
    QSqlQuery query;
    query.exec("select * from Teacher");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            //updateProgress();
            ui->TeacherWidget->setRowCount(ui->TeacherWidget->rowCount()+1);
            ui->TeacherWidget->setItem(ui->TeacherWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->TeacherWidget->setItem(ui->TeacherWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
            ui->TeacherWidget->setItem(ui->TeacherWidget->rowCount()-1,2,new QTableWidgetItem(query.value(2).toString()));
        }
    }else{
        QMessageBox::warning(this,"查询教师信息错误",query.lastError().text());
    }
}

void AdminWindow::on_AddStudentButton_clicked()
{
    AddStuWidget* addstuwidget=new AddStuWidget();
    addstuwidget->show();
}

void AdminWindow::on_FlushButton_3_clicked()
{
    ui->StudentWidget->clearContents();
    ui->StudentWidget->setRowCount(0);
    QSqlQuery query;
    query.exec("select * from Student");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            //updateProgress();
            ui->StudentWidget->setRowCount(ui->StudentWidget->rowCount()+1);
            ui->StudentWidget->setItem(ui->StudentWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->StudentWidget->setItem(ui->StudentWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
            ui->StudentWidget->setItem(ui->StudentWidget->rowCount()-1,2,new QTableWidgetItem(query.value(2).toString()));
            ui->StudentWidget->setItem(ui->StudentWidget->rowCount()-1,3,new QTableWidgetItem(query.value(3).toString()));
            ui->StudentWidget->setItem(ui->StudentWidget->rowCount()-1,4,new QTableWidgetItem(query.value(4).toString()));
        }
    }else{
        QMessageBox::warning(this,"查询学生信息错误",query.lastError().text());
    }
}

void AdminWindow::on_AddLessonButton_2_clicked()
{
    AddTeacherWidget* widget=new AddTeacherWidget();
    widget->show();
}

void AdminWindow::on_FlushButton_4_clicked()
{
    ui->ScholarshipWidget->clear();
    QSqlQuery query;
    query.exec("select * from ScholarLst");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            QSqlQuery examQuery;
            examQuery.exec("select * from ScholarAppli where Scholarship='"+query.value(0).toString()+"' and Response='3'");
            if(examQuery.lastError().type()==QSqlError::NoError){
                if(examQuery.next()){
                    ui->ScholarshipWidget->addItem("* "+query.value(0).toString()+"  金额："+query.value(2).toString()+"元"+"  介绍："+query.value(1).toString());
                }else{
                    ui->ScholarshipWidget->addItem(query.value(0).toString()+"  金额："+query.value(2).toString()+"元"+"  介绍："+query.value(1).toString());
                }
            }else{
                QMessageBox::warning(this,"查询奖学金申请信息错误",examQuery.lastError().text());
            }

        }
    }else{
        QMessageBox::warning(this,"查询奖学金错误",query.lastError().text());
    }
}

void AdminWindow::setProgressDialog(QProgressDialog * pd_){
    this->pd=pd_;
}

void AdminWindow::updateProgress(){
    if(pd){
        if(pd->value()==pd->maximum()){
            pd->setValue(0);
        }else{
            pd->setValue(pd->value()+1);
        }
    }
}

void AdminWindow::on_toolButton_26_clicked()
{
    AddScholarWidget *widget=new AddScholarWidget();
    widget->show();
}

void AdminWindow::on_ScholarshipWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString content=item->text();
    QString name;
    for(int i=0;i<content.size();i++){
        if(content.at(i)==' '){
            break;
        }else if(content.at(i)=='*'){
            i++;
        }
        else{
            name+=content.at(i);
        }
    }
    ScholarMsgWidget *widget=new ScholarMsgWidget();
    widget->setName(name);
    widget->flush();
    widget->show();
}

void AdminWindow::on_ModifyTeacherButton_clicked()
{
    QList<QTableWidgetItem*> items = ui->TeacherWidget->selectedItems();
    if(items.size()<=0){
        QMessageBox::warning(this,"错误","您没有选中任何教师！");
    }else{
        int rowIndex=ui->TeacherWidget->row(items.at(0));
        QString tno=ui->TeacherWidget->item(rowIndex,0)->text();
        QString tname=ui->TeacherWidget->item(rowIndex,1)->text();
        QString dept=ui->TeacherWidget->item(rowIndex,2)->text();
        ModifyTeacherWidget *widget=new ModifyTeacherWidget();
        widget->setTno(tno,tname,dept);
        widget->flush();
        widget->show();
    }
}

void AdminWindow::on_FlushButton_5_clicked()
{
    ui->MsgWidget->clear();
    QSqlQuery query;
    query.exec("select Sname,Rcontent,Response from S2A,Student where S2A.Sno=Student.Sno");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            ui->MsgWidget->addItem("学生："+query.value(0).toString()+"  内容:"+query.value(1).toString()+" 回复："+query.value(2).toString());
        }
    }else{
        QMessageBox::warning(this,"查询待处理信息错误",query.lastError().text());
    }
    query.exec("select Tname,Rcontent,Response from T2A,Teacher where T2A.Tno=Teacher.Tno");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            ui->MsgWidget->addItem("教师："+query.value(0).toString()+" 内容:"+query.value(1).toString()+" 回复："+query.value(2).toString());
        }
    }else{
        QMessageBox::warning(this,"查询待处理信息错误",query.lastError().text());
    }
}

void AdminWindow::on_MsgWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ModifyApplyWidget* widget=new ModifyApplyWidget();
    QString content="";
    int i=0;
    for(;i<item->text().size();i++){
        if(item->text().at(i)==':'){
            i++;
            break;
        }
    }
    for(;i<item->text().size();i++){
        if(item->text().at(i)==' ') break;
        else{
            content+=item->text().at(i);
        }
    }
    qDebug()<<content;
    widget->setContent(content);
    widget->show();
}

void AdminWindow::on_toolButton_27_clicked()
{
    QList<QListWidgetItem*> items=ui->ScholarshipWidget->selectedItems();
    if(items.size()<=0){
        QMessageBox::warning(this,"错误","您没有选中任何奖学金！");

    }else{
        QSqlQuery query;
        for(int i=0;i<items.size();i++){
            QString name;
            QString con=items.at(i)->text();
            for(int j=0;j<con.size();j++){
                if(con.at(j)=='*') j++;
                else if(con.at(j)==' ') break;
                else name+=con.at(j);
            }
            query.exec("delete from ScholarLst where Scholarship='"+name+"' delete from ScholarAppli where Scholarship='"+name+"'");
            if(query.lastError().type()==QSqlError::NoError){
                QMessageBox::information(this,"删除奖学金","删除奖学金成功！");
            }else{
                QMessageBox::warning(this,"错误",query.lastError().text());
            }
        }
    }
}

void AdminWindow::on_ModifyStudentButton_clicked()
{
    ModifyStuWidget *widget=new ModifyStuWidget();
    QList<QTableWidgetItem*> items=ui->StudentWidget->selectedItems();
    if(items.size()<=0){
        QMessageBox::warning(this,"错误","您没有选中任何学生！");
    }else{
        int index=ui->StudentWidget->row(items.at(0));
        widget->setMsg(ui->StudentWidget->item(index,0)->text(),ui->StudentWidget->item(index,1)->text(),ui->StudentWidget->item(index,2)->text(),ui->StudentWidget->item(index,3)->text(),ui->StudentWidget->item(index,4)->text());
        widget->show();
    }
}

void AdminWindow::on_FindLessonButton_clicked()
{
    QList<QTableWidgetItem*> items=ui->LessonWidget->selectedItems();
    if(items.size()<=0){
        QMessageBox::warning(this,"错误","您没有选中任何课程！");
    }else{
        QString res;
        QSqlQuery query;
        for(int i=0;i<items.size();i++){
            int index=ui->LessonWidget->row(items.at(i));
            query.exec("delete from CourseBasic where Cno='"+ui->LessonWidget->item(index,0)->text()+"'");
            if(query.lastError().text()!=QSqlError::NoError){
                res+=query.lastError().text();
            }
        }
        if(res==""){
            QMessageBox::warning(this,"删除课程","删除课程成功！");
        }else{
            QMessageBox::information(this,"删除课程",res);
        }

    }
}

void AdminWindow::on_DeleteTeacherButton_clicked()
{
    QList<QTableWidgetItem*> items=ui->TeacherWidget->selectedItems();
    if(items.size()<=0){
        QMessageBox::warning(this,"错误","您没有选中任何学生！");
    }else{
        QString res;
        QSqlQuery query;
        for(int i=0;i<items.size();i++){
            int index=ui->TeacherWidget->row(items.at(i));
            query.exec("delete from Teacher where Tno='"+ui->TeacherWidget->item(index,0)->text()+"'");
            if(query.lastError().type()!=QSqlError::NoError){
                res+=query.lastError().text();
            }
        }
        if(res==""){
            QMessageBox::information(this,"删除教师","删除教师成功！");
        }else{
            QMessageBox::warning(this,"删除教师",query.lastError().text());
        }
    }
}

void AdminWindow::on_DeleteStudentButton_clicked()
{
    QList<QTableWidgetItem*> items=ui->StudentWidget->selectedItems();
    if(items.size()<=0){
        QMessageBox::warning(this,"错误","您没有选中任何学生！");
    }else{
        QString res;
        QSqlQuery query;
        for(int i=0;i<items.size();i++){
            int index=ui->StudentWidget->row(items.at(i));
            query.exec("delete from Student where Sno='"+ui->StudentWidget->item(index,0)->text()+"'");
            if(query.lastError().type()!=QSqlError::NoError){
                res+=query.lastError().text();
            }
        }
        if(res==""){
            QMessageBox::information(this,"删除学生","删除学生成功！");
        }else{
            QMessageBox::warning(this,"删除学生",query.lastError().text());
        }
    }
}
