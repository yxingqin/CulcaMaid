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
	void setModel(PlotModel* model);

public slots:
	void enterNumber(const QString &t);
	void enterOpt(const QString &t);
	void enterPoint();
	void enterClear();
	void enterBackspace();
	void enterParenLeft();
	void enterParenRight();
	void enterFunc(const QString &t);
	void enterValue(const QString& t);
	void enterFrequentExpr1(const QString& t);
	void enterFrequentExpr2(const QString& t);


private:
	PlotDelegate* delegate;
	PlotModel* m_model;
	Ui::PageEditPlot *ui;
};


#endif //CALCUMAID_PAGEEDITPLOT_H
