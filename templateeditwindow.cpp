#include "templateeditwindow.h"
#include "ui_templateeditwindow.h"

TemplateEditWindow::TemplateEditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TemplateEditWindow)
{
    ui->setupUi(this);
}
TemplateEditWindow::TemplateEditWindow(QWidget *parent, TemplateScoreChecker * scorechecker ) :
    QDialog(parent),
    ui(new Ui::TemplateEditWindow)
{
    ui->setupUi(this);
    this->scorechecker=scorechecker;
    this->setWindowTitle(QString(this->scorechecker->getDescription().c_str()));
    scoringmodel= new ScoreCheckerViewModel(this, this->scorechecker->vecScoreCheckers);
    scoringdelegate= new ScoreCheckerViewDelegate(this);
    this->SetupTable();
}
TemplateEditWindow::~TemplateEditWindow()
{
    delete ui;
}
void TemplateEditWindow::SetupTable()
{
    ui->mainTable->setModel(this->scoringmodel);
    ui->mainTable->setItemDelegate(this->scoringdelegate);
    ui->mainTable->setDragEnabled(true);
    ui->mainTable->setDropIndicatorShown(true);
    ui->mainTable->setDragDropMode(QAbstractItemView::DragDrop);
    ui->mainTable->setDragDropOverwriteMode(false);
    //leftTableView->setDragDropMode(QAbstractItemView::DragOnly);
    //ui->mainTable->setDragDropMode(QAbstractItemView:: InternalMove);

    QHeaderView *verticalHeader = ui->mainTable->verticalHeader();
    QHeaderView *horizontalHeader = ui->mainTable->horizontalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(30);

    horizontalHeader->setDefaultSectionSize(60);
}
