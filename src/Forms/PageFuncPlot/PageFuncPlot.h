//
// Created by 24100 on 2022/4/5.
//

#ifndef CALCULMAID_PAGEFUNCPLOT_H
#define CALCULMAID_PAGEFUNCPLOT_H

#include <QFrame>


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

private:
	Ui::PageFuncPlot *ui;
};


#endif //CALCULMAID_PAGEFUNCPLOT_H
