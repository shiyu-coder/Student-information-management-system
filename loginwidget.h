#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include<QMessageBox>
#include<adminwindow.h>
#include<studentwindow.h>
#include<teacherwindow.h>

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

private:
    Ui::LogInWidget *ui;
};

#endif // LOGINWIDGET_H
