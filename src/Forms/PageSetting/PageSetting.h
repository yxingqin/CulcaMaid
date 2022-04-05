//
// Created by 24100 on 2022/4/5.
//

#ifndef CALCULMAID_PAGESETTING_H
#define CALCULMAID_PAGESETTING_H

#include <QFrame>


QT_BEGIN_NAMESPACE
namespace Ui
{
class PageSetting;
}
QT_END_NAMESPACE

class PageSetting : public QFrame
{
Q_OBJECT

public:
	explicit PageSetting(QWidget *parent = nullptr);
	~PageSetting() override;

private:
	Ui::PageSetting *ui;
};


#endif //CALCULMAID_PAGESETTING_H
