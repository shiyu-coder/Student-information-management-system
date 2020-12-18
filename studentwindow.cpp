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
    query.exec("select CourseBasic.Cno,Cname,Cchar,Climit,Ccur,Cdept,Ccredit,Cgrade,Stu_Cour.Cterm from CourseBasic,Stu_Cour where CourseBasic.Cno=Stu_Cour.Cno and Stu_Cour.Sno='"+data->sno+"'");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){

            qDebug()<<query.value(0).toString();
            ui->MyLessonWidget->setRowCount(ui->MyLessonWidget->rowCount()+1);
            ui->MyLessonWidget->setItem(ui->MyLessonWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->MyLessonWidget->setItem(ui->MyLessonWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
            ui->MyLessonWidget->setItem(ui->MyLessonWidget->rowCount()-1,2,new QTableWidgetItem(query.value(2).toString()));
            QSqlQuery teaQuery;
            teaQuery.exec("select Tname from CourseBasic,Tcourse,Teacher where CourseBasic.Cno=Tcourse.Cno and Tcourse.Tno=Teacher.Tno and CourseBasic.Cno='"+query.value(0).toString()+"'");
            QString tea;
            if(teaQuery.lastError().type()==QSqlError::NoError){
                while(teaQuery.next()){
                    tea=tea+" "+teaQuery.value(0).toString();
                }
            }else{
                qDebug()<<teaQuery.lastError().text();
            }
            ui->MyLessonWidget->setItem(ui->MyLessonWidget->rowCount()-1,3,new QTableWidgetItem(tea));
            ui->MyLessonWidget->setItem(ui->MyLessonWidget->rowCount()-1,4,new QTableWidgetItem(query.value(3).toString()));
            ui->MyLessonWidget->setItem(ui->MyLessonWidget->rowCount()-1,5,new QTableWidgetItem(query.value(4).toString()));
            ui->MyLessonWidget->setItem(ui->MyLessonWidget->rowCount()-1,6,new QTableWidgetItem(query.value(5).toString()));
            ui->MyLessonWidget->setItem(ui->MyLessonWidget->rowCount()-1,7,new QTableWidgetItem(query.value(6).toString()));
            ui->MyLessonWidget->setItem(ui->MyLessonWidget->rowCount()-1,8,new QTableWidgetItem(query.value(7).toString()));
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

            ui->MyLessonWidget->setItem(ui->MyLessonWidget->rowCount()-1,9,new QTableWidgetItem(time));
        }
    }else{
        QMessageBox::warning(this,"查询课程信息错误",query.lastError().text());
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

void StudentWindow::on_ApplyScholarButton_clicked()
{
    QList<QListWidgetItem*> items = ui->AppliableScholarWidget->selectedItems();
    if(items.size()<=0){
        QMessageBox::warning(this,"错误","您没有选中任何奖学金！");
    }else{
        QString content=items.at(0)->text();
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
        ApplyScholarWidget *widget=new ApplyScholarWidget();
        widget->setMsg(name);
        widget->show();

    }

}

void StudentWindow::on_actionAbout_triggered()
{
    AboutWidget *widget=new AboutWidget();
    widget->show();
}

void StudentWindow::on_ChooseLessonButton_clicked()
{
    QList<QTableWidgetItem*> items = ui->LessonWidget->selectedItems();
    if(items.size()<=0){
        QMessageBox::warning(this,"错误","您没有选中任何课程！");
    }else{
        QSqlQuery query;
        QString res;
        for(int i=0;i<items.size();i++){
            int index=ui->LessonWidget->row(items.at(i));
            if(ui->LessonWidget->item(index,5)->text().toInt()>=ui->LessonWidget->item(index,4)->text().toInt()){
                res+="课程："+ui->LessonWidget->item(index,1)->text()+" 已达到最大人数！/n";
            }else{
                Data *data=Data::getData();
                QString term;
                if(ui->LessonWidget->item(index,9)->text()=="第一学期") term="1";
                else term="2";
                query.exec("insert into Stu_Cour values('"+data->sno+"','"+ui->LessonWidget->item(index,0)->text()+"','"+term+"',"+ui->LessonWidget->item(index,8)->text()+"); update CourseBasic set Ccur=Ccur+1 where Cno='"+ui->LessonWidget->item(index,0)->text()+"'");
                if(query.lastError().type()==QSqlError::NoError){

                }else{
                    res+=query.lastError().text();
                }
            }
        }
        if(res==""){
            QMessageBox::information(this,"选择课程","选择课程成功！");

        }else{
            QMessageBox::warning(this,"选择课程",res);
        }
    }
}

void StudentWindow::on_ApplyProButton_clicked()
{
    QList<QListWidgetItem*> items=ui->AppliableProWidget->selectedItems();
    if(items.size()<=0){
        QMessageBox::warning(this,"错误","您没有选中任何大创项目！");
    }else{
        ApplyProWidget *widget=new ApplyProWidget();
        int index=ui->AppliableProWidget->row(items.at(0));
        QString name;
        QString res=ui->AppliableProWidget->item(index)->text();
        for(int i=0;i<=res.size();i++){
            if(res.at(i)==' ') break;
            else{
                name=name+res.at(i);
            }
        }
        widget->setName(name);
        widget->show();
    }
}

void StudentWindow::on_AddApplyButton_clicked()
{
    AddMsgWidget *widget=new AddMsgWidget();
    widget->show();
}

void StudentWindow::on_FlushButton_5_clicked()
{
    ui->MsgWidget->clear();
    QSqlQuery query;
    Data* data=Data::getData();
    query.exec("select Rcontent,Response from S2A where Sno='"+data->sno+"'");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            ui->MsgWidget->addItem(query.value(0).toString()+" 回复："+query.value(1).toString());
        }
    }else{
        QMessageBox::warning(this,"查询待处理信息错误",query.lastError().text());
    }
}

void StudentWindow::on_DeleteLessonButton_clicked()
{
    QList<QTableWidgetItem*> items=ui->MyLessonWidget->selectedItems();
    if(items.size()<=0){
        QMessageBox::warning(this,"错误","您没有选中任何课程");
    }else{
        QSqlQuery query;
        QString res;
        for(int i=0;i<items.size();i++){
            int index=ui->MyLessonWidget->row(items.at(i));
            QString cno=ui->MyLessonWidget->item(index,0)->text();
            Data *data=Data::getData();
            query.exec("delete from Stu_Cour where Cno='"+cno+"' and Sno='"+data->sno+"' update CourseBasic set Ccur=Ccur-1 where Cno='"+cno+"'");
            if(query.lastError().type()!=QSqlError::NoError) res+=query.lastError().text();
        }
        if(res==""){
            QMessageBox::information(this,"退选课程","退选课程成功");
        }
        else QMessageBox::warning(this,"退选课程错误",res);
    }
}
