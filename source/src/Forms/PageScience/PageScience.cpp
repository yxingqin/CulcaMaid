//
// Created by 24100 on 2022/4/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PageScience.h" resolved

#include "PageScience.h"
#include "ui_PageScience.h"


PageScience::PageScience(QWidget *parent) :
		QFrame(parent), ui(new Ui::PageScience)
{
	ui->setupUi(this);
}

PageScience::~PageScience()
{
	delete ui;
}

