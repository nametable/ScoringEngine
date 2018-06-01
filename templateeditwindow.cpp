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

    actionInsert_Blank = new QAction(this);
    actionInsert_Blank->setObjectName(QStringLiteral("actionInsert_Blank"));
    actionDelete = new QAction(this);
    actionDelete->setObjectName(QStringLiteral("actionDelete"));
    actionInsert_Blank->setText(QApplication::translate("MainWindow", "Insert Blank", nullptr));
    actionDelete->setText(QApplication::translate("MainWindow", "Delete", nullptr));
    menuBar = new QMenuBar(this);
    menuBar->setObjectName(QStringLiteral("menuBar"));
    menuEdit = new QMenu(menuBar);
    menuEdit->setObjectName(QStringLiteral("menuEdit"));
    menuCheckers = new QMenu(menuBar);
    menuCheckers->setObjectName(QStringLiteral("menuCheckers"));
    menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", nullptr));
    menuCheckers->setTitle(QApplication::translate("MainWindow", "Checkers", nullptr));


    //ui->verticalLayout_2->addWidget(menuBar);
    ui->verticalLayout->insertWidget(0, menuBar);
    setTabOrder(menuBar, ui->mainTable);
    setTabOrder(ui->mainTable, ui->buttonBox);
    menuBar->addAction(menuCheckers->menuAction());
    menuBar->addAction(menuEdit->menuAction());
    menuEdit->addAction(actionDelete);
    menuCheckers->addAction(actionInsert_Blank);
    //QAction *action1 = new QAction("Del", toolBar);

    scoringmodel= new ScoreCheckerViewModel(this, this->scorechecker->vecScoreCheckers);
    scoringdelegate= new ScoreCheckerViewDelegate(this);
    this->scorechecker->vecScoreCheckers->push_back(new PathExistScoreChecker());
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
