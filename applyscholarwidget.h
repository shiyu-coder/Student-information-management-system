#ifndef APPLYSCHOLARWIDGET_H
#define APPLYSCHOLARWIDGET_H

#include <QWidget>
#include<data.h>
#include<adminwindow.h>
#include<QSqlError>
#include<QMessageBox>

namespace Ui {
class ApplyScholarWidget;
}

class ApplyScholarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ApplyScholarWidget(QWidget *parent = nullptr);
    ~ApplyScholarWidget();

    void setMsg(QString scholar);

private slots:
    void on_QuitButton_clicked();

    void on_ConfirmButton_clicked();

private:
    Ui::ApplyScholarWidget *ui;
    QString scholar;
};

#endif // APPLYSCHOLARWIDGET_H
