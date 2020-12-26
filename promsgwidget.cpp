#include "promsgwidget.h"
#include "ui_promsgwidget.h"

ProMsgWidget::ProMsgWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProMsgWidget)
{
    ui->setupUi(this);
}

ProMsgWidget::~ProMsgWidget()
{
    delete ui;
}

void ProMsgWidget::setName(QString name){
    ui->NameEdit->setText(name);
    on_FlushButton_clicked();

}

void ProMsgWidget::on_QuitButton_clicked()
{
    QList<QTableWidgetItem*> items=ui->ApplyWidget->selectedItems();
    if(items.size()<=0){
        QMessageBox::warning(this,"错误","您没有选中任何申请！");
    }else{
        QString res;
        QSqlQuery query;
        for(int i=0;i<items.size();i++){
            int index=ui->ApplyWidget->row(items.at(i));
            query.exec("update ProjectAppli set Response='0' where Sno='"+ui->ApplyWidget->item(index,0)->text()+"' and ProjectName='"+ui->NameEdit->text()+"'");
            if(query.lastError().type()!=QSqlError::NoError){
                res+=query.lastError().text();
            }
        }
        if(res==""){
            QMessageBox::information(this,"拒绝申请","拒绝申请成功！");
        }else{
            QMessageBox::warning(this,"拒绝申请",res);
        }
    }
}

void ProMsgWidget::on_ConfirmButton_clicked()
{
    QList<QTableWidgetItem*> items=ui->ApplyWidget->selectedItems();
    if(items.size()<=0){
        QMessageBox::warning(this,"错误","您没有选中任何申请！");
    }else{
        QString res;
        QSqlQuery query;
        for(int i=0;i<items.size();i++){
            int index=ui->ApplyWidget->row(items.at(i));
            query.exec("update ProjectAppli set Response='1' where Sno='"+ui->ApplyWidget->item(index,0)->text()+"' and ProjectName='"+ui->NameEdit->text()+"'");
            if(query.lastError().type()!=QSqlError::NoError){
                res+=query.lastError().text();
            }
        }
        if(res==""){
            QMessageBox::information(this,"通过申请","通过申请成功！");
        }else{
            QMessageBox::warning(this,"通过申请",res);
        }
    }
}

void ProMsgWidget::on_FlushButton_clicked()
{
    ui->ApplyWidget->clearContents();
    ui->AdmittedWidget->clearContents();
    ui->ApplyWidget->setRowCount(0);
    ui->AdmittedWidget->setRowCount(0);

    QSqlQuery query1,query2;
    query1.exec("select ProjectAppli.Sno,Sname,Reason from ProjectAppli,Student where ProjectAppli.Sno=Student.Sno and Response='3' and ProjectName='"+ui->NameEdit->text()+"'");
    query2.exec("select ProjectAppli.Sno,Sname,Reason from ProjectAppli,Student where ProjectAppli.Sno=Student.Sno and Response='1' and ProjectName='"+ui->NameEdit->text()+"'");
    if(query1.lastError().type()==QSqlError::NoError){
        while(query1.next()){
            ui->ApplyWidget->setRowCount(ui->ApplyWidget->rowCount()+1);
            ui->ApplyWidget->setItem(ui->ApplyWidget->rowCount()-1,0,new QTableWidgetItem(query1.value(0).toString()));
            ui->ApplyWidget->setItem(ui->ApplyWidget->rowCount()-1,1,new QTableWidgetItem(query1.value(1).toString()));
            ui->ApplyWidget->setItem(ui->ApplyWidget->rowCount()-1,2,new QTableWidgetItem(query1.value(2).toString()));
        }
    }else{
        QMessageBox::warning(this,"获取未审核申请信息错误",query1.lastError().text());
    }
    if(query2.lastError().type()==QSqlError::NoError){
        while(query2.next()){
            ui->AdmittedWidget->setRowCount(ui->AdmittedWidget->rowCount()+1);
            ui->AdmittedWidget->setItem(ui->AdmittedWidget->rowCount()-1,0,new QTableWidgetItem(query2.value(0).toString()));
            ui->AdmittedWidget->setItem(ui->AdmittedWidget->rowCount()-1,1,new QTableWidgetItem(query2.value(1).toString()));
            ui->AdmittedWidget->setItem(ui->AdmittedWidget->rowCount()-1,2,new QTableWidgetItem(query2.value(2).toString()));
        }
    }else{
        QMessageBox::warning(this,"获取成员申请信息错误",query2.lastError().text());
    }
}
