#include "applyscholarwidget.h"
#include "ui_applyscholarwidget.h"

ApplyScholarWidget::ApplyScholarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApplyScholarWidget)
{
    ui->setupUi(this);
}

ApplyScholarWidget::~ApplyScholarWidget()
{
    delete ui;
}

void ApplyScholarWidget::on_QuitButton_clicked()
{
    this->close();
}

void ApplyScholarWidget::setMsg(QString scholar_){
    this->scholar=scholar_;
    ui->NameEdit->setText(scholar);
}

void ApplyScholarWidget::on_ConfirmButton_clicked()
{
    Data *data=Data::getData();
    QString sno=data->sno;
    QString reason=ui->textEdit->toPlainText();
    QSqlQuery query;
    query.exec("insert into ScholarAppli values('"+sno+"','"+scholar+"','"+reason+"','3')");
    if(query.lastError().type()==QSqlError::NoError){
        QMessageBox::information(this,"申请奖学金","申请奖学金成功！");
        this->close();
    }else{
        QMessageBox::warning(this,"申请奖学金错误",query.lastError().text());
    }

}
