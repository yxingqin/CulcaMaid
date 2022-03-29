//
// Created by 24100 on 2022/3/28.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PopMenu.h" resolved

#include "PopMenu.h"
#include "ui_PopMenu.h"
#include "PopMenuItem.h"
#include "../../unit/LoadFile.h"
PopMenu::PopMenu(QWidget *parent) :
		QWidget(parent), ui(new Ui::PopMenu)
{
	ui->setupUi(this);
	setStyleSheet(Load::loadStyle(":/res/qss/popmenu.qss"));
	//添加 项目
	QList<QString> listItem{"标准","科学","程序员","程序员","日期","关系"};
	addItem("标准",":/res/icon/calcu.png");
	addItem("科学",":/res/icon/science.png");
	addItem("程序员",":/res/icon/program.png");
	addItem("绘图",":/res/icon/funimage.png");
	addItem("日期",":/res/icon/date.png");
	addItem("关系",":/res/icon/relation.png");
}

PopMenu::~PopMenu()
{
	delete ui;
}

void PopMenu::addItem(QString title, QString icon)
{
	QListWidgetItem * newWidget = new QListWidgetItem(ui->listw_calcu);
	PopMenuItem* popMenuItem=new PopMenuItem(ui->listw_calcu,title,icon);
	ui->listw_calcu->setItemWidget(newWidget,popMenuItem);
}

