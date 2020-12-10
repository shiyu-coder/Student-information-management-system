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
    QString input_userName=ui->NameLineEdit->text();
    QString input_key=ui->KeyLineEdit->text();
    //管理员：0  教师：1  学生：2
    int input_type=ui->comboBox->currentIndex();

    if(input_type==0){
        if(input_userName=="admin" && input_key=="123"){
            AdminWindow *adminWindow=new AdminWindow();
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
