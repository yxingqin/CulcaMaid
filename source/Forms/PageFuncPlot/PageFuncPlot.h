//
// Created by 24100 on 2022/4/30.
//

#ifndef CALCUMAID_PAGEFUNCPLOT_H
#define CALCUMAID_PAGEFUNCPLOT_H

#include <QFrame>
#include "Plot/PlotPainter.h"


QT_BEGIN_NAMESPACE
namespace Ui
{
class PageFuncPlot;
}
QT_END_NAMESPACE

class PageFuncPlot : public QFrame
{
Q_OBJECT

public:
	explicit PageFuncPlot(QWidget *parent = nullptr);
	~PageFuncPlot() override;
	PlotPainter* getPainter()const;
private:
	Ui::PageFuncPlot *ui;
};


#endif //CALCUMAID_PAGEFUNCPLOT_H
