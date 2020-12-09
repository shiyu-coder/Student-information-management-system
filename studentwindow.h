#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>

namespace Ui {
class StudentWindow;
}

class StudentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentWindow(QWidget *parent = nullptr);
    ~StudentWindow();

private:
    Ui::StudentWindow *ui;
};

#endif // STUDENTWINDOW_H
