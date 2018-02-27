#include "myscoringmodel.h"
#include <QPixmap>
#include <QIcon>
#include <QStandardItem>
#include <string>
MyScoringModel::MyScoringModel(QObject *parent, std::vector<BaseScoreChecker*> *vecScoreCheckers)
    :QAbstractTableModel(parent) //:QStandardItemModel(parent)
{
    this->vecScoreCheckers=vecScoreCheckers;
}

int MyScoringModel::rowCount(const QModelIndex & /*parent*/) const
{
   //return 5000;
    return this->vecScoreCheckers->size();
}

int MyScoringModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 7;
}

QVariant MyScoringModel::data(const QModelIndex &index, int role) const
{
    QPixmap pic;
    QIcon icon;
    int value;
    switch(index.column())
    {
    case 0: //ScoreChecker Type
        switch(role)
        {
        case Qt::DisplayRole:
            //return tr("Path Exist");
            return QString(vecScoreCheckers->at(index.row())->getCheckerType().c_str());
            break;
        case Qt::EditRole:
            //return tr("Path Exist");
            if (vecScoreCheckers->at(index.row())->getCheckerType()=="PathExist")return 0;
            if (vecScoreCheckers->at(index.row())->getCheckerType()=="RunCommand")return 1;
            if (vecScoreCheckers->at(index.row())->getCheckerType()=="ValueCheck")return 2;
            if (vecScoreCheckers->at(index.row())->getCheckerType()=="RunScript")return 3;
            if (vecScoreCheckers->at(index.row())->getCheckerType()=="Compound")return 4;
            //return QString(vecScoreCheckers->at(index.row())->getCheckerType().c_str());
            break;
        }
        break;
    case 1: //ScoreChecker Description
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return QString(vecScoreCheckers->at(index.row())->getDescription().c_str());
            break;
        }
        break;
    case 2: //ScoreChecker Opt1
        if (index.model()->data(index.sibling(index.row(),0), Qt::DisplayRole).toString()=="")break;
        value = index.model()->data(index.sibling(index.row(),0), Qt::EditRole).toInt();
        switch(value)
        {
        case 0: //PathExist
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return QString(static_cast<PathExistScoreChecker*>(vecScoreCheckers->at(index.row()))->getFilepath().c_str());
                break;
            }
            break;
        case 1: //RunCommand
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return QString(static_cast<RunCommandScoreChecker*>(vecScoreCheckers->at(index.row()))->getCommand().c_str());
                break;
            }
            break;
        case 2: //ValueCheck
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return QString(static_cast<ValueScoreChecker*>(vecScoreCheckers->at(index.row()))->getFilepath().c_str());
                break;
            }
            break;
        case 3: //ScriptCheck
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                //return QString(static_cast<ValueScoreChecker*>(vecScoreCheckers->at(index.row()))->getFilepath().c_str());
                //button for editing script will be here

                break;
            }
            break;
        case 4: //CompoundCheck
            break;
        }
        break;
    case 3: //ScoreChecker Opt2
        if (index.model()->data(index.sibling(index.row(),0), Qt::DisplayRole).toString()=="")break;
        value = index.model()->data(index.sibling(index.row(),0), Qt::EditRole).toInt();
        //value = index.model()->data(QModelIndex(index.row(),0),Qt::EditRole).toInt();
        switch(value)
        {
        case 0: //PathCheck
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
        case 1: //CommandCheck
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
        case 2: //Value Check
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
        case 3: //ScriptCheck
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
        case 4: //CompoundCheck
            break;
        }
        break;
    case 4: //ScoreChecker Opt3
        if (index.model()->data(index.sibling(index.row(),0), Qt::DisplayRole).toString()=="")break;
        value = index.model()->data(index.sibling(index.row(),0), Qt::EditRole).toInt();
        switch(value)
        {
        case 0: //PathCheck
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return QString("Unused");
                break;
            }
        case 1: //RunCommand
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return static_cast<RunCommandScoreChecker*>(vecScoreCheckers->at(index.row()))->getSearchString().c_str();
                break;
            }
            break;
        case 2: //ValueCheck
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return static_cast<ValueScoreChecker*>(vecScoreCheckers->at(index.row()))->getSearchString().c_str();
                break;
            }
            break;
        case 3: //ScriptCheck
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return static_cast<ScriptScoreChecker*>(vecScoreCheckers->at(index.row()))->getSearchString().c_str();
                break;
            }
            break;
        case 4: //CompoundCheck
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return QString("UNK");
                break;
            }
            break;
        }
        break;
    case 5: //ScoreChecker point value
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return vecScoreCheckers->at(index.row())->getPoints();
            break;
        }
        break;
    case 6: //ScoreChecker state
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
QVariant MyScoringModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("Type");
        case 1:
            return tr("Description");
        case 2:

        case 3:
            return tr("OPT");
            break;
        case 4:
            return tr("SearchStr");
            break;
        case 5:
            return tr("Points");
        case 6:
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
bool MyScoringModel::setData(const QModelIndex &index, const QVariant &value, int role= Qt::EditRole)
{
    int typevalue = index.model()->data(index.sibling(index.row(),0), Qt::EditRole).toInt();
    int checktype=value.toInt();
    switch(index.column())
    {
    case 0: //ScoreChecker Type
        switch(role)
        {
        case Qt::DisplayRole:
            break;
        case Qt::EditRole:
            switch(checktype)
            {
            case 0: //PathExist
                vecScoreCheckers->at(index.row())=new PathExistScoreChecker();
                break;
            case 1: //CommandCheck
                vecScoreCheckers->at(index.row())=new RunCommandScoreChecker();
                break;
            case 2: //ValueCheck
                vecScoreCheckers->at(index.row())=new ValueScoreChecker();
                break;
            case 3: //ScriptCheck
                vecScoreCheckers->at(index.row())=new ScriptScoreChecker();
                break;
            case 4: //CompoundCheck
                //vecScoreCheckers->at(index.row())=new PathExistScoreChecker();
                break;
            }
            break;
        }
        break;
    case 1: //ScoreChecker Description
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            vecScoreCheckers->at(index.row())->setDescription(value.toString().toStdString());
            break;
        }
        break;
    case 2: //ScoreChecker Opt1
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            BaseScoreChecker * basecheck= vecScoreCheckers->at(index.row());
            static_cast<PathExistScoreChecker*>(basecheck)->setFilepath(value.toString().toStdString());//PathExistScoreChecker * scorecheck= basecheck;
            //static_cast<PathExistScoreChecker*>(vecScoreCheckers->at(index.row())).setFilepath(value.toString().toStdString());
            //scorecheck->setFilepath(value.toString().toStdString());
            //vecScoreCheckers->at(index.row())
            break;
        }
        break;
    case 3: //ScoreChecker Opt2
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            BaseScoreChecker * basecheck= vecScoreCheckers->at(index.row());
            switch(typevalue)
            {
            case 0: //PathExist
                static_cast<PathExistScoreChecker*>(basecheck)->setDesireExist(value.toBool());//PathExistScoreChecker * scorecheck= basecheck;
                break;
            case 1: //CommandCheck
                static_cast<RunCommandScoreChecker*>(basecheck)->setSearchExist(value.toBool());
                break;
            case 2: //ValueCheck
                static_cast<ValueScoreChecker*>(basecheck)->setDesireExist(value.toBool());
                break;
            case 3: //ScriptCheck
                static_cast<ScriptScoreChecker*>(basecheck)->setDesiredState(value.toBool());
                break;
            case 4: //CompoundCheck
                //static_cast<PathExistScoreChecker*>(basecheck)->setDesireExist(value.toBool());
                break;
            }
             break;
        }
        break;
    case 4: //Unused column
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            BaseScoreChecker * basecheck= vecScoreCheckers->at(index.row());
            switch(typevalue)
            {
            case 0: //PathExist
                //Nothing to set here
                break;
            case 1: //CommandCheck
                (static_cast<RunCommandScoreChecker*>(basecheck))->setSearchString(value.toString().toStdString());
                break;
            case 2: //ValueCheck
                static_cast<ValueScoreChecker*>(basecheck)->setSearchString(value.toString().toStdString());
                break;
            case 3: //ScriptCheck
                static_cast<ScriptScoreChecker*>(basecheck)->setSearchString(value.toString().toStdString());
                break;
            case 4: //CompoundCheck
                //static_cast<PathExistScoreChecker*>(basecheck)->setSearchString(value.toString());
                break;
            }
             break;
        }
        break;
    case 5: //ScoreChecker point value
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            vecScoreCheckers->at(index.row())->setPoints(value.toInt());
            break;
        }
        break;
    case 6: //ScoreChecker state
            vecScoreCheckers->at(index.row())->checkState();
            //vecScoreCheckers->at(index.row()).setPoints(value.toInt());
        break;
    default:
        return false;
        break;
    }
    return true;
}
Qt::ItemFlags  MyScoringModel::flags(const QModelIndex &index) const //set the attributes of individual items/cells based on data
{
    switch (index.column())
    {
    case 0:
        if(index.data(Qt::DisplayRole)!=""){return Qt::ItemIsEnabled | Qt::ItemIsSelectable;}else{return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;}
    case 1:
        //return Qt::ItemIsSelectable;
    case 2:
        //return Qt::ItemIsSelectable;
    case 3:
        //return Qt::ItemIsSelectable;
    case 4:

    case 5:
        return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    case 6:
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    return 0;
}
void MyScoringModel::refresh(int column)
{

}
void MyScoringModel::insertChecker(BaseScoreChecker *checker)
{
    this->beginInsertRows(QModelIndex(),(int)this->vecScoreCheckers->size(),(int)this->vecScoreCheckers->size());
    this->vecScoreCheckers->push_back(checker);
    this->endInsertRows();

}
