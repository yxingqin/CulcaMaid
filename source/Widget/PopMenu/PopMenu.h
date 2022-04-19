//
// Created by 24100 on 2022/4/4.
//

#ifndef CALCULMAID_POPMENU_H
#define CALCULMAID_POPMENU_H

#include <QFrame>
#include <QListWidget>
#include "PageSetting/PageSetting.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
	class PopMenu;
}
QT_END_NAMESPACE

class PopMenu : public QFrame
{
	Q_OBJECT
	friend class MainWin;

public:
	explicit PopMenu(QWidget *parent = nullptr);
	~PopMenu() override;
signals:
	void switchPage(int index, QString title);

private:
	void addItem(QString title, QString icon);

private:
	QListWidget *list_culca;
	PageSetting *mpSetting;
	Ui::PopMenu *ui;
};

#endif // CALCULMAID_POPMENU_H
