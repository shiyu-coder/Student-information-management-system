#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    QApplication::setQuitOnLastWindowClosed(true);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}
//导入课程触发函数
void AdminWindow::on_actionLoadClassFromWeb_triggered()
{
    LoadClassFromWebWidget *loadWidget=new LoadClassFromWebWidget();
    loadWidget->show();
    WebLogWidget *webLogWidget=new WebLogWidget();
    webLogWidget->show();
}

void AdminWindow::closeEvent(QCloseEvent *event){
    qApp->quit();
    event->accept();
}

