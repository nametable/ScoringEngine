#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class startdialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent = nullptr);
    ~StartDialog();

private slots:

    void on_btnSingle_clicked();

    void on_btnMulti_clicked();

    void on_btnEditor_clicked();

private:
    Ui::startdialog *ui;
    MainWindow *editorWindow;
};

#endif // STARTDIALOG_H
