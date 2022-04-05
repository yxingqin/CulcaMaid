//
// Created by 24100 on 2022/4/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PageDate.h" resolved

#include "PageDate.h"
#include "ui_PageDate.h"


PageDate::PageDate(QWidget *parent) :
		QFrame(parent), ui(new Ui::PageDate)
{
	ui->setupUi(this);
}

PageDate::~PageDate()
{
	delete ui;
}

