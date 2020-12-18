#include "addprowidget.h"
#include "ui_addprowidget.h"

AddProWidget::AddProWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddProWidget)
{
    ui->setupUi(this);
}

AddProWidget::~AddProWidget()
{
    delete ui;
}

void AddProWidget::on_toolButton_2_clicked()
{
    this->close();
}

void AddProWidget::on_toolButton_clicked()
{
    QString name=ui->NameEdit->text();
    QString intro=ui->IntroEdit->toPlainText();
    QSqlQuery query;
    Data* data=Data::getData();
    query.exec("insert into ProjectLst values('"+name+"','"+data->tno+"','"+intro+"')");
    if(query.lastError().type()==QSqlError::NoError){
        QMessageBox::information(this,"新增大创项目","新增大创项目成功！");
        this->close();
    }else{
        QMessageBox::warning(this,"新增大创项目失败",query.lastError().text());
    }
}
