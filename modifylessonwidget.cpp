#include "modifylessonwidget.h"
#include "ui_modifylessonwidget.h"

ModifyLessonWidget::ModifyLessonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyLessonWidget)
{
    ui->setupUi(this);
}

ModifyLessonWidget::~ModifyLessonWidget()
{
    delete ui;
}
