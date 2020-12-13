#ifndef MODIFYDEPTMSGWIDGET_H
#define MODIFYDEPTMSGWIDGET_H

#include <QWidget>
#include<QString>
#include<QSqlQuery>
#include<QMessageBox>
#include<QSqlError>

namespace Ui {
class ModifyDeptMsgWidget;
}

class ModifyDeptMsgWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyDeptMsgWidget(QWidget *parent = nullptr);
    ~ModifyDeptMsgWidget();
    void getCurrentDept(QString name_,QString info_);
signals:
    void updateSignals();
private:
    Ui::ModifyDeptMsgWidget *ui;
    QString name;
    QString info;
protected slots:
    void updateMsg();
private slots:
    void on_ConfirmButton_clicked();
    void on_QuitButton_clicked();
};

#endif // MODIFYDEPTMSGWIDGET_H
