#include "loginwidget.h"
#include "ui_loginwidget.h"
#include<mainwindow.h>
#include<adminwindow.h>

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
            pd->setRange(0,10001);
            pd->setWindowModality(Qt::WindowModal);
            pd->setModal(true);
            pd->setMinimumDuration(5);
            pd->setWindowTitle("请稍后...");
            pd->setFixedWidth(400);
            pd->setValue(0);
            pd->show();
            for(int i=0;i<100;i++){
                for(int j=0;j<100;j++){
                    updateProgressDialog();
                }
            }

            AdminWindow *adminWindow;
            adminWindow=new AdminWindow();
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
    pd->setValue(currentValue);
    QCoreApplication::processEvents();//避免界面冻结
    if(pd->wasCanceled())
        pd->setHidden(true);//隐藏对话框
}
