#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    QApplication::setQuitOnLastWindowClosed(true);
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
    on_FlushButton_clicked();
    on_FlushButton_2_clicked();
    on_FlushButton_3_clicked();
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
    WebLogWidget *webLogWidget=new WebLogWidget();
    webLogWidget->show();
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
