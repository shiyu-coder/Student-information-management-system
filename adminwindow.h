#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include<loadclassfromwebwidget.h>
#include<weblogwidget.h>
#include<connectdabasewidget.h>
#include<aboutwidget.h>
#include<deptwidget.h>
#include<QSqlQuery>

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void on_actionLoadClassFromWeb_triggered();

    void closeEvent(QCloseEvent *event);

    void on_actionInit_triggered();

    void on_actionAbout_triggered();

    void on_actionDeptManagement_triggered();

    void on_actionDatabaseRenew_triggered();

    void on_FlushButton_clicked();

private:
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
