#ifndef DEPTWIDGET_H
#define DEPTWIDGET_H

#include <QWidget>
#include<data.h>
#include<dataquery.h>
#include<QMessageBox>
#include<QSqlQuery>
#include<QTableWidgetItem>
#include<QDebug>
#include<modifydeptmsgwidget.h>
#include<QList>
#include<adddeptwidget.h>

namespace Ui {
class DeptWidget;
}

class DeptWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeptWidget(QWidget *parent = nullptr);
    ~DeptWidget();

private slots:
    void on_ModifyDeptInfoButton_clicked();

    void on_toolButton_clicked();

    void on_AddDeptButton_clicked();

private:
    Ui::DeptWidget *ui;
};

#endif // DEPTWIDGET_H
