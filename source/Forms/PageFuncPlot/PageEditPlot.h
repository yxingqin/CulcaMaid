//
// Created by 24100 on 2022/4/30.
//

#ifndef CALCUMAID_PAGEEDITPLOT_H
#define CALCUMAID_PAGEEDITPLOT_H

#include <QFrame>
#include "Plot/PlotModel.h"
#include "Plot/PlotDelegate.h"


QT_BEGIN_NAMESPACE
namespace Ui
{
class PageEditPlot;
}
QT_END_NAMESPACE

class PageEditPlot : public QFrame
{
Q_OBJECT

public:
	explicit PageEditPlot(QWidget *parent = nullptr);
	~PageEditPlot() override;

	signals:
	void sendExpr(const QString& expr);


private:

	Ui::PageEditPlot *ui;
};


#endif //CALCUMAID_PAGEEDITPLOT_H
