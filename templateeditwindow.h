#ifndef TEMPLATEEDITWINDOW_H
#define TEMPLATEEDITWINDOW_H

#include <QDialog>
#include "templatescorechecker.h"
#include "scorecheckerviewdelegate.h"
#include "scorecheckerviewmodel.h"
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
    ScoreCheckerViewModel *scoringmodel;
    ScoreCheckerViewDelegate *scoringdelegate;
    Ui::TemplateEditWindow *ui;
    void SetupTable();
};

#endif // TEMPLATEEDITWINDOW_H
