//
// Created by 24100 on 2022/3/30.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SettingWin.h" resolved

#include "SettingWin.h"
#include "ui_SettingWin.h"


SettingWin::SettingWin(QWidget *parent) :
		QWidget(parent), ui(new Ui::SettingWin)
{
	ui->setupUi(this);
}

SettingWin::~SettingWin()
{
	delete ui;
}

