#include "scholarmsgwidget.h"
#include "ui_scholarmsgwidget.h"

ScholarMsgWidget::ScholarMsgWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScholarMsgWidget)
{
    ui->setupUi(this);
}

void ScholarMsgWidget::setName(QString name_){
    this->name=name_;
}

ScholarMsgWidget::~ScholarMsgWidget()
{
    delete ui;
}

void ScholarMsgWidget::flush(){
    ui->ApplyWidget->clearContents();
    ui->ApplyWidget->setRowCount(0);
    ui->GrantWidget->clear();
    QSqlQuery query;
    query.exec("select * from ScholarLst where Scholarship='"+name+"'");
    if(query.lastError().type()==QSqlError::NoError){
        if(query.next()){
            ui->NameEdit->setText(query.value(0).toString());
            ui->IntroEdit->setText(query.value(1).toString());
            ui->MoneyEdit->setText(query.value(2).toString());
        }
    }else{
        QMessageBox::warning(this,"查询奖学金错误",query.lastError().text());
    }
    query.exec("select Sname,Reason from Student,ScholarAppli where Student.Sno=ScholarAppli.Sno and Response='3' and Scholarship='"+name+"'");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            ui->ApplyWidget->setRowCount(ui->ApplyWidget->rowCount()+1);
            ui->ApplyWidget->setItem(ui->ApplyWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->ApplyWidget->setItem(ui->ApplyWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
        }
    }else{
        QMessageBox::warning(this,"查询奖学金错误",query.lastError().text());
    }
    query.exec("select Sname,Reason from Student,ScholarAppli where Student.Sno=ScholarAppli.Sno and Response='1' and Scholarship='"+name+"'");
    if(query.lastError().type()==QSqlError::NoError){
        while(query.next()){
            ui->GrantWidget->addItem(query.value(0).toString()+"  申请理由："+query.value(1).toString());
        }
    }else{
        QMessageBox::warning(this,"查询奖学金错误",query.lastError().text());
    }
}

void ScholarMsgWidget::on_toolButton_clicked()
{
    QString intro=ui->IntroEdit->toPlainText();
    QString money=ui->MoneyEdit->text();
    QSqlQuery query;
    query.exec("update ScholarLst set SchoIntro='"+intro+"',Money="+money+" where Scholarship='"+name+"'");
    if(query.lastError().type()==QSqlError::NoError){
        QMessageBox::information(this,"更改奖学金信息","更改奖学金信息成功！");
    }else{
        QMessageBox::warning(this,"更改奖学金信息失败",query.lastError().text());
    }
}

void ScholarMsgWidget::on_DenyButton_clicked()
{
    QList<QTableWidgetItem*> items=ui->ApplyWidget->selectedItems();
    if(items.size()<=0){
        QMessageBox::warning(this,"错误","您没有选中任何申请人！");
    }else{
        QString res;
        for(int i=0;i<items.size();i++){
            int rowIndex=ui->ApplyWidget->row(items.at(i));
            QString nameStr=ui->ApplyWidget->item(rowIndex,0)->text();
            QSqlQuery query;
            query.exec("update ScholarAppli set Response='0' where Scholarship='"+ui->NameEdit->text()+"' and Sno in (select Sno from Student where Sname='"+nameStr+"')");
            if(query.lastError().type()==QSqlError::NoError){

            }else{
                res+=query.lastError().text();
            }
        }
        if(res==""){
            QMessageBox::information(this,"拒绝奖学金申请","拒绝奖学金申请成功!");
            flush();
        }else{
            QMessageBox::warning(this,"拒绝奖学金申请失败",res);
        }
    }
}

void ScholarMsgWidget::on_ConfirmButton_clicked()
{
    QList<QTableWidgetItem*> items=ui->ApplyWidget->selectedItems();
    if(items.size()<=0){
        QMessageBox::warning(this,"错误","您没有选中任何申请人！");
    }else{
        QString res;
        for(int i=0;i<items.size();i++){
            int rowIndex=ui->ApplyWidget->row(items.at(i));
            QString nameStr=ui->ApplyWidget->item(rowIndex,0)->text();
            QSqlQuery query;
            query.exec("select * from ScholarLst,ScholarAppli where ScholarLst.Scholarship=ScholarAppli.Scholarship and Money>=5000 and Response='3'");
            if(query.lastError().type()==QSqlError::NoError){
                if(query.next()&&ui->MoneyEdit->text().toInt()<5000){
                    QMessageBox::warning(this,"错误","存在待审核的5000元及以上金额的奖学金！");
                }else{
                    query.exec("update ScholarAppli set Response='1' where Scholarship='"+ui->NameEdit->text()+"' and Sno in (select Sno from Student where Sname='"+nameStr+"')");
                    if(query.lastError().type()==QSqlError::NoError){
                        if(ui->MoneyEdit->text().toInt()>=5000){
                            query.exec("update ScholarAppli set Response='2' where Scholarship!='"+ui->NameEdit->text()+"' and Sno in (select Sno from Student where Sname='"+nameStr+"')");
                            if(query.lastError().type()==QSqlError::NoError){
                                QMessageBox::information(this,"授予奖学金","授予奖学金成功！");
                                flush();
                            }else{
                                QMessageBox::warning(this,"授予奖学金失败",query.lastError().text());
                            }

                        }else{
                            QMessageBox::information(this,"授予奖学金","授予奖学金成功！");
                            flush();
                        }
                    }else{
                        QMessageBox::warning(this,"授予奖学金失败",query.lastError().text());
                    }
                }
            }else{
                QMessageBox::warning(this,"奖学金信息查询失败",query.lastError().text());
            }
        }
    }

}
