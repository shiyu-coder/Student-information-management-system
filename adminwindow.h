#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include<loadclassfromwebwidget.h>
#include<weblogwidget.h>

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

private:
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
