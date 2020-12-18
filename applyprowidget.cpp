#include "applyprowidget.h"
#include "ui_applyprowidget.h"

ApplyProWidget::ApplyProWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApplyProWidget)
{
    ui->setupUi(this);
}

ApplyProWidget::~ApplyProWidget()
{
    delete ui;
}

void ApplyProWidget::setName(QString name){
    ui->lineEdit->setText(name);
}

void ApplyProWidget::on_toolButton_2_clicked()
{
    this->close();
}

void ApplyProWidget::on_toolButton_clicked()
{
    Data* data=Data::getData();
    QString sno=data->sno;
    QString name=ui->lineEdit->text();
    QString intro=ui->textEdit->toPlainText();
    QSqlQuery query;
    query.exec("insert into ProjectAppli values('"+sno+"','"+name+"','"+intro+"','3')");
    if(query.lastError().type()==QSqlError::NoError){
        QMessageBox::information(this,"申请大创项目","申请大创项目成功！");
        this->close();
    }else{
        QMessageBox::warning(this,"申请大创项目错误",query.lastError().text());
    }
}
