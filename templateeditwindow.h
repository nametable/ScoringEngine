#ifndef TEMPLATEEDITWINDOW_H
#define TEMPLATEEDITWINDOW_H

#include <QDialog>

namespace Ui {
class TemplateEditWindow;
}

class TemplateEditWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TemplateEditWindow(QWidget *parent = 0);
    ~TemplateEditWindow();

private:
    Ui::TemplateEditWindow *ui;
};

#endif // TEMPLATEEDITWINDOW_H
