//
// Created by 24100 on 2022/4/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PageRelation.h" resolved

#include "PageRelation.h"
#include "ui_PageRelation.h"


PageRelation::PageRelation(QWidget *parent) :
		QFrame(parent), ui(new Ui::PageRelation)
{
	ui->setupUi(this);
}

PageRelation::~PageRelation()
{
	delete ui;
}

