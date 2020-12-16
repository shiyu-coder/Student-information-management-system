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
