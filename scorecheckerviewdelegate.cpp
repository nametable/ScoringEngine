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
    case 0:
        //checker[0]->
        //break;
        //if(index.data(Qt::DisplayRole)!="")break;
        combo->addItem(tr("Path Exist"));
        combo->addItem(tr("Command Output"));
        combo->addItem(tr("Value"));
        combo->addItem(tr("Script"));
        combo->addItem(tr("Compound - not working"));
        combo->addItem(tr("Template - beta"));
        combo->setCurrentIndex(0);
        return combo;
        break;
    case 1:
        //break;
        //return QItemDelegate::createEditor(parent,option,index);
        //spinbox->setFrame(false);
        return QStyledItemDelegate::createEditor(parent,option,index);
        break;
    case 2: //Opt1
        if (index.model()->data(index.sibling(index.row(),0), Qt::DisplayRole).toString()=="")break;
        value = index.model()->data(index.sibling(index.row(),0), Qt::EditRole).toInt();
        switch(value)
        {
        case 0: //PathCheck
            break;
        case 1: //CommandCheck
            break;
        case 2: //ValueCheck
            break;
        case 3: //ScriptCheck
            //button->setText("EditScript");
            //return button;
            break;
        case 4: //CompoundCheck
            button->setText("GoInline");
            return button;
        }
        break;
    case 3:
        combo->addItem(tr("!Exist"));
        combo->addItem(tr("Exist"));
        combo->setCurrentIndex(index.data(Qt::EditRole).toBool());
        return combo;
    case 4: //SearchString
        //return button;
    case 5: //Points
        break;
    case 6:
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
    case 0: //ScoreChecker Type
        combo = static_cast<QComboBox*>(editor);
        model->setData(index,combo->currentIndex());

        break;
    case 1: //ScoreChecker Description
        lineedit = static_cast<QLineEdit*>(editor);
        model->setData(index,lineedit->text());

        break;
    case 2: //Opt1
        if (index.model()->data(index.sibling(index.row(),0), Qt::DisplayRole).toString()=="")break;
        value = index.model()->data(index.sibling(index.row(),0), Qt::EditRole).toInt();
        switch(value)
        {
        case 0: //PathCheck
            lineedit = static_cast<QLineEdit*>(editor);
            model->setData(index,lineedit->text());
            break;
        case 1: //CommandCheck
        case 2: //ValueCheck
            lineedit = static_cast<QLineEdit*>(editor);
            model->setData(index,lineedit->text());
            break;
        case 3: //ScriptCheck
            break;
        case 4: //CompoundCheck
            break;
        }
        break;
    case 3: //ScoreChecker Desired State
        combo = static_cast<QComboBox*>(editor);
        model->setData(index,combo->currentIndex());
        break;
    case 4:
        lineedit = static_cast<QLineEdit*>(editor);
        model->setData(index,lineedit->text());
        break;
    case 5: //ScoreChecker point value
        spinbox = static_cast<QSpinBox*>(editor);
        model->setData(index,spinbox->value());
            //vecScoreCheckers->at(index.row()).setPoints(value.toInt());
        break;
    case 6: //ScoreChecker state
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
         case 2:
             switch (model->data(index.sibling(index.row(),0),Qt::EditRole).toInt())
             {
             case 0: ; //PathExist
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
             case 1:
                 break;
             case 2:
                 {
                     QMouseEvent * e = (QMouseEvent *)event;
                     if (e->button()==Qt::RightButton)
                     {
                         QFileDialog opendialog(0, tr("Select File"));

                         QString filename=opendialog.getOpenFileName(0,tr("Select Path"),model->data(index).toString());
                         if (filename.length()>0)model->setData(index, filename);
                     }
                 }
                 break;
             case 3:
                 {
                     QMouseEvent * e = (QMouseEvent *)event;
                     if (e->button()==Qt::RightButton)
                     {
                         ScriptEditDialog *scriptedit=new ScriptEditDialog(0,model->data(index, Qt::EditRole | Qt::DisplayRole).toString().toStdString() );
                         scriptedit->exec();
                         //model->data(index, Qt::EditRole)
                         if (scriptedit->getScript()!="")model->setData(index, scriptedit->getScript().c_str());
                     }
                 }
                 break;
             case 5: //TemplateChecker
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
         case 6:

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
