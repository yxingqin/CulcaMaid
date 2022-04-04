//
// Created by 24100 on 2022/4/4.
//

#ifndef CALCULMAID_PAGEDATE_H
#define CALCULMAID_PAGEDATE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui
{
class PageDate;
}
QT_END_NAMESPACE

class PageDate : public QWidget
{
Q_OBJECT

public:
	explicit PageDate(QWidget *parent = nullptr);
	~PageDate() override;

private:
	Ui::PageDate *ui;
};


#endif //CALCULMAID_PAGEDATE_H
