#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    QApplication::setQuitOnLastWindowClosed(true);
    //Data* data=Data::getData();
    //ui->MsgBoard->append(data->getCurrentTime()+"管理员登录成功");
    //登陆后首先需要连接数据库
    DataQuery *query=DataQuery::getDataQuery();
    QString result=query->connectToDatabase("sa","9638527410.s");
    if(result==""){
        QMessageBox::information(this,"连接到数据库","数据库连接成功！");
    }else{
        QMessageBox::warning(this,"连接到数据库",result);
    }
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


void AdminWindow::on_actionInit_triggered()
{
    DataQuery *query=DataQuery::getDataQuery();
    if(!query->databaseOnline){
        ConnectDabaseWidget *cdwidget=new ConnectDabaseWidget();
        cdwidget->show();
    }else{
        QString result=query->init();
        QMessageBox::information(this,"数据库初始化",result);
    }
}

void AdminWindow::on_actionAbout_triggered()
{
    AboutWidget *aboutwidget=new AboutWidget();
    aboutwidget->show();
}
