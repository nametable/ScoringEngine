#ifndef TEMPLATEEDITWINDOW_H
#define TEMPLATEEDITWINDOW_H

#include <QDialog>
#include "templatescorechecker.h"
#include "scorecheckerviewdelegate.h"
#include "scorecheckerviewmodel.h"
#include "QMenuBar"
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
    QMenuBar * menuBar;
    QMenu * menuEdit;
    QMenu * menuCheckers;
    QAction *actionInsert_Blank;
    QAction *actionDelete;
    Ui::TemplateEditWindow *ui;
    void SetupTable();
};

#endif // TEMPLATEEDITWINDOW_H
