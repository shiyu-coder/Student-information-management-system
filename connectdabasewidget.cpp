#include "connectdabasewidget.h"
#include "ui_connectdabasewidget.h"

ConnectDabaseWidget::ConnectDabaseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectDabaseWidget)
{
    ui->setupUi(this);
}

ConnectDabaseWidget::~ConnectDabaseWidget()
{
    delete ui;
}

void ConnectDabaseWidget::on_toolButton_2_clicked()
{
    this->close();
}

void ConnectDabaseWidget::on_toolButton_clicked()
{
    QString dbName=ui->dbNameEdit->text();
    QString dbKey=ui->dbKeyEdit->text();

    DataQuery *query=DataQuery::getDataQuery();
    QString result=query->connectToDatabase(dbName,dbKey);
    if(result==""){
        QMessageBox::information(this,"连接到数据库","数据库连接成功！");
        this->close();
    }else{
        QMessageBox::warning(this,"连接到数据库",result);
    }
}
