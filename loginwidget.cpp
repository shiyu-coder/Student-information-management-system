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
    //程序初次登录检测
    //若程序初次登陆，需要先初始化一下
    //通过initialize.pm文件是否存在检测
    QFile iniFile("initialize.pm");
    if(!iniFile.exists()){
        DataQuery *query=DataQuery::getDataQuery();
        QString res0=query->connectToDatabase("sa","9638527410.s");
        if(res0!="") qApp->quit();
        QString res=query->init();
        if(res==""){
            if(iniFile.open(QIODevice::WriteOnly|QIODevice::Text)){
                iniFile.close();
            }else{
                //出现了无法解决的错误，直接退出程序
                QMessageBox::warning(this,"错误",iniFile.errorString());
                this->destroy();
                qApp->quit();
            }
        }else{
            QMessageBox::warning(this,"数据库初始化错误",res);
            if(iniFile.open(QIODevice::WriteOnly|QIODevice::Text)){
                iniFile.close();
            }else{
                //出现了无法解决的错误，直接退出程序
                QMessageBox::warning(this,"错误",iniFile.errorString());
                this->destroy();
                qApp->quit();
            }
        }
    }
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
    pd=new QProgressDialog(this);
    pd->setRange(0,MAX_SEC);
    pd->setWindowModality(Qt::WindowModal);
    pd->setModal(true);
    pd->setMinimumDuration(5);
    pd->setWindowTitle("请稍后...");
    pd->setFixedWidth(400);
    pd->setValue(0);
    pd->setValue(0);
    pd->show();
    if(input_type==0){
        if(input_userName=="admin" && input_key=="123"){
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

            pd->setValue(MAX_SEC*93/100);
            qApp->processEvents();
            adminWindow->on_FlushButton_5_clicked();

            pd->setValue(MAX_SEC);
            qApp->processEvents();
            pd->close();

            adminWindow->show();
            this->close();
        }else{
            QMessageBox::warning(this,"警告","用户名或密码错误！");
            return;
        }
    }else{
        DataQuery *query=DataQuery::getDataQuery();
        bool canLogIn=query->canLogInSIMS(input_userName,input_key,input_type);
        if(canLogIn){
            if(input_type==1){
                Data* data=Data::getData();
                data->tno=input_userName;

                TeacherWindow *teacherWindow=new TeacherWindow();
                pd->setValue(MAX_SEC/7);
                qApp->processEvents();
                teacherWindow->on_FlushButton_1_clicked();
                pd->setValue(MAX_SEC*35/100);
                qApp->processEvents();
                teacherWindow->on_FlushButton_2_clicked();
                pd->setValue(MAX_SEC*57/100);
                qApp->processEvents();
                teacherWindow->on_FlushButton_3_clicked();
                pd->setValue(MAX_SEC*69/100);
                qApp->processEvents();
                teacherWindow->on_FlushButton_4_clicked();
                pd->setValue(MAX_SEC*86/100);
                qApp->processEvents();

                teacherWindow->show();
                this->close();
            }else if(input_type==2){
                Data* data=Data::getData();
                data->sno=input_userName;
                StudentWindow *studentWindow=new StudentWindow();
                pd->setValue(MAX_SEC/7);
                qApp->processEvents();
                studentWindow->on_FlushButton_1_clicked();
                pd->setValue(MAX_SEC*37/100);
                qApp->processEvents();
                studentWindow->on_FlushButton_2_clicked();
                pd->setValue(MAX_SEC*51/100);
                qApp->processEvents();

                studentWindow->on_FlushButton_3_clicked();
                pd->setValue(MAX_SEC*65/100);
                qApp->processEvents();

                studentWindow->on_FlushButton_4_clicked();
                pd->setValue(MAX_SEC*82/100);
                qApp->processEvents();

                studentWindow->on_FlushButton_5_clicked();
                pd->setValue(MAX_SEC*93/100);
                qApp->processEvents();

                pd->setValue(MAX_SEC);
                qApp->processEvents();
                pd->close();

                studentWindow->show();
                this->close();
            }
        }else{
            QMessageBox::warning(this,"警告","用户名或密码错误！");
            return;
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
