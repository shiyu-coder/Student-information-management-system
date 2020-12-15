#ifndef ADDSTUWIDGET_H
#define ADDSTUWIDGET_H

#include <QWidget>
#include<QSqlQuery>
#include<QString>
#include<QStringList>
#include<QMessageBox>
#include<data.h>
#include<QDebug>
#include<QSqlError>

namespace Ui {
class AddStuWidget;
}

class AddStuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddStuWidget(QWidget *parent = nullptr);
    ~AddStuWidget();

private slots:
    void on_QuitButton_clicked();

    void on_ConfirmButton_clicked();

private:
    Ui::AddStuWidget *ui;
};

#endif // ADDSTUWIDGET_H
