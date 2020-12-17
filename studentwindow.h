#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include<adminwindow.h>

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

private:
    Ui::StudentWindow *ui;
};

#endif // STUDENTWINDOW_H
