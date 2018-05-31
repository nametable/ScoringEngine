#ifndef TEMPLATEEDITWINDOW_H
#define TEMPLATEEDITWINDOW_H

#include <QDialog>
#include "templatescorechecker.h"
#include "mydelegate.h"
#include "myscoringmodel.h"
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
    MyScoringModel *scoringmodel;
    MyDelegate *scoringdelegate;
    Ui::TemplateEditWindow *ui;
    void SetupTable();
};

#endif // TEMPLATEEDITWINDOW_H
