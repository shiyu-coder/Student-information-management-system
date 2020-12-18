#ifndef ADDPROWIDGET_H
#define ADDPROWIDGET_H

#include <QWidget>
#include<adminwindow.h>
#include <QWidget>
#include<QSqlQuery>
#include<QString>
#include<QStringList>
#include<QMessageBox>
#include<data.h>
#include<QDebug>
#include<QSqlError>

namespace Ui {
class AddProWidget;
}

class AddProWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddProWidget(QWidget *parent = nullptr);
    ~AddProWidget();

private slots:
    void on_toolButton_2_clicked();

    void on_toolButton_clicked();

private:
    Ui::AddProWidget *ui;
};

#endif // ADDPROWIDGET_H
