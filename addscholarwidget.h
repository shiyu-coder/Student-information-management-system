#ifndef ADDSCHOLARWIDGET_H
#define ADDSCHOLARWIDGET_H

#include <QWidget>
#include<adminwindow.h>

namespace Ui {
class AddScholarWidget;
}

class AddScholarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddScholarWidget(QWidget *parent = nullptr);
    ~AddScholarWidget();

private slots:
    void on_QuitButton_clicked();

    void on_ConfirmButton_clicked();

private:
    Ui::AddScholarWidget *ui;
};

#endif // ADDSCHOLARWIDGET_H
