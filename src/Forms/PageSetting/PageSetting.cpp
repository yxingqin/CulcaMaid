//
// Created by 24100 on 2022/4/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PageSetting.h" resolved

#include "PageSetting.h"
#include "ui_PageSetting.h"


PageSetting::PageSetting(QWidget *parent) :
		QFrame(parent), ui(new Ui::PageSetting)
{
	ui->setupUi(this);
}

PageSetting::~PageSetting()
{
	delete ui;
}

