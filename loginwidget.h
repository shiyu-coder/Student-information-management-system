#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

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

    void on_ConfirmButton_clicked();

    void on_toolButton_clicked();

private:
    Ui::LogInWidget *ui;
};

#endif // LOGINWIDGET_H
