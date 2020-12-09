#include "teacherwindow.h"
#include "ui_teacherwindow.h"

TeacherWindow::TeacherWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TeacherWindow)
{
    ui->setupUi(this);
}

TeacherWindow::~TeacherWindow()
{
    delete ui;
}
