#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include<adminwindow.h>
#include<applyscholarwidget.h>
#include<aboutwidget.h>
#include<applyprowidget.h>
#include<addmsgwidget.h>

namespace Ui {
class StudentWindow;
}

class StudentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentWindow(QWidget *parent = nullptr);
    ~StudentWindow();

public slots:
    void on_FlushButton_2_clicked();

    void on_FlushButton_1_clicked();

    void on_FlushButton_3_clicked();

    void on_FlushButton_4_clicked();

    void on_ApplyScholarButton_clicked();

    void on_actionAbout_triggered();

    void on_ChooseLessonButton_clicked();

    void on_ApplyProButton_clicked();

    void on_AddApplyButton_clicked();

    void on_FlushButton_5_clicked();

private slots:
    void on_DeleteLessonButton_clicked();

private:
    Ui::StudentWindow *ui;
};

#endif // STUDENTWINDOW_H
