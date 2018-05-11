#include "templateeditwindow.h"
#include "ui_templateeditwindow.h"

TemplateEditWindow::TemplateEditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TemplateEditWindow)
{
    ui->setupUi(this);
}

TemplateEditWindow::~TemplateEditWindow()
{
    delete ui;
}
