//
// Created by 24100 on 2022/4/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PageHistory.h" resolved

#include "PageHistory.h"
#include "ui_PageHistory.h"


PageHistory::PageHistory(QWidget *parent) :
		QFrame(parent), ui(new Ui::PageHistory)
{
	ui->setupUi(this);
}

PageHistory::~PageHistory()
{
	delete ui;
}

