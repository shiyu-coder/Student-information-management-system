#include "deptwidget.h"
#include "ui_deptwidget.h"

DeptWidget::DeptWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeptWidget)
{
    ui->setupUi(this);
    //加载院系信息
    QSqlQuery query;
    query.exec("select * from Dept");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            qDebug()<<query.value(0).toString()<<" "<<query.value(1).toString();
            ui->DeptMsgWidget->setRowCount(ui->DeptMsgWidget->rowCount()+1);
            ui->DeptMsgWidget->setItem(ui->DeptMsgWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->DeptMsgWidget->setItem(ui->DeptMsgWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
        }
    }else{
        QMessageBox::warning(this,"错误",query.lastError().text());
    }
}

DeptWidget::~DeptWidget()
{
    delete ui;
}

void DeptWidget::on_ModifyDeptInfoButton_clicked()
{
    QList<QTableWidgetItem*> items = ui->DeptMsgWidget->selectedItems();
    if(items.size()<=0){
        QMessageBox::warning(this,"错误","您没有选中任何院系！");
    }else{
        int rowIndex=ui->DeptMsgWidget->row(items.at(0));
        QString name=ui->DeptMsgWidget->item(rowIndex,0)->text();
        QString info=ui->DeptMsgWidget->item(rowIndex,1)->text();
        ModifyDeptMsgWidget *widget=new ModifyDeptMsgWidget();
        widget->getCurrentDept(name,info);
        widget->show();
    }
}

void DeptWidget::on_toolButton_clicked()
{
    ui->DeptMsgWidget->clearContents();
    ui->DeptMsgWidget->setRowCount(0);
    QSqlQuery query;
    query.exec("select * from Dept");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            qDebug()<<query.value(0).toString()<<" "<<query.value(1).toString();
            ui->DeptMsgWidget->setRowCount(ui->DeptMsgWidget->rowCount()+1);
            ui->DeptMsgWidget->setItem(ui->DeptMsgWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->DeptMsgWidget->setItem(ui->DeptMsgWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
        }
    }else{
        QMessageBox::warning(this,"错误",query.lastError().text());
    }
}

void DeptWidget::on_AddDeptButton_clicked()
{
    AddDeptWidget *widget=new AddDeptWidget();
    widget->show();
}
