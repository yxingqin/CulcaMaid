#ifndef PLOTMODEL_H
#define PLOTMODEL_H

#include <QAbstractListModel>
#include "PlotPainter.h"

class PlotModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit PlotModel(PlotPainter* painter,QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)override;
	Qt::ItemFlags flags(const QModelIndex &index) const override;
private:
	PlotPainter* painter;
};

#endif // PLOTMODEL_H
