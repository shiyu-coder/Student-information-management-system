#include "loginwidget.h"
#include "ui_loginwidget.h"
#include<mainwindow.h>

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
void LogInWidget::on_ConfirmButton_clicked()
{
    MainWindow *mainWindow=new MainWindow();
    mainWindow->show();
    this->close();
}

void LogInWidget::on_toolButton_clicked()
{
    MainWindow *mainWindow=new MainWindow();
    mainWindow->show();
    this->close();

}
