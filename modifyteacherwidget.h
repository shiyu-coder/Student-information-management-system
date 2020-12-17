#ifndef MODIFYTEACHERWIDGET_H
#define MODIFYTEACHERWIDGET_H

#include <QWidget>
#include<adminwindow.h>

namespace Ui {
class ModifyTeacherWidget;
}

class ModifyTeacherWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyTeacherWidget(QWidget *parent = nullptr);
    ~ModifyTeacherWidget();

    void setTno(QString tno_,QString tname_,QString dept_);

    void flush();

private slots:
    void on_QuitButton_clicked();

    void on_ConfirmButton_clicked();

private:
    Ui::ModifyTeacherWidget *ui;
    QString tno;
    QString tname;
    QString dept;
};

#endif // MODIFYTEACHERWIDGET_H
