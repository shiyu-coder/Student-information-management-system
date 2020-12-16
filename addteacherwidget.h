#ifndef ADDTEACHERWIDGET_H
#define ADDTEACHERWIDGET_H

#include <QWidget>
#include<adminwindow.h>

namespace Ui {
class AddTeacherWidget;
}

class AddTeacherWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddTeacherWidget(QWidget *parent = nullptr);
    ~AddTeacherWidget();

private slots:
    void on_QuitButton_clicked();

    void on_ConfirmButton_clicked();

private:
    Ui::AddTeacherWidget *ui;
};

#endif // ADDTEACHERWIDGET_H
