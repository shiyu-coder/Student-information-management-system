#ifndef APPLYPROWIDGET_H
#define APPLYPROWIDGET_H

#include <QWidget>
#include<adminwindow.h>

namespace Ui {
class ApplyProWidget;
}

class ApplyProWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ApplyProWidget(QWidget *parent = nullptr);
    ~ApplyProWidget();

    void setName(QString name);

private slots:
    void on_toolButton_2_clicked();

    void on_toolButton_clicked();

private:
    Ui::ApplyProWidget *ui;
};

#endif // APPLYPROWIDGET_H
