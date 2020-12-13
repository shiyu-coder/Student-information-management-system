#include "modifydeptmsgwidget.h"
#include "ui_modifydeptmsgwidget.h"

ModifyDeptMsgWidget::ModifyDeptMsgWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyDeptMsgWidget)
{
    ui->setupUi(this);
    connect(this,SIGNAL(updateSignals()),this,SLOT(updateMsg()));
}

ModifyDeptMsgWidget::~ModifyDeptMsgWidget()
{
    delete ui;
}

void ModifyDeptMsgWidget::getCurrentDept(QString name_,QString info_){
    this->name=name_;
    this->info=info_;
    emit updateSignals();
}

void ModifyDeptMsgWidget::updateMsg(){
    this->setWindowTitle("修改院系“"+name+"”的信息");
    ui->textEdit->setText(info);
}

void ModifyDeptMsgWidget::on_ConfirmButton_clicked()
{
    QString newInfo=ui->textEdit->toPlainText();
    QSqlQuery query;
    query.exec("update Dept set Dintro='"+newInfo+"' where Dname='"+name+"'");
    if(query.lastError().type()==QSqlError::NoError){
        QMessageBox::information(this,"更新院系信息","院系信息更新成功！");
        this->close();
    }else{
        QMessageBox::warning(this,"错误",query.lastError().text());
    }
}

void ModifyDeptMsgWidget::on_QuitButton_clicked()
{
    this->close();
}
