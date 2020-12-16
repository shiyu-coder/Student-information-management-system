#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include<QMessageBox>
#include<adminwindow.h>
#include<studentwindow.h>
#include<teacherwindow.h>
#include<QProgressDialog>
#include<QTimer>
#include<QThread>

namespace Ui {
class LogInWidget;
}

class LogInWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogInWidget(QWidget *parent = nullptr);
    ~LogInWidget();

private slots:

    void on_toolButton_clicked();
    void updateProgressDialog();

private:
    Ui::LogInWidget *ui;

    QTimer *timer;
    int currentValue;
    QProgressDialog *pd;
    QThread *pdThread;
};

#endif // LOGINWIDGET_H
