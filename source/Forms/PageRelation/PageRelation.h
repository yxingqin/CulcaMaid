//
// Created by 24100 on 2022/4/5.
//

#ifndef CALCULMAID_PAGERELATION_H
#define CALCULMAID_PAGERELATION_H

#include <QFrame>


QT_BEGIN_NAMESPACE
namespace Ui
{
class PageRelation;
}
QT_END_NAMESPACE

class PageRelation : public QFrame
{
Q_OBJECT

public:
	explicit PageRelation(QWidget *parent = nullptr);
	~PageRelation() override;

private:
	Ui::PageRelation *ui;
};


#endif //CALCULMAID_PAGERELATION_H
