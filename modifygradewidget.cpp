#include "modifygradewidget.h"
#include "ui_modifygradewidget.h"

ModifyGradeWidget::ModifyGradeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyGradeWidget)
{
    ui->setupUi(this);
}

ModifyGradeWidget::~ModifyGradeWidget()
{
    delete ui;
}


void ModifyGradeWidget::setMsg(QString name,QStringList cnos){
    _name=name;
    _cnos=cnos;
}

void ModifyGradeWidget::on_toolButton_clicked()
{
    QString grade=ui->lineEdit->text();
    QString res;
    QSqlQuery query;
    for(int i=0;i<_cnos.size();i++){
        query.exec("update Stu_Cour set Grade="+grade+" where Sno='"+_cnos.at(i)+"' and Cno=(select Cno from CourseBasic where Cname='"+_name+"')");
        if(query.lastError().type()!=QSqlError::NoError) res+=query.lastError().text();
    }
    if(res==""){
        QMessageBox::information(this,"修改成绩","修改成绩成功！");
        this->close();
    }else{
        QMessageBox::warning(this,"修改成绩错误",res);
    }
}
