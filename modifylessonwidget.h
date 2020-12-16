#ifndef MODIFYLESSONWIDGET_H
#define MODIFYLESSONWIDGET_H

#include <QWidget>

namespace Ui {
class ModifyLessonWidget;
}

class ModifyLessonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyLessonWidget(QWidget *parent = nullptr);
    ~ModifyLessonWidget();

private:
    Ui::ModifyLessonWidget *ui;
};

#endif // MODIFYLESSONWIDGET_H
