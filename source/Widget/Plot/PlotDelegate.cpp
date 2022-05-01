//
// Created by 24100 on 2022/4/29.
//

#include "PlotDelegate.h"
#include "PlotEdit.h"
#include <QDebug>
PlotDelegate::PlotDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *PlotDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	PlotEdit*  edit=new PlotEdit(parent);
	return edit;
}

void PlotDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString value = index.model()->data(index,Qt::EditRole).toString();
	PlotEdit* plotEdit=static_cast<PlotEdit*>(editor);
	plotEdit->setExpr(value);

}

void PlotDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	PlotEdit* plotEdit=static_cast<PlotEdit*>(editor);


	QString value = plotEdit->getExpr();
	model->setData(index,value,Qt::EditRole);
}

void
PlotDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	editor->setGeometry(option.rect);
}

void PlotDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QStyledItemDelegate::paint(painter, option, index);
}

QSize PlotDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	return QStyledItemDelegate::sizeHint(option, index);
}