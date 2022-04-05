//
// Created by 24100 on 2022/4/5.
//

#ifndef CALCULMAID_PAGEDATE_H
#define CALCULMAID_PAGEDATE_H

#include <QFrame>


QT_BEGIN_NAMESPACE
namespace Ui
{
class PageDate;
}
QT_END_NAMESPACE

class PageDate : public QFrame
{
Q_OBJECT

public:
	explicit PageDate(QWidget *parent = nullptr);
	~PageDate() override;

private:
	Ui::PageDate *ui;
};


#endif //CALCULMAID_PAGEDATE_H
