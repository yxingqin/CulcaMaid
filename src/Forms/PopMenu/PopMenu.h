//
// Created by 24100 on 2022/3/28.
//

#ifndef CALCULMAID_POPMENU_H
#define CALCULMAID_POPMENU_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui
{
class PopMenu;
}
QT_END_NAMESPACE

class PopMenu : public QWidget
{
Q_OBJECT

public:
	explicit PopMenu(QWidget *parent = nullptr);
	~PopMenu() override;

private:
	Ui::PopMenu *ui;
	QList<QString> mlist_calcu;
};


#endif //CALCULMAID_POPMENU_H
