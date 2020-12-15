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
        QMessageBox::information(this,"新增学生","新增学生成功！");
        this->close();
    }else{
        QMessageBox::warning(this,"新增学生错误",query.lastError().text());
    }
}
