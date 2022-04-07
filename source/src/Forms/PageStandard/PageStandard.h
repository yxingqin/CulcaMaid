//
// Created by 24100 on 2022/4/4.
//

#ifndef CALCULMAID_PAGESTANDARD_H
#define CALCULMAID_PAGESTANDARD_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui
{
class PageStandard;
}
QT_END_NAMESPACE

class PageStandard : public QWidget
{
Q_OBJECT

public:
	explicit PageStandard(QWidget *parent = nullptr);
	~PageStandard() override;

private:

	Ui::PageStandard *ui;
};


#endif //CALCULMAID_PAGESTANDARD_H
