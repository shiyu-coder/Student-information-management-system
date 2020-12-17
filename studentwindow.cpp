#include "studentwindow.h"
#include "ui_studentwindow.h"

StudentWindow::StudentWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);
}

StudentWindow::~StudentWindow()
{
    delete ui;
}

void StudentWindow::on_FlushButton_2_clicked()
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

void StudentWindow::on_FlushButton_1_clicked()
{
    ui->MyLessonWidget->clearContents();
    ui->MyLessonWidget->setRowCount(0);
    //SELECT Sno_Course.Cno, Cname, Tname, Sno_Course.Cterm, Wday, Cbegin, Cend FROM Sno_Course, CourseBasic, CTime, Tcourse, Teacher WHERE Sno_Course.Cno=CourseBasic.Cno AND Sno_Course.Cno=Tcourse.Cno AND Sno_Course.Cterm=Tcourse.Cterm AND Sno_Course.Cno=CTime.Cno AND Sno_Course.Cterm=CTime.Cterm
    QSqlQuery query;
    Data* data=Data::getData();
    QString sno=data->sno;
    query.exec("SELECT S"+sno+"_Course.Cno, Cname, Tname, S"+sno+"_Course.Cterm, Wday, Cbegin, Cend FROM S"+sno+"_Course, CourseBasic, CTime, Tcourse, Teacher WHERE S"+sno+"_Course.Cno=CourseBasic.Cno AND S"+sno+"_Course.Cno=Tcourse.Cno AND S"+sno+"_Course.Cterm=Tcourse.Cterm AND S"+sno+"_Course.Cno=CTime.Cno AND S"+sno+"_Course.Cterm=CTime.Cterm");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            ui->MyLessonWidget->setRowCount(ui->MyLessonWidget->rowCount()+1);
            ui->MyLessonWidget->setItem(ui->MyLessonWidget->rowCount()-1,0,new QTableWidgetItem());
        }
    }else{
        QMessageBox::warning(this,"查询学生课程信息错误",query.lastError().text());
    }
}

void StudentWindow::on_FlushButton_3_clicked()
{
    ui->AppliedScholarWidget->clear();
    ui->AppliableScholarWidget->clear();
    QSqlQuery query;
    Data *data=Data::getData();
    query.exec("select * from ScholarLst where Scholarship not in(select Scholarship from ScholarAppli where Sno='"+data->sno+"')");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            ui->AppliableScholarWidget->addItem(query.value(0).toString()+"  金额："+query.value(2).toString()+"元"+"  介绍："+query.value(1).toString());
        }
    }else{
        QMessageBox::warning(this,"查询奖学金信息错误",query.lastError().text());
    }
    query.exec("select ScholarLst.Scholarship,Money,Response from S"+data->sno+"_Scho,ScholarLst where S"+data->sno+"_Scho.Scholarship=ScholarLst.Scholarship");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            QString res;
            QStringList resList;
            resList<<"不通过"<<"通过"<<"不可兼得"<<"未审核";
            res=resList.at(query.value(2).toInt());
            ui->AppliedScholarWidget->addItem(query.value(0).toString()+"  金额："+query.value(1).toString()+"元  状态："+res);
        }
    }else{
        QMessageBox::warning(this,"查询学生奖学金信息错误",query.lastError().text());
    }
}

void StudentWindow::on_FlushButton_4_clicked()
{
    ui->AppliedProWidget->clear();
    ui->AppliableProWidget->clear();
    QSqlQuery query;
    Data *data=Data::getData();
    query.exec("select ProgramName,Tname,ProIntro from ProjectLst,Teacher where Teacher.Tno=ProjectLst.Tno and ProgramName not in(select ProjectName from S"+data->sno+"_Pro)");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            ui->AppliableProWidget->addItem(query.value(0).toString()+"  辅导教师："+query.value(1).toString()+"  项目介绍："+query.value(2).toString());
        }
    }else{
        QMessageBox::warning(this,"查询大创项目信息失败",query.lastError().text());
    }
    query.exec("select ProjectName,Tname,Response from S"+data->sno+"_Pro,Teacher,ProjectLst where Teacher.Tno=ProjectLst.Tno and ProgramName=ProjectName");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            QString res;
            QStringList resList;
            resList<<"不通过"<<"通过"<<"不可兼得"<<"未审核";
            res=resList.at(query.value(2).toInt());
            ui->AppliedProWidget->addItem(query.value(0).toString()+"  辅导教师："+query.value(1).toString()+"  状态："+res);
        }
    }else{
        QMessageBox::warning(this,"查询学生大创项目信息失败",query.lastError().text());
    }
}
