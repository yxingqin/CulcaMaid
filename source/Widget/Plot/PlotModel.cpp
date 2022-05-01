#include "PlotModel.h"

PlotModel::PlotModel(PlotPainter* painter,QObject *parent)
    : painter(painter),QAbstractListModel(parent)
{
}

QVariant PlotModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	return QVariant();
}

int PlotModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
	return painter->plotCount();
}

QVariant PlotModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		int row=index.row();
		if(row<painter->plotCount())
			return painter->getPlotExprAt(row);
	}
    return QVariant();
}

bool PlotModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (index.isValid() && role == Qt::EditRole)
	{
		int row = index.row();
		if (row < painter->plotCount())
		{
			painter->setPlotExprAt(row, value.toString());

			emit dataChanged(index, index, QVector<int>() << role);
			return true;
		}
	}
	return false;
}

Qt::ItemFlags PlotModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}
