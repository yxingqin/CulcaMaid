//
// Created by 24100 on 2022/3/29.
//

#ifndef CALCULMAID_POPMENUITEM_H
#define CALCULMAID_POPMENUITEM_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui
{
class PopMenuItem;
}
QT_END_NAMESPACE

class PopMenuItem : public QWidget
{
Q_OBJECT

public:
	PopMenuItem(QWidget *parent,QString title,QString ico);
	~PopMenuItem() override;

private:
	Ui::PopMenuItem *ui;
};


#endif //CALCULMAID_POPMENUITEM_H
