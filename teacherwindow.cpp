#include "teacherwindow.h"
#include "ui_teacherwindow.h"

TeacherWindow::TeacherWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TeacherWindow)
{
    ui->setupUi(this);
}

TeacherWindow::~TeacherWindow()
{
    delete ui;
}

void TeacherWindow::on_actionAbout_triggered()
{
    AboutWidget *widget=new AboutWidget();
    widget->show();
}

void TeacherWindow::on_AddProButton_clicked()
{
    AddProWidget *widget=new AddProWidget();
    widget->show();

}

void TeacherWindow::on_FlushButton_3_clicked()
{
    ui->ProWidget->clear();
    QSqlQuery query;
    Data* data=Data::getData();
    query.exec("select ProgramName,ProIntro from ProjectLst where Tno='"+data->tno+"'");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            QString res=query.value(0).toString()+"  介绍："+query.value(1).toString();
            ui->ProWidget->addItem(res);
        }
    }else{
        QMessageBox::warning(this,"查询大创项目信息错误",query.lastError().text());
    }
}

void TeacherWindow::on_FlushButton_1_clicked()
{
    ui->LessonWidget->clearContents();
    ui->LessonWidget->setRowCount(0);
    Data *data=Data::getData();
    QString tno=data->tno;
    QSqlQuery query;
    query.exec("select CourseBasic.Cno,Cname,Cchar,Climit,Ccur,Cdept,Ccredit,Cgrade,Cterm from CourseBasic,Tcourse where CourseBasic.Cno=Tcourse.Cno and Tcourse.Tno='"+tno+"'");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            ui->LessonWidget->setRowCount(ui->LessonWidget->rowCount()+1);
            ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
            ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,2,new QTableWidgetItem(query.value(2).toString()));
            ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,3,new QTableWidgetItem(query.value(3).toString()));
            ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,4,new QTableWidgetItem(query.value(4).toString()));
            ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,5,new QTableWidgetItem(query.value(5).toString()));
            ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,6,new QTableWidgetItem(query.value(6).toString()));
            ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,7,new QTableWidgetItem(query.value(7).toString()));
            ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,8,new QTableWidgetItem(query.value(8).toString()));
            QSqlQuery timeQuery;
            timeQuery.exec("select Wday,Cbegin,Cend from CTime where Cno='"+query.value(0).toString()+"' and Cterm='"+query.value(8).toString()+"'");
            QString time;
            QStringList timeThansfer;
            timeThansfer<<"一"<<"二"<<"三"<<"四"<<"五"<<"六"<<"日";
            if(timeQuery.lastError().type()==QSqlError::NoError){
                while(timeQuery.next()){
                    time+="周"+timeThansfer.at(timeQuery.value(0).toInt())+" 第"+timeQuery.value(1).toString()+"-"+timeQuery.value(2).toString()+"节 ";
                }
            }else{
                QMessageBox::warning(this,"查询课程时间信息错误",timeQuery.lastError().text());
            }

            ui->LessonWidget->setItem(ui->LessonWidget->rowCount()-1,9,new QTableWidgetItem(time));
        }
    }else{
        QMessageBox::warning(this,"查询课程信息错误",query.lastError().text());
    }
}

void TeacherWindow::on_FlushButton_2_clicked()
{
    ui->StudentLessonBox->clear();
    QSqlQuery query;
    Data* data=Data::getData();
    query.exec("select Cname from Tcourse,CourseBasic where Tcourse.Cno=CourseBasic.Cno and Tno='"+data->tno+"'");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            ui->StudentLessonBox->addItem(query.value(0).toString());
        }
    }
    QString cur=ui->StudentLessonBox->currentText();
    on_StudentLessonBox_currentIndexChanged(cur);
}

void TeacherWindow::on_FlushButton_4_clicked()
{
    ui->MsgWidget->clear();
    QSqlQuery query;
    Data* data=Data::getData();
    query.exec("select Rcontent,Response from T2A where Tno='"+data->tno+"'");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            ui->MsgWidget->addItem(query.value(0).toString()+" 回复："+query.value(1).toString());
        }
    }else{
        QMessageBox::warning(this,"查询待处理信息错误",query.lastError().text());
    }

}

void TeacherWindow::on_StudentLessonBox_currentIndexChanged(const QString &arg1)
{
    ui->StudentWidget->clearContents();
    ui->StudentWidget->setRowCount(0);
    QSqlQuery query;
    query.exec("select CourseBasic.Cno,Cname,Ssex,Sdept,Sgrade from Student,Stu_Cour,CourseBasic where CourseBasic.Cno=Stu_Cour.Cno and Stu_Cour.Sno=Student.Sno and Cname='"+arg1+"'");
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

void TeacherWindow::on_AddApplyButton_clicked()
{
    AddMsgWidget *widget=new AddMsgWidget();
    widget->show();
}
