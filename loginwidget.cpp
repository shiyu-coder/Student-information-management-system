#include "loginwidget.h"
#include "ui_loginwidget.h"
#include<mainwindow.h>
#include<adminwindow.h>

#define MAX_SEC 10000

LogInWidget::LogInWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogInWidget)
{
    ui->setupUi(this);
    currentValue=0;
}

LogInWidget::~LogInWidget()
{
    delete ui;
}

//登录界面确定按钮触发
void LogInWidget::on_toolButton_clicked()
{
    QString input_userName=ui->NameLineEdit->text();
    QString input_key=ui->KeyLineEdit->text();
    //管理员：0  教师：1  学生：2
    int input_type=ui->comboBox->currentIndex();

    if(input_type==0){
        if(input_userName=="admin" && input_key=="123"){
            pd=new QProgressDialog(this);
            pd->setRange(0,MAX_SEC);
            pd->setWindowModality(Qt::WindowModal);
            pd->setModal(true);
            pd->setMinimumDuration(5);
            pd->setWindowTitle("请稍后...");
            pd->setFixedWidth(400);
            pd->setValue(0);

            //timer=new QTimer();
            //connect(timer,SIGNAL(timeout()),this,SLOT(updateProgressDialog()));
            //timer->start(100);

            pd->setValue(0);
            pd->show();

            AdminWindow *adminWindow;
            adminWindow=new AdminWindow();
            pd->setValue(MAX_SEC/5);
            qApp->processEvents();
            adminWindow->on_FlushButton_clicked();

            pd->setValue(MAX_SEC*2/3);
            qApp->processEvents();
            adminWindow->on_FlushButton_2_clicked();

            pd->setValue(MAX_SEC*3/4);
            qApp->processEvents();
            adminWindow->on_FlushButton_3_clicked();

            pd->setValue(MAX_SEC*4/5);
            qApp->processEvents();
            adminWindow->on_FlushButton_4_clicked();

            pd->setValue(MAX_SEC);
            qApp->processEvents();

            //timer->stop();
            pd->close();

            adminWindow->show();
            this->close();
        }else{
            QMessageBox::warning(this,"警告","用户名或密码错误！");
        }
    }else{
        DataQuery *query=DataQuery::getDataQuery();
        bool canLogIn=query->canLogInSIMS(input_userName,input_key,input_type);
        if(canLogIn){
            if(input_type==1){
                TeacherWindow *teacherWindow=new TeacherWindow();
                teacherWindow->show();
                this->close();
            }else if(input_type==2){
                StudentWindow *studentWindow=new StudentWindow();
                studentWindow->show();
                this->close();
            }
        }else{
            QMessageBox::warning(this,"警告","用户名或密码错误！");
        }
    }

}

void LogInWidget::updateProgressDialog(){
    currentValue++;
    if(currentValue==MAX_SEC) currentValue=0;
    pd->setValue(currentValue);
    qApp->processEvents();
    if(pd->wasCanceled())
        pd->setHidden(true);//隐藏对话框
}
