//
// Created by 24100 on 2022/4/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PageProgram.h" resolved

#include "PageProgram.h"
#include "ui_PageProgram.h"


PageProgram::PageProgram(QWidget *parent) :
		QFrame(parent), ui(new Ui::PageProgram)
{
	ui->setupUi(this);
}

PageProgram::~PageProgram()
{
	delete ui;
}

