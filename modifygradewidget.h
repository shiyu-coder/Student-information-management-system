#ifndef MODIFYGRADEWIDGET_H
#define MODIFYGRADEWIDGET_H

#include <QWidget>
#include<adminwindow.h>

namespace Ui {
class ModifyGradeWidget;
}

class ModifyGradeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyGradeWidget(QWidget *parent = nullptr);
    ~ModifyGradeWidget();

    void setMsg(QString name,QStringList cnos);

private slots:
    void on_toolButton_clicked();

private:
    Ui::ModifyGradeWidget *ui;

    QString _name;
    QStringList _cnos;
};

#endif // MODIFYGRADEWIDGET_H
