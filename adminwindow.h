#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

private:
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
