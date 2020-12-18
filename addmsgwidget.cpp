#include "addmsgwidget.h"
#include "ui_addmsgwidget.h"

AddMsgWidget::AddMsgWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddMsgWidget)
{
    ui->setupUi(this);
}

AddMsgWidget::~AddMsgWidget()
{
    delete ui;
}

void AddMsgWidget::on_toolButton_2_clicked()
{
    this->close();
}

void AddMsgWidget::on_toolButton_clicked()
{
    Data* data=Data::getData();
    QSqlQuery query;
    QString index;
    if(data->tno=="") index="S2A values('"+data->sno;
    else if(data->sno=="") index="T2A values('"+data->tno;
    query.exec("insert into "+index+"','"+ui->textEdit->toPlainText()+"','')");
    if(query.lastError().type()==QSqlError::NoError){
        QMessageBox::information(this,"新增消息","新增消息成功！");
        this->close();
    }else{
        QMessageBox::warning(this,"新增消息错误",query.lastError().text());
    }
}
