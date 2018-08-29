#include "scorecheckerviewmodel.h"
#include <QPixmap>
#include <QIcon>
#include <QStandardItem>
#include <string>

ScoreCheckerViewModel::ScoreCheckerViewModel(QObject *parent, std::vector<BaseScoreChecker*> *vecScoreCheckers)
    :QAbstractTableModel(parent) //:QStandardItemModel(parent)
{
    this->vecScoreCheckers=vecScoreCheckers;
}

int ScoreCheckerViewModel::rowCount(const QModelIndex & /*parent*/) const
{
   //return 5000;
    return this->vecScoreCheckers->size();
}

int ScoreCheckerViewModel::columnCount(const QModelIndex & /*parent*/) const
{
    return COLUMN_FIXED+1;
}

QVariant ScoreCheckerViewModel::data(const QModelIndex &index, int role) const
{
    QPixmap pic;
    QIcon icon;
    int value;
    switch(index.column())
    {
    case COLUMN_TYPE: //ScoreChecker Type
        switch(role)
        {
        case Qt::DisplayRole:
            //return tr("Path Exist");
            return QString(vecScoreCheckers->at(index.row())->getCheckerType().c_str());
            break;
        case Qt::EditRole:
            //return tr("Path Exist");
            if (vecScoreCheckers->at(index.row())->getCheckerType()=="PathExist")return CHECKER_PATH;
            if (vecScoreCheckers->at(index.row())->getCheckerType()=="RunCommand")return CHECKER_RUN_COMMAND;
            if (vecScoreCheckers->at(index.row())->getCheckerType()=="ValueCheck")return CHECKER_VALUE;
            if (vecScoreCheckers->at(index.row())->getCheckerType()=="RunScript")return CHECKER_RUN_SCRIPT;
            if (vecScoreCheckers->at(index.row())->getCheckerType()=="QuestionAnswer")return CHECKER_QA;
            if (vecScoreCheckers->at(index.row())->getCheckerType()=="Template")return CHECKER_TEMPLATE;
            //return QString(vecScoreCheckers->at(index.row())->getCheckerType().c_str());
            break;
        }
        break;
    case COLUMN_DESCRIPTION: //ScoreChecker Description
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return QString(vecScoreCheckers->at(index.row())->getDescription().c_str());
            break;
        }
        break;
    case COLUMN_INSTRUCTIONS:
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return QString(vecScoreCheckers->at(index.row())->getInstructions().c_str());
            break;
        }
        break;
    case COLUMN_OPT1: //ScoreChecker Opt1
        if (index.model()->data(index.sibling(index.row(),0), Qt::DisplayRole).toString()=="")break;
        value = index.model()->data(index.sibling(index.row(),0), Qt::EditRole).toInt();
        switch(value)
        {
        case CHECKER_PATH: //PathExist
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return QString(static_cast<PathExistScoreChecker*>(vecScoreCheckers->at(index.row()))->getFilepath().c_str());
                break;
            }
            break;
        case CHECKER_RUN_COMMAND: //RunCommand
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return QString(static_cast<RunCommandScoreChecker*>(vecScoreCheckers->at(index.row()))->getCommand().c_str());
                break;
            }
            break;
        case CHECKER_VALUE: //ValueCheck
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return QString(static_cast<ValueScoreChecker*>(vecScoreCheckers->at(index.row()))->getFilepath().c_str());
                break;
            }
            break;
        case CHECKER_RUN_SCRIPT: //ScriptCheck
            //if (role==Qt::EditRole | Qt::DisplayRole)return QString(static_cast<ScriptScoreChecker*>(vecScoreCheckers->at(index.row()))->getScript().c_str());
            if (role==Qt::EditRole | Qt::DisplayRole)return QVariant::fromValue<ScriptScoreChecker*>(static_cast<ScriptScoreChecker*>(vecScoreCheckers->at(index.row())));
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                //return QString(static_cast<ValueScoreChecker*>(vecScoreCheckers->at(index.row()))->getFilepath().c_str());
                //button for editing script will be here
                return tr("RtClick to Edit");
                break;
            }
            break;
        case CHECKER_QA: //QuestionAnswer
            break;
        case CHECKER_TEMPLATE: //TemplateCheck
            if (role==Qt::EditRole | Qt::DisplayRole)return QVariant::fromValue<TemplateScoreChecker*>(static_cast<TemplateScoreChecker*>(vecScoreCheckers->at(index.row())));
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                //return QString(static_cast<ValueScoreChecker*>(vecScoreCheckers->at(index.row()))->getFilepath().c_str());
                //button for editing script will be here
                return tr("RtClick to Edit");
                break;
            }
            break;
        }
        break;
    case COLUMN_OPT2: //ScoreChecker Opt2
        if (index.model()->data(index.sibling(index.row(),0), Qt::DisplayRole).toString()=="")break;
        value = index.model()->data(index.sibling(index.row(),0), Qt::EditRole).toInt();
        //value = index.model()->data(QModelIndex(index.row(),0),Qt::EditRole).toInt();
        switch(value)
        {
        case CHECKER_PATH: //PathCheck
            switch(role)
            {
            case Qt::DisplayRole:
                if (static_cast<PathExistScoreChecker*>(vecScoreCheckers->at(index.row()))->getDesireExist())
                {
                    return QString("Exist");
                }else
                {
                    return QString("!Exist");
                }
                break;
            case Qt::EditRole:
                return static_cast<PathExistScoreChecker*>(vecScoreCheckers->at(index.row()))->getDesireExist();
                break;
            }
            break;
        case CHECKER_RUN_COMMAND: //CommandCheck
            switch(role)
            {
            case Qt::DisplayRole:
                if (static_cast<RunCommandScoreChecker*>(vecScoreCheckers->at(index.row()))->getSearchExist())
                {
                    return QString("Exist");
                }else
                {
                    return QString("!Exist");
                }
                break;
            case Qt::EditRole:
                return static_cast<RunCommandScoreChecker*>(vecScoreCheckers->at(index.row()))->getSearchExist();
                break;
            }
            break;
        case CHECKER_VALUE: //Value Check
            switch(role)
            {
            case Qt::DisplayRole:
                if (static_cast<ValueScoreChecker*>(vecScoreCheckers->at(index.row()))->getDesireExist())
                {
                    return QString("Exist");
                }else
                {
                    return QString("!Exist");
                }
                break;
            case Qt::EditRole:
                return static_cast<ValueScoreChecker*>(vecScoreCheckers->at(index.row()))->getDesireExist();
                break;
            }
            break;
        case CHECKER_RUN_SCRIPT: //ScriptCheck
            switch(role)
            {
            case Qt::DisplayRole:
                if (static_cast<ScriptScoreChecker*>(vecScoreCheckers->at(index.row()))->getDesiredState())
                {
                    return QString("Exist");
                }else
                {
                    return QString("!Exist");
                }
                break;
            case Qt::EditRole:
                return static_cast<ScriptScoreChecker*>(vecScoreCheckers->at(index.row()))->getDesiredState();
                break;
            }
            break;
        case CHECKER_QA: //CompoundCheck
            break;
        case CHECKER_TEMPLATE: //TemplateCheck
            switch(role)
            {
            case Qt::DisplayRole:
                if (static_cast<TemplateScoreChecker*>(vecScoreCheckers->at(index.row()))->getDesiredState())
                {
                    return QString("Exist");
                }else
                {
                    return QString("!Exist");
                }
                break;
            case Qt::EditRole:
                return static_cast<TemplateScoreChecker*>(vecScoreCheckers->at(index.row()))->getDesiredState();
                break;
            }
            break;
        }
        break;
    case COLUMN_SEARCH_STR: //ScoreChecker Opt3
        //return QString("nothing");
        if (index.model()->data(index.sibling(index.row(),0), Qt::DisplayRole).toString()=="")break;
        value = index.model()->data(index.sibling(index.row(),0), Qt::EditRole).toInt();
        switch(value)
        {
        case CHECKER_PATH: //PathCheck
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return QString("Unused");
                break;
            }
        case CHECKER_RUN_COMMAND: //RunCommand
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return QString(static_cast<RunCommandScoreChecker*>(vecScoreCheckers->at(index.row()))->getSearchString().c_str());
                break;
            }
            break;
        case CHECKER_VALUE: //ValueCheck
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return QString(static_cast<ValueScoreChecker*>(vecScoreCheckers->at(index.row()))->getSearchString().c_str());
                break;
            }
            break;
        case CHECKER_RUN_SCRIPT: //ScriptCheck
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return QString(static_cast<ScriptScoreChecker*>(vecScoreCheckers->at(index.row()))->getSearchString().c_str());
                break;
            }
            break;
        case CHECKER_QA: //CompoundCheck
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return QString("UNK");
                break;
            }
        case CHECKER_TEMPLATE: //TemplateCheck
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return QString("Unused");
                break;
            }
            break;
        }
        break;
    case COLUMN_POINTS: //ScoreChecker point value
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return vecScoreCheckers->at(index.row())->getPoints();
            break;
        }
        break;
    case COLUMN_FIXED: //ScoreChecker state
        switch(role)
        {
        case Qt::DisplayRole:
            if (vecScoreCheckers->at(index.row())->getState())
            {
                return QString("True");
            }else
            {
                return QString("False");
            }
            break;
        case Qt::DecorationRole:
            if (vecScoreCheckers->at(index.row())->getState())
            {
                pic= QPixmap("://Imgs/SuccessSignal.xpm");
            }else
            {
                pic= QPixmap("://Imgs/ErrorSignal.xpm");
            }
            icon= QIcon(pic);
            return icon;
            break;
        }
        break;
    default:
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return QString("Row%1, Column%2")
                        .arg(index.row() + 1)
                        .arg(index.column() +1);
        }
        break;
    }
    return QVariant();
}
QVariant ScoreCheckerViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case COLUMN_TYPE:
            return tr("Type");
        case COLUMN_DESCRIPTION:
            return tr("Description");
        case COLUMN_INSTRUCTIONS:
            return tr("Instructions/Question");
        case COLUMN_OPT1:
            return tr("OPT");
        case COLUMN_OPT2:
            return tr("OPT");
            break;
        case COLUMN_SEARCH_STR:
            return tr("SearchStr");
            break;
        case COLUMN_POINTS:
            return tr("Points");
        case COLUMN_FIXED:
            return tr("Fixed");
        default:
            return QVariant();
        }
    }
    if (orientation == Qt::Vertical)
    {
        return section;
    }
    return QVariant();
}
bool ScoreCheckerViewModel::setData(const QModelIndex &index, const QVariant &value, int role= Qt::EditRole)
{
    int typevalue = index.model()->data(index.sibling(index.row(),0), Qt::EditRole).toInt();
    int checktype=value.toInt();
    switch(index.column())
    {
    case COLUMN_TYPE: //ScoreChecker Type
        switch(role)
        {
        case Qt::DisplayRole:
            break;
        case Qt::EditRole:
            switch(checktype)
            {
            case CHECKER_PATH: //PathExist
                vecScoreCheckers->at(index.row())=new PathExistScoreChecker();
                break;
            case CHECKER_RUN_COMMAND: //CommandCheck
                vecScoreCheckers->at(index.row())=new RunCommandScoreChecker();
                break;
            case CHECKER_VALUE: //ValueCheck
                vecScoreCheckers->at(index.row())=new ValueScoreChecker();
                break;
            case CHECKER_RUN_SCRIPT: //ScriptCheck
                vecScoreCheckers->at(index.row())=new ScriptScoreChecker();
                break;
            case CHECKER_QA: //QuestionAnswer
                vecScoreCheckers->at(index.row())=new QuestionAnswerScoreChecker();
                break;
            case CHECKER_TEMPLATE: //TemplateCheck
                vecScoreCheckers->at(index.row())=new TemplateScoreChecker();
                break;
            }
            break;
        }
        break;
    case COLUMN_DESCRIPTION: //ScoreChecker Description
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            vecScoreCheckers->at(index.row())->setDescription(value.toString().toStdString());
            break;
        }
        break;
    case COLUMN_INSTRUCTIONS: //instructions/question
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            vecScoreCheckers->at(index.row())->setInstructions(value.toString().toStdString());
            break;
        }
        break;
        break;
    case COLUMN_OPT1: //ScoreChecker Opt1
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            BaseScoreChecker * basecheck= vecScoreCheckers->at(index.row());
            switch(typevalue)
            {
            case CHECKER_PATH: //PathExist
                static_cast<PathExistScoreChecker*>(basecheck)->setFilepath(value.toString().toStdString());//PathExistScoreChecker * scorecheck= basecheck;
                break;
            case CHECKER_RUN_COMMAND: //CommandCheck
                static_cast<RunCommandScoreChecker*>(basecheck)->setCommand(value.toString().toStdString());
                break;
            case CHECKER_VALUE: //ValueCheck
                static_cast<ValueScoreChecker*>(basecheck)->setFilepath(value.toString().toStdString());
                break;
            case CHECKER_RUN_SCRIPT: //ScriptCheck
                static_cast<ScriptScoreChecker*>(basecheck)->setScript(value.toString().toStdString());
            case CHECKER_QA: //CompoundCheck
                //static_cast<PathExistScoreChecker*>(basecheck)->setDesireExist(value.toBool());
                break;
            case CHECKER_TEMPLATE: //TemplateCheck
                break;
            }

            break;
        }
        break;
    case COLUMN_OPT2: //ScoreChecker Opt2
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            BaseScoreChecker * basecheck= vecScoreCheckers->at(index.row());
            switch(typevalue)
            {
            case CHECKER_PATH: //PathExist
                static_cast<PathExistScoreChecker*>(basecheck)->setDesireExist(value.toBool());//PathExistScoreChecker * scorecheck= basecheck;
                break;
            case CHECKER_RUN_COMMAND: //CommandCheck
                static_cast<RunCommandScoreChecker*>(basecheck)->setSearchExist(value.toBool());
                break;
            case CHECKER_VALUE: //ValueCheck
                static_cast<ValueScoreChecker*>(basecheck)->setDesireExist(value.toBool());
                break;
            case CHECKER_RUN_SCRIPT: //ScriptCheck
                static_cast<ScriptScoreChecker*>(basecheck)->setDesiredState(value.toBool());
                break;
            case CHECKER_QA: //CompoundCheck
                //static_cast<PathExistScoreChecker*>(basecheck)->setDesireExist(value.toBool());
                break;
            case CHECKER_TEMPLATE: //TemplateCheck
                static_cast<TemplateScoreChecker*>(basecheck)->setDesiredState(value.toBool());
                break;
            }
             break;
        }
        break;
    case COLUMN_SEARCH_STR: //Search string
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            BaseScoreChecker * basecheck= vecScoreCheckers->at(index.row());
            switch(typevalue)
            {
            case CHECKER_PATH: //PathExist
                //Nothing to set here
                break;
            case CHECKER_RUN_COMMAND: //CommandCheck
                (static_cast<RunCommandScoreChecker*>(basecheck))->setSearchString(value.toString().toStdString());
                break;
            case CHECKER_VALUE: //ValueCheck
                (static_cast<ValueScoreChecker*>(basecheck))->setSearchString(value.toString().toStdString());
                break;
            case CHECKER_RUN_SCRIPT: //ScriptCheck
                (static_cast<ScriptScoreChecker*>(basecheck))->setSearchString(value.toString().toStdString());
                break;
            case CHECKER_QA: //CompoundCheck
                //static_cast<PathExistScoreChecker*>(basecheck)->setSearchString(value.toString());
                break;
            }
             break;
        }
        break;
    case COLUMN_POINTS: //ScoreChecker point value
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            vecScoreCheckers->at(index.row())->setPoints(value.toInt());
            break;
        }
        break;
    case COLUMN_FIXED: //ScoreChecker state
            vecScoreCheckers->at(index.row())->checkState();
            //vecScoreCheckers->at(index.row()).setPoints(value.toInt());
        break;
    default:
        return false;
        break;
    }
    return true;
}
Qt::ItemFlags  ScoreCheckerViewModel::flags(const QModelIndex &index) const //set the attributes of individual items/cells based on data
{
    if (index.row()==-1) return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
    int typevalue = index.model()->data(index.sibling(index.row(),0), Qt::EditRole).toInt();
    switch (index.column())
    {
    case COLUMN_TYPE:
        //if(index.data(Qt::DisplayRole)!=""){return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;}else{return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;}
        return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
    case COLUMN_DESCRIPTION:
        return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    case COLUMN_INSTRUCTIONS:
        return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    case COLUMN_OPT1:
        //return Qt::ItemIsSelectable;
        if (typevalue==3)return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    case COLUMN_OPT2:
        //return Qt::ItemIsSelectable;
    case COLUMN_SEARCH_STR:

    case COLUMN_POINTS:
        return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    case COLUMN_FIXED:
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    return 0;
}
void ScoreCheckerViewModel::refresh(int column)
{

}
void ScoreCheckerViewModel::insertChecker(BaseScoreChecker *checker)
{
    this->beginInsertRows(QModelIndex(),(int)this->vecScoreCheckers->size(),(int)this->vecScoreCheckers->size());
    this->vecScoreCheckers->push_back(checker);
    this->endInsertRows();

}
void ScoreCheckerViewModel::removeCheckers(QModelIndexList indexlist)
{
    QModelIndex index;
    int a=0;
     foreach(index, indexlist) {
         this->beginRemoveRows(QModelIndex(),index.row()+a,index.row()+a);
         this->vecScoreCheckers->erase(vecScoreCheckers->begin()+index.row()+a);
         this->endRemoveRows();
         a--;
     }

     std::cerr << this->vecScoreCheckers->size() << " scorecheckers remain.\n";
}
void ScoreCheckerViewModel::sort(int column, Qt::SortOrder order)
{
    switch (column)
    {
    case COLUMN_TYPE:
        std::sort(this->vecScoreCheckers->begin(), this->vecScoreCheckers->end(),sortByType);
        break;
    case COLUMN_DESCRIPTION:
        std::sort(this->vecScoreCheckers->begin(), this->vecScoreCheckers->end(),sortByDescription);
        break;
    case COLUMN_POINTS:
        std::sort(this->vecScoreCheckers->begin(), this->vecScoreCheckers->end(),sortByPoints);
        break;
    case COLUMN_FIXED:
        std::sort(this->vecScoreCheckers->begin(), this->vecScoreCheckers->end(),sortBySolved);
        break;
    }
    //reverse if order changed
    if (order==Qt::SortOrder::AscendingOrder)std::reverse(this->vecScoreCheckers->begin(), this->vecScoreCheckers->end());

    //https://forum.qt.io/topic/47206/how-to-refresh-a-qtableview-after-sorting-the-datasource-object/2
    this->layoutChanged(); //lets Qt know that the rows need to be refreshed after the sort
}

bool sortByType(BaseScoreChecker *a, BaseScoreChecker *b)
{
    return a->getCheckerType() > b->getCheckerType();
}
bool sortByDescription(BaseScoreChecker *a, BaseScoreChecker *b)
{
    return a->getDescription() > b->getDescription();
}
bool sortByPoints(BaseScoreChecker *a, BaseScoreChecker *b)
{
    return a->getPoints() > b->getPoints();
}
bool sortBySolved(BaseScoreChecker *a, BaseScoreChecker *b)
{
    return a->getState() > b->getState();
}
