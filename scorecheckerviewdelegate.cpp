#include "scorecheckerviewdelegate.h"
#include <QPushButton>
#include <QtGui>
#include <QDialog>
#include <QApplication>
#include <QComboBox>
#include <QSpinBox>
#include <QFileDialog>
#include <QLineEdit>
#include <iostream>
#include "scripteditdialog.h"
#include "templateeditwindow.h"
ScoreCheckerViewDelegate::ScoreCheckerViewDelegate(QObject *parent)
{
}
QWidget * ScoreCheckerViewDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                      const QModelIndex &index) const
{
    QComboBox * combo= new QComboBox(parent);
    QPushButton * button= new QPushButton(parent);
    QSpinBox * spinbox= new QSpinBox(parent);
    QString datavar;
    int value;
    switch(index.column())
    {
    case COLUMN_TYPE:
        //checker[0]->
        //break;
        //if(index.data(Qt::DisplayRole)!="")break;
        combo->addItem(tr("Path Exist"));
        combo->addItem(tr("Command Output"));
        combo->addItem(tr("Value"));
        combo->addItem(tr("Script"));
        combo->addItem(tr("QuestionAnswer"));
        combo->addItem(tr("Template - beta"));
        combo->setCurrentIndex(0);
        return combo;
        break;
    case COLUMN_DESCRIPTION:
        //break;
        //return QItemDelegate::createEditor(parent,option,index);
        //spinbox->setFrame(false);
        return QStyledItemDelegate::createEditor(parent,option,index);
        break;
    case COLUMN_OPT1: //Opt1
        if (index.model()->data(index.sibling(index.row(),0), Qt::DisplayRole).toString()=="")break;
        value = index.model()->data(index.sibling(index.row(),0), Qt::EditRole).toInt();
        switch(value)
        {
        case CHECKER_PATH: //PathCheck
            break;
        case CHECKER_RUN_COMMAND: //CommandCheck
            break;
        case CHECKER_VALUE: //ValueCheck
            break;
        case CHECKER_RUN_SCRIPT: //ScriptCheck
            break;
        case CHECKER_QA: //QuestionAnswer
            break;
        }
        break;
    case COLUMN_OPT2:
        combo->addItem(tr("!Exist"));
        combo->addItem(tr("Exist"));
        combo->setCurrentIndex(index.data(Qt::EditRole).toBool());
        return combo;
    case COLUMN_SEARCH_STR: //SearchString
        //return button;
    case COLUMN_POINTS: //Points
        break;
    case COLUMN_FIXED:
        button->setText(tr("HI"));
        return button;
    //default:

    }
    return QStyledItemDelegate::createEditor(parent,option,index);
}

void ScoreCheckerViewDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //QString value= index.model()->data(index, Qt::EditRole).toString();
    //QComboBox * combo= static_cast<QComboBox *>(editor);
    //combo->addItem(tr("Test Item"));
    //editor->setProperty()

    //QItemDelegate::setEditorData(editor,index);
    int value = index.model()->data(index, Qt::EditRole).toInt();
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);

    QStyledItemDelegate::setEditorData(editor,index);
}
void ScoreCheckerViewDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                  const QModelIndex &index) const
{
    QLineEdit *lineedit;
    QSpinBox * spinbox;
    QComboBox * combo;
    int value;
    switch(index.column())
    {
    case COLUMN_TYPE: //ScoreChecker Type
        combo = static_cast<QComboBox*>(editor);
        model->setData(index,combo->currentIndex());

        break;
    case COLUMN_DESCRIPTION: //ScoreChecker Description
        lineedit = static_cast<QLineEdit*>(editor);
        model->setData(index,lineedit->text());

        break;
    case COLUMN_INSTRUCTIONS: //Instructions/Question
        lineedit = static_cast<QLineEdit*>(editor);
        model->setData(index,lineedit->text());

        break;
    case COLUMN_OPT1: //Opt1
        if (index.model()->data(index.sibling(index.row(),0), Qt::DisplayRole).toString()=="")break;
        value = index.model()->data(index.sibling(index.row(),0), Qt::EditRole).toInt();
        switch(value)
        {
        case CHECKER_PATH: //PathCheck
            lineedit = static_cast<QLineEdit*>(editor);
            model->setData(index,lineedit->text());
            break;
        case CHECKER_RUN_COMMAND: //CommandCheck
        case CHECKER_VALUE: //ValueCheck
            lineedit = static_cast<QLineEdit*>(editor);
            model->setData(index,lineedit->text());
            break;
        case CHECKER_RUN_SCRIPT: //ScriptCheck
            break;
        case CHECKER_QA: //CompoundCheck
            break;
        }
        break;
    case COLUMN_OPT2: //ScoreChecker Desired State
        combo = static_cast<QComboBox*>(editor);
        model->setData(index,combo->currentIndex());
        break;
    case COLUMN_SEARCH_STR:
        lineedit = static_cast<QLineEdit*>(editor);
        model->setData(index,lineedit->text());
        break;
    case COLUMN_POINTS: //ScoreChecker point value
        spinbox = static_cast<QSpinBox*>(editor);
        model->setData(index,spinbox->value());
            //vecScoreCheckers->at(index.row()).setPoints(value.toInt());
        break;
    case COLUMN_FIXED: //ScoreChecker state
        break;
    default:
        break;
    }
}
bool ScoreCheckerViewDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
     if( event->type() == QEvent::MouseButtonPress)
     {
         switch(index.column())
         {
         case COLUMN_OPT1:
             switch (model->data(index.sibling(index.row(),0),Qt::EditRole).toInt())
             {
             case CHECKER_PATH: ; //PathExist
                 {
                     QMouseEvent * e = (QMouseEvent *)event;
                     if (e->button()==Qt::RightButton)
                     {
                         QFileDialog opendialog(0, tr("Select Path"));

                         QString filename=opendialog.getOpenFileName(0,tr("Select Path"),model->data(index).toString());
                         if (filename.length()>0)model->setData(index, filename);
                     }
                 }
                 break;
             case CHECKER_VALUE:
                 break;
             case CHECKER_RUN_COMMAND:
                 {
                     QMouseEvent * e = (QMouseEvent *)event;
                     if (e->button()==Qt::RightButton)
                     {
                         QFileDialog opendialog(nullptr, tr("Select File"));

                         QString filename=opendialog.getOpenFileName(nullptr,tr("Select Path"),model->data(index).toString());
                         if (filename.length()>0)model->setData(index, filename);
                     }
                 }
                 break;
             case CHECKER_RUN_SCRIPT:
                 {
                     QMouseEvent * e = (QMouseEvent *)event;
                     if (e->button()==Qt::RightButton)
                     {
                         ScriptEditDialog *scriptedit=new ScriptEditDialog(0,model->data(index, Qt::EditRole | Qt::DisplayRole).value<ScriptScoreChecker*>() );
                         scriptedit->exec();
                         //model->data(index, Qt::EditRole)
                         //if (scriptedit->getScript()!="")model->setData(index, scriptedit->getScript().c_str());
                     }
                 }
                 break;
             case CHECKER_TEMPLATE: //TemplateChecker
                 QMouseEvent * e = (QMouseEvent *)event;
                 if (e->button()==Qt::RightButton)
                 {
                     TemplateEditWindow *templatewindow=new TemplateEditWindow(0,model->data(index, Qt::EditRole | Qt::DisplayRole).value<TemplateScoreChecker*>() );
                     templatewindow->exec();
                     //model->data(index, Qt::EditRole)
                     //if (scriptedit->getScript()!="")model->setData(index, scriptedit->getScript().c_str());
                 }
                 break;
             }
             break;
         case COLUMN_FIXED:

             QMouseEvent * e = (QMouseEvent *)event;
             //std::cout << "Button Clicked in col #7\n";
             model->setData(index,1); //trigger a check
             return true;

             break;
         }
     }
     return QStyledItemDelegate::editorEvent(event, model, option, index);
}
void ScoreCheckerViewDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
void ScoreCheckerViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    /*QStyleOptionButton button;
    QRect r = option.rect;//getting the rect of the cell
    int x,y,w,h;
    x = r.left() + r.width() - 60;//the X coordinate
    y = r.top();//the Y coordinate
    w = 60;//button width
    h = 30;//button height
    button.rect = QRect(x,y,w,h);
    button.text = "=^.^=";
    button.state = QStyle::State_Enabled;

    QApplication::style()->drawControl( QStyle::CE_PushButton, &button, painter);*/

    //QItemDelegate::paint(painter, option, index);
    QStyledItemDelegate::paint(painter, option, index);

}
