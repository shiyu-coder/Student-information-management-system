#include "addscholarwidget.h"
#include "ui_addscholarwidget.h"

AddScholarWidget::AddScholarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddScholarWidget)
{
    ui->setupUi(this);
}

AddScholarWidget::~AddScholarWidget()
{
    delete ui;
}

void AddScholarWidget::on_QuitButton_clicked()
{
    this->close();
}

void AddScholarWidget::on_ConfirmButton_clicked()
{
    QString name=ui->NameEdit->text();
    QString intro=ui->IntroEdit->toPlainText();
    QString money=ui->MoneyEdit->text();
    QSqlQuery query;
    query.exec("insert into ScholarLst values('"+name+"','"+intro+"',"+money+")");
    if(query.lastError().type()==QSqlError::NoError){
        QMessageBox::information(this,"新增奖学金","新增奖学金成功！");
        this->close();
    }else{
        QMessageBox::warning(this,"新增奖学金错误",query.lastError().text());
    }
}
