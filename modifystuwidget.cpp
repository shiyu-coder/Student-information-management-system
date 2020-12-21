#include "modifystuwidget.h"
#include "ui_modifystuwidget.h"

ModifyStuWidget::ModifyStuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyStuWidget)
{
    ui->setupUi(this);
}

ModifyStuWidget::~ModifyStuWidget()
{
    delete ui;
}

void ModifyStuWidget::on_QuitButton_clicked()
{
    this->close();
}

void ModifyStuWidget::setMsg(QString sno,QString sname,QString sex,QString sdept,QString sgrade){
    ui->SnoEdit->setText(sno);
    ui->NameEdit->setText(sname);
    ui->SexBox->addItem("男");
    ui->SexBox->addItem("女");
    ui->SexBox->setCurrentText(sex);
    QDate date(QDate::currentDate());
    int year = date.year();
    int month=date.month();
    if(month<=6){//如果是上半年，则课表是去年的
        year--;
    }
    QSqlQuery query;
    query.exec("select Dname from Dept");
    if(query.lastError().type()==QSqlError::NoError){
        while (query.next()) {
            ui->DeptBox->addItem(query.value(0).toString());
        }
    }else{
        QMessageBox::warning(this,"查询院系信息错误",query.lastError().text());
        return;
    }
    ui->DeptBox->setCurrentText(sdept);
    ui->GradeBox->addItem(QString::number(year));
    ui->GradeBox->addItem(QString::number(year-1));
    ui->GradeBox->addItem(QString::number(year-2));
    ui->GradeBox->addItem(QString::number(year-3));
    ui->GradeBox->setCurrentText(sgrade);
}

void ModifyStuWidget::on_ConfirmButton_clicked()
{
    QString sno=ui->SnoEdit->text();
    QString name=ui->NameEdit->text();
    QString sex=ui->SexBox->currentText();
    QString dept=ui->DeptBox->currentText();
    QString grade=ui->GradeBox->currentText();
    QSqlQuery query;
    query.exec("update Student set Sname='"+name+"',Ssex='"+sex+"',Sdept='"+dept+"',Sgrade='"+grade+"' where Sno='"+sno+"'");
    if(query.lastError().type()==QSqlError::NoError){
        QMessageBox::information(this,"更改学生信息","更改学生信息成功！");
        this->close();
    }else{
        QMessageBox::warning(this,"更改学生信息错误",query.lastError().text());
    }
}
