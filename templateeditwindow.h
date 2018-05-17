#ifndef TEMPLATEEDITWINDOW_H
#define TEMPLATEEDITWINDOW_H

#include <QDialog>
#include "templatescorechecker.h"
namespace Ui {
class TemplateEditWindow;
}

class TemplateEditWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TemplateEditWindow(QWidget *parent = 0);
    explicit TemplateEditWindow(QWidget *parent = 0, TemplateScoreChecker* scorechecker=0);
    ~TemplateEditWindow();
protected:
    TemplateScoreChecker * scorechecker;
private:
    Ui::TemplateEditWindow *ui;
};

#endif // TEMPLATEEDITWINDOW_H
