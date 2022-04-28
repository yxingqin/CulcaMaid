//
// Created by 24100 on 2022/4/4.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PopMenu.h" resolved

#include "PopMenu.h"
#include "ui_PopMenu.h"
#include <QGraphicsDropShadowEffect>
#include "PopMenuItem.h"
#include "Load.h"
PopMenu::PopMenu(QWidget *parent) : QFrame(parent), ui(new Ui::PopMenu)
{
	ui->setupUi(this);
	setStyleSheet(Load::loadStyle(":/qss/popmenu.qss"));
	//设置页面
	mpSetting = new PageSetting();
	connect(ui->btn_setting, &QPushButton::clicked, this, [this]()
			{ mpSetting->show(); });
	//阴影
	auto shadowEffect = new QGraphicsDropShadowEffect(this);
	shadowEffect->setColor("#778899");
	shadowEffect->setOffset(1, 5);
	shadowEffect->setBlurRadius(22);
	this->setGraphicsEffect(shadowEffect);
	//添加 项目
	addItem("标准", ":/icon/calcu.png");
	addItem("科学", ":/icon/science.png");

	addItem("绘图", ":/icon/funimage.png");
	addItem("日期", ":/icon/date.png");
	//	addItem("程序员", ":/icon/program.png");
//	addItem("关系", ":/icon/relation.png");
	ui->listw_calcu->setCurrentRow(0);
	list_culca = ui->listw_calcu;

	connect(ui->listw_calcu, &QListWidget::currentRowChanged, this, [this](int row)
			{ emit switchPage(row, ui->listw_calcu->itemWidget(ui->listw_calcu->item(row))->findChild<QLabel *>("lbl_title")->text()); });
}

PopMenu::~PopMenu()
{
	delete ui;
	delete mpSetting;
}

void PopMenu::addItem(QString title, QString icon)
{
	QListWidgetItem *newWidget = new QListWidgetItem(ui->listw_calcu);
	PopMenuItem *popMenuItem = new PopMenuItem(ui->listw_calcu, title, icon);
	ui->listw_calcu->setItemWidget(newWidget, popMenuItem);
}
