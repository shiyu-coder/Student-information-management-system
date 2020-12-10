#ifndef CONNECTDABASEWIDGET_H
#define CONNECTDABASEWIDGET_H

#include <QWidget>
#include<dataquery.h>
#include<QMessageBox>

namespace Ui {
class ConnectDabaseWidget;
}

class ConnectDabaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectDabaseWidget(QWidget *parent = nullptr);
    ~ConnectDabaseWidget();

private slots:
    void on_toolButton_2_clicked();

    void on_toolButton_clicked();

private:
    Ui::ConnectDabaseWidget *ui;
};

#endif // CONNECTDABASEWIDGET_H
