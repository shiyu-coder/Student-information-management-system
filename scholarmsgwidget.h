#ifndef SCHOLARMSGWIDGET_H
#define SCHOLARMSGWIDGET_H

#include <QWidget>
#include<adminwindow.h>

namespace Ui {
class ScholarMsgWidget;
}

class ScholarMsgWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScholarMsgWidget(QWidget *parent = nullptr);
    ~ScholarMsgWidget();

    void setName(QString name);

    void flush();

private slots:
    void on_toolButton_clicked();

    void on_DenyButton_clicked();

    void on_ConfirmButton_clicked();

private:
    Ui::ScholarMsgWidget *ui;
    QString name;
};

#endif // SCHOLARMSGWIDGET_H
