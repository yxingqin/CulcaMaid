//
// Created by 24100 on 2022/3/28.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PopMenu.h" resolved

#include "PopMenu.h"
#include "ui_PopMenu.h"

PopMenu::PopMenu(QWidget *parent) :
		QWidget(parent), ui(new Ui::PopMenu)
{
	ui->setupUi(this);
	mlist_calcu<<"标准"<<"科学"<<"程序员"<<"绘图"<<"日期"<<"关系";

	//计算器子菜单
	for(auto& it:mlist_calcu)
	{
		ui->listw_calcu->addItem(new QListWidgetItem(QIcon(":/res/icon/calcu.png"),it));


	}
}

PopMenu::~PopMenu()
{
	delete ui;
}

