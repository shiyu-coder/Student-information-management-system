#include "adddeptwidget.h"
#include "ui_adddeptwidget.h"

AddDeptWidget::AddDeptWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDeptWidget)
{
    ui->setupUi(this);
}

AddDeptWidget::~AddDeptWidget()
{
    delete ui;
}

void AddDeptWidget::on_toolButton_2_clicked()
{
    this->close();
}

void AddDeptWidget::on_toolButton_clicked()
{
    QString name,info;
    name=ui->lineEdit->text();
    info=ui->textEdit->toPlainText();
    QSqlQuery query;
    query.exec("insert into Dept values('"+name+"','"+info+"')");
    if(query.lastError().type()==QSqlError::NoError){
        QMessageBox::information(this,"新增院系","新增院系成功！");
        this->close();
    }else{
        QMessageBox::warning(this,"新增院系错误",query.lastError().text());
    }
}
