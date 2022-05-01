//
// Created by 24100 on 2022/4/29.
//

#ifndef CALCUMAID_PLOTDELEGATE_H
#define CALCUMAID_PLOTDELEGATE_H


#include <QStyledItemDelegate>

class PlotDelegate : public  QStyledItemDelegate
{
Q_OBJECT
public:
	PlotDelegate(QObject *parent= nullptr);
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
	                      const QModelIndex &index) const override;

	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
	                  const QModelIndex &index) const override;

	void updateEditorGeometry(QWidget *editor,
	                          const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	void paint(QPainter *painter,
	           const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	QSize sizeHint(const QStyleOptionViewItem &option,
	               const QModelIndex &index) const override;
};




#endif //CALCUMAID_PLOTDELEGATE_H
