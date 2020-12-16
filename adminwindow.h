#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include<loadclassfromwebwidget.h>
#include<weblogwidget.h>
#include<connectdabasewidget.h>
#include<aboutwidget.h>
#include<deptwidget.h>
#include<QSqlQuery>
#include<addstuwidget.h>
#include<QTimer>
#include<QProgressDialog>
#include<addteacherwidget.h>

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

    void on_FlushButton_2_clicked();

    void on_AddStudentButton_clicked();

    void on_FlushButton_3_clicked();

    void updateProgressDialog();

    void on_AddLessonButton_2_clicked();

private:
    Ui::AdminWindow *ui;

    QTimer *timer;
    int currentValue;
    QProgressDialog *pd;
};

#endif // ADMINWINDOW_H
