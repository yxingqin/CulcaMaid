//
// Created by 24100 on 2022/4/4.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PopMenu.h" resolved

#include "PopMenu.h"
#include "ui_PopMenu.h"
#include <QGraphicsDropShadowEffect>
#include "PopMenuItem.h"
PopMenu::PopMenu(QWidget *parent) :
		QFrame(parent), ui(new Ui::PopMenu)
{
	ui->setupUi(this);
	//阴影
	auto shadowEffect=new QGraphicsDropShadowEffect(this);
	shadowEffect->setColor("#778899");
	shadowEffect->setOffset(0,0);
	shadowEffect->setBlurRadius(22);
	this->setGraphicsEffect(shadowEffect);
	//添加 项目
	addItem("标准",":/res/icon/calcu.png");
	addItem("科学",":/res/icon/science.png");
	addItem("程序员",":/res/icon/program.png");
	addItem("绘图",":/res/icon/funimage.png");
	addItem("日期",":/res/icon/date.png");
	addItem("关系",":/res/icon/relation.png");
	ui->listw_calcu->setCurrentRow(0);
	list_culca=ui->listw_calcu;
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

