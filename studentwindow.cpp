#include "studentwindow.h"
#include "ui_studentwindow.h"

StudentWindow::StudentWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);
}

StudentWindow::~StudentWindow()
{
    delete ui;
}
