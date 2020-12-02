#include "loginwidget.h"
#include "ui_loginwidget.h"
#include<mainwindow.h>
#include<adminwindow.h>

LogInWidget::LogInWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogInWidget)
{
    ui->setupUi(this);
}

LogInWidget::~LogInWidget()
{
    delete ui;
}

//登录界面确定按钮触发
void LogInWidget::on_toolButton_clicked()
{
    AdminWindow *adminWindow=new AdminWindow();
    adminWindow->show();
    this->close();

}
