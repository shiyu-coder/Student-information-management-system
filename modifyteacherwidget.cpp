#include "modifyteacherwidget.h"
#include "ui_modifyteacherwidget.h"

ModifyTeacherWidget::ModifyTeacherWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyTeacherWidget)
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

ModifyTeacherWidget::~ModifyTeacherWidget()
{
    delete ui;
}

void ModifyTeacherWidget::on_QuitButton_clicked()
{
    this->close();
}

void ModifyTeacherWidget::setTno(QString tno_,QString tname_,QString dept_){
    this->tno=tno_;
    this->tname=tname_;
    this->dept=dept_;
}

void ModifyTeacherWidget::flush(){
    ui->lineEdit->setText(tno);
    ui->NameEdit->setText(tname);
    ui->DeptBox->setCurrentText(dept);
}

void ModifyTeacherWidget::on_ConfirmButton_clicked()
{
    QString name=ui->NameEdit->text();
    QString dep=ui->DeptBox->currentText();
    QSqlQuery query;
    query.exec("update Teacher set Tname='"+name+"',Tdept='"+dep+"' where Tno='"+tno+"'");
    if(query.lastError().type()==QSqlError::NoError){
        QMessageBox::information(this,"修改教师信息","修改教师信息成功！");
        this->close();
    }else{
        QMessageBox::warning(this,"修改教师信息错误",query.lastError().text());
    }
}
