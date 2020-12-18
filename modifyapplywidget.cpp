#include "modifyapplywidget.h"
#include "ui_modifyapplywidget.h"

ModifyApplyWidget::ModifyApplyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyApplyWidget)
{
    ui->setupUi(this);
}

ModifyApplyWidget::~ModifyApplyWidget()
{
    delete ui;
}

void ModifyApplyWidget::setContent(QString content_){
    this->content=content_;
}

void ModifyApplyWidget::on_toolButton_2_clicked()
{
    this->close();
}

void ModifyApplyWidget::on_toolButton_clicked()
{
    QSqlQuery query1,query2;
    query1.exec("update S2A set Response='"+ui->textEdit->toPlainText()+"' where Rcontent='"+content+"'");
    query2.exec("update T2A set Response='"+ui->textEdit->toPlainText()+"' where Rcontent='"+content+"'");
    if(query1.lastError().type()==QSqlError::NoError||query2.lastError().type()==QSqlError::NoError){
        QMessageBox::information(this,"回复消息","回复消息成功！");
        this->close();
    }else{
        QMessageBox::warning(this,"回复消息错误",query1.lastError().text()+query2.lastError().text());
    }
}
