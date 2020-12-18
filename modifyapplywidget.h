#ifndef MODIFYAPPLYWIDGET_H
#define MODIFYAPPLYWIDGET_H

#include <QWidget>
#include<adminwindow.h>

namespace Ui {
class ModifyApplyWidget;
}

class ModifyApplyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyApplyWidget(QWidget *parent = nullptr);
    ~ModifyApplyWidget();

    void setContent(QString content);

private slots:
    void on_toolButton_2_clicked();

    void on_toolButton_clicked();

private:
    QString content;
    Ui::ModifyApplyWidget *ui;
};

#endif // MODIFYAPPLYWIDGET_H
