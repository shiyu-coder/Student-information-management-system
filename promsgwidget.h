#ifndef PROMSGWIDGET_H
#define PROMSGWIDGET_H

#include <QWidget>
#include<adminwindow.h>

namespace Ui {
class ProMsgWidget;
}

class ProMsgWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProMsgWidget(QWidget *parent = nullptr);
    ~ProMsgWidget();

    void setName(QString name);

private slots:
    void on_QuitButton_clicked();

    void on_ConfirmButton_clicked();

    void on_FlushButton_clicked();

private:
    Ui::ProMsgWidget *ui;
};

#endif // PROMSGWIDGET_H
