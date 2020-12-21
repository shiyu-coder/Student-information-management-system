#ifndef MODIFYSTUWIDGET_H
#define MODIFYSTUWIDGET_H

#include <QWidget>
#include<QDate>
#include<adminwindow.h>
#include<QMessageBox>

namespace Ui {
class ModifyStuWidget;
}

class ModifyStuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyStuWidget(QWidget *parent = nullptr);
    ~ModifyStuWidget();

    void setMsg(QString sno,QString sname,QString sex,QString sdept,QString sgrade);

private slots:
    void on_QuitButton_clicked();

    void on_ConfirmButton_clicked();

private:
    Ui::ModifyStuWidget *ui;
};

#endif // MODIFYSTUWIDGET_H
