#ifndef ADDMSGWIDGET_H
#define ADDMSGWIDGET_H

#include <QWidget>
#include<adminwindow.h>

namespace Ui {
class AddMsgWidget;
}

class AddMsgWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddMsgWidget(QWidget *parent = nullptr);
    ~AddMsgWidget();

private slots:
    void on_toolButton_2_clicked();

    void on_toolButton_clicked();

private:
    Ui::AddMsgWidget *ui;
};

#endif // ADDMSGWIDGET_H
