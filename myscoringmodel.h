#ifndef MYSCORINGMODEL_H
#define MYSCORINGMODEL_H
#include <QAbstractTableModel>
#include <QStandardItemModel>
#include <vector>
#include "pathexistscorechecker.h"
#include "runcommandscorechecker.h"
#include "valuescorechecker.h"
#include "scriptscorechecker.h"

class MyScoringModel : public QAbstractTableModel //QStandardItemModel //
{
    Q_OBJECT
public:
    MyScoringModel(QObject *parent, std::vector<BaseScoreChecker*> *vecScoreCheckers );
    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void sort(int column, Qt::SortOrder order);
    void refresh(int column);
    void insertChecker(BaseScoreChecker *checker);
private:
    std::vector<BaseScoreChecker*> *vecScoreCheckers;
};
bool sortByType(BaseScoreChecker* a, BaseScoreChecker* b);
bool sortByDescription(BaseScoreChecker* a, BaseScoreChecker* b);
bool sortByPoints(BaseScoreChecker* a, BaseScoreChecker* b);
bool sortBySolved(BaseScoreChecker* a, BaseScoreChecker* b);
#endif // MYSCORINGMODEL_H
