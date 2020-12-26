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
#include<addscholarwidget.h>
#include<loginwidget.h>
#include<scholarmsgwidget.h>
#include<modifyteacherwidget.h>
#include<applyscholarwidget.h>
#include<modifyapplywidget.h>
#include<modifystuwidget.h>

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

    void setProgressDialog(QProgressDialog * pd);

    void updateProgress();

public slots:
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

    void on_FlushButton_4_clicked();

    void on_toolButton_26_clicked();

    void on_ScholarshipWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_ModifyTeacherButton_clicked();

    void on_FlushButton_5_clicked();

private slots:
    void on_MsgWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_toolButton_27_clicked();

    void on_ModifyStudentButton_clicked();

    void on_FindLessonButton_clicked();

    void on_DeleteTeacherButton_clicked();

    void on_DeleteStudentButton_clicked();

private:
    Ui::AdminWindow *ui;

    QTimer *timer;
    int currentValue;
    QProgressDialog *pd;
};

#endif // ADMINWINDOW_H
