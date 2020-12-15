#ifndef ADDDEPTWIDGET_H
#define ADDDEPTWIDGET_H

#include <QWidget>
#include<adminwindow.h>

namespace Ui {
class AddDeptWidget;
}

class AddDeptWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddDeptWidget(QWidget *parent = nullptr);
    ~AddDeptWidget();

private slots:
    void on_toolButton_2_clicked();

    void on_toolButton_clicked();

private:
    Ui::AddDeptWidget *ui;
};

#endif // ADDDEPTWIDGET_H
