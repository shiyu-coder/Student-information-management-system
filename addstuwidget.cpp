#include "addstuwidget.h"
#include "ui_addstuwidget.h"

AddStuWidget::AddStuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddStuWidget)
{
    ui->setupUi(this);
    QSqlQuery query;
    query.exec("select Dname from Dept");
    if(query.lastError().type()==QSqlError::NoError){
        QStringList depts;
        while(query.next()){
            depts<<query.value(0).toString();
        }
        ui->DeptBox->addItems(depts);
    }else{
        QMessageBox::warning(this,"查询院系信息错误",query.lastError().text());
    }
    QStringList sexes;
    sexes<<"男"<<"女";
    ui->SexBox->addItems(sexes);
    QStringList grades;
    QDate date(QDate::currentDate());
    int year = date.year();
    int month=date.month();
    if(month<=6){//如果是上半年，则课表是去年的
        year--;
    }
    for(int i=0;i<=3;i++){
        grades<<QString::number(year-i);
    }
    ui->GradeBox->addItems(grades);
}

AddStuWidget::~AddStuWidget()
{
    delete ui;
}

void AddStuWidget::on_QuitButton_clicked()
{
    this->close();
}

void AddStuWidget::on_ConfirmButton_clicked()
{
    QStringList info;
    QSqlQuery query;
    query.exec("select COUNT(Sno) from Student");
    if(query.lastError().type()==QSqlError::NoError){
        if(query.next()){
            int snoIndex=query.value(0).toInt()+1;
            QString sno=QString::number(snoIndex);
            while(sno.size()<=6){
                sno="0"+sno;
            }
            info<<sno;
        }
    }else{
        QMessageBox::warning(this,"查询学生数量错误",query.lastError().text());
    }
    info<<ui->NameEdit->text();
    info<<ui->SexBox->currentText();
    info<<ui->DeptBox->currentText();
    info<<ui->GradeBox->currentText();
    qDebug()<<"insert into Student values('"+info.at(0)+"','"+info.at(1)+"','"+info.at(2)+"','"+info.at(3)+"','"+info.at(4)+"')";
    query.exec("insert into Student values('"+info.at(0)+"','"+info.at(1)+"','"+info.at(2)+"','"+info.at(3)+"','"+info.at(4)+"')");
    if(query.lastError().type()==QSqlError::NoError){
        QStringList sqls;
        sqls<<"create login "+info.at(1)+" with password='123456', default_database=E_Chain";
        sqls<<"create user "+info.at(1)+" for login "+info.at(1)+" with default_schema=dbo";
        sqls<<"CREATE VIEW Sno_Info_"+info.at(0)+" AS SELECT Sno , Sname, Ssex, Sdept, Sgrade FROM Student WHERE Sno='"+info.at(0)+"'";
        sqls<<"GRANT SELECT ON Sno_Info_"+info.at(0)+" TO "+info.at(1)+"";
        sqls<<"CREATE VIEW Sno_Course_"+info.at(0)+" AS SELECT DISTINCT Stu_Cour.Cno, Stu_Cour.Cterm FROM Stu_Cour WHERE Stu_Cour.Sno='"+info.at(0)+"'";
        sqls<<"GRANT SELECT, INSERT ON Sno_Course_"+info.at(0)+" TO "+info.at(1)+"";
        sqls<<"SELECT Sno_Course_"+info.at(0)+".Cno, Cname, Tname, Sno_Course_"+info.at(0)+".Cterm, Wday, Cbegin, Cend FROM Sno_Course_"+info.at(0)+", CourseBasic, CTime, Tcourse, Teacher WHERE Sno_Course_"+info.at(0)+".Cno=CourseBasic.Cno AND Sno_Course_"+info.at(0)+".Cno=Tcourse.Cno AND Sno_Course_"+info.at(0)+".Cterm=Tcourse.Cterm AND Sno_Course_"+info.at(0)+".Cno=CTime.Cno AND Sno_Course_"+info.at(0)+".Cterm=CTime.Cterm";
        sqls<<"CREATE VIEW Sno_Grade_"+info.at(0)+" AS SELECT DISTINCT Stu_Cour.Cno, Cname, Cchar, Ccredit, Grade,Cterm FROM Stu_Cour, CourseBasic WHERE Stu_Cour.Sno='"+info.at(0)+"' AND Stu_Cour.Cno=CourseBasic.Cno ";
        sqls<<"GRANT SELECT ON Sno_Grade_"+info.at(0)+" TO "+info.at(1);
        sqls<<"CREATE VIEW Sno_S2A_"+info.at(0)+" AS SELECT Rcontent, Response FROM S2A WHERE Sno='"+info.at(0)+"'";
        sqls<<"GRANT SELECT, UPDATE(Rcontent),INSERT  ON Sno_S2A_"+info.at(0)+" TO "+info.at(1);
        sqls<<"CREATE VIEW Sno_Pro_"+info.at(0)+" AS SELECT ProjectName, Reason, Response FROM ProjectAppli WHERE Sno='"+info.at(0)+"'";
        sqls<<"GRANT SELECT, UPDATE(ProjectName, Reason),INSERT ON Sno_Pro_"+info.at(0)+" TO "+info.at(1);
        sqls<<"CREATE VIEW Sno_Scho_"+info.at(0)+" AS SELECT Scholarship, Reason, Response FROM ScholarAppli WHERE Sno='"+info.at(0)+"'";
        sqls<<"GRANT SELECT, UPDATE(Scholarship, Reason),INSERT ON Sno_Scho_"+info.at(0)+" TO "+info.at(1);

        QString res;
        for(int i=0;i<sqls.size();i++){
            query.exec(sqls.at(i));
            if(query.lastError().type()==QSqlError::NoError){

            }else{
                res+=query.lastError().text();
            }
        }
        if(res==""){
            QMessageBox::information(this,"新增学生","新增学生成功！");
            this->close();
        }else{
            QMessageBox::warning(this,"创建学生用户及视图错误",res);
        }

    }else{
        QMessageBox::warning(this,"新增学生错误",query.lastError().text());
    }
}
