//
// Created by 24100 on 2022/4/5.
//

#ifndef CALCULMAID_PAGESCIENCE_H
#define CALCULMAID_PAGESCIENCE_H

#include <QFrame>


QT_BEGIN_NAMESPACE
namespace Ui
{
class PageScience;
}
QT_END_NAMESPACE

class PageScience : public QFrame
{
Q_OBJECT

public:
	explicit PageScience(QWidget *parent = nullptr);
	~PageScience() override;

private:
	Ui::PageScience *ui;
};


#endif //CALCULMAID_PAGESCIENCE_H
