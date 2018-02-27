#include "pathexistscorechecker.h"

PathExistScoreChecker::PathExistScoreChecker()
{
    this->filepath="/home/logan/";
    this->points=1;
    this->desireExist=true;
    this->checkerType="PathExist";
}
void PathExistScoreChecker::checkState()
{
    this->state=(boost::filesystem::exists(filepath) == this->desireExist);
    if (this->state){this->soundWin();}else{this->soundLose();}
}
void PathExistScoreChecker::setFilepath(std::string newFilepath)
{
    this->filepath=newFilepath;
}
void PathExistScoreChecker::setDesireExist(bool newDesireExist)
{
    this->desireExist=newDesireExist;
}
std::string PathExistScoreChecker::getFilepath()
{
    return this->filepath;
}
bool PathExistScoreChecker::getDesireExist()
{
    return this->desireExist;
}

/*
static QWidget * PathExistScoreChecker::createEditor(QWidget *parent, QStyleOptionViewItem &option,
                      QModelIndex &index)
{

}

static void PathExistScoreChecker::setEditorData(QWidget *editor, QModelIndex &index)
{

}
static void PathExistScoreChecker::setModelData(QWidget *editor, QAbstractItemModel *model,
                  QModelIndex &index)
{

}

static void PathExistScoreChecker::updateEditorGeometry(QWidget *editor, QStyleOptionViewItem &option, QModelIndex &index)
{

}
static void PathExistScoreChecker::paint(QPainter * painter, QStyleOptionViewItem & option, QModelIndex & index)
{

}
static bool PathExistScoreChecker::editorEvent(QEvent *event, QAbstractItemModel *model, QStyleOptionViewItem &option, QModelIndex &index)
{

}
*/

