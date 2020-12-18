#include "addteacherwidget.h"
#include "ui_addteacherwidget.h"

AddTeacherWidget::AddTeacherWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddTeacherWidget)
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
}

AddTeacherWidget::~AddTeacherWidget()
{
    delete ui;
}

void AddTeacherWidget::on_QuitButton_clicked()
{
    this->close();
}

void AddTeacherWidget::on_ConfirmButton_clicked()
{
    QSqlQuery TeaQuery;
    TeaQuery.exec("select COUNT(Tno) from Teacher");
    if(TeaQuery.lastError().type()==QSqlError::NoError){
        if(TeaQuery.next()){
            int tnoIndex=TeaQuery.value(0).toInt();
            QString tno=QString::number(tnoIndex);
            while(tno.size()<4){
                tno="0"+tno;
            }
            QString name=ui->NameEdit->text();
            QString dept=ui->DeptBox->currentText();
            QSqlQuery query;
            query.exec("insert into Teacher values('"+tno+"','"+name+"','"+dept+"')");
            if(query.lastError().type()==QSqlError::NoError){
                QSqlQuery query2;
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
                QMessageBox::information(this,"新增教师信息","新增教师成功");
                this->close();
            }else{
                QMessageBox::warning(this,"新增教师信息错误",query.lastError().text());
            }
        }
    }else{
        QMessageBox::warning(this,"查询教师信息错误",TeaQuery.lastError().text());
    }

}
