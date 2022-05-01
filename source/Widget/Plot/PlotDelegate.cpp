//
// Created by 24100 on 2022/4/29.
//

#include "PlotDelegate.h"
#include "PlotEdit.h"
#include <QDebug>
#include <QApplication>
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
	if(index.isValid())
	{

		QStyleOptionViewItem opt = option;
		opt.state &= ~QStyle::State_HasFocus;
		initMyStyleOption(&opt, index);
		const QWidget *widget = opt.widget;
		QStyle *style = widget ? widget->style() : QApplication::style();
		style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, widget);
	}
}

QSize PlotDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{

	return QStyledItemDelegate::sizeHint(option, index);
}

void PlotDelegate::initMyStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
	QVariant value = index.data(Qt::FontRole);
	if (value.isValid() && !value.isNull()) {
		option->font = qvariant_cast<QFont>(value).resolve(option->font);
		option->fontMetrics = QFontMetrics(option->font);
	}
	option->displayAlignment = Qt::AlignLeft|Qt::AlignVCenter;
	//前景色
	value = index.data(Qt::ForegroundRole);
	if (value.canConvert<QBrush>())
		option->palette.setBrush(QPalette::Text, qvariant_cast<QBrush>(value));
	option->index = index;
	option->features |= QStyleOptionViewItem::HasDisplay;
	option->text =  "f(x)= "+index.data(Qt::DisplayRole).toString();
	option->backgroundBrush = qvariant_cast<QBrush>(index.data(Qt::BackgroundRole));
	option->styleObject = nullptr;

}
