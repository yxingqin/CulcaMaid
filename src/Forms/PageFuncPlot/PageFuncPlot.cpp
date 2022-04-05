//
// Created by 24100 on 2022/4/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PageFuncPlot.h" resolved

#include "PageFuncPlot.h"
#include "ui_PageFuncPlot.h"


PageFuncPlot::PageFuncPlot(QWidget *parent) :
		QFrame(parent), ui(new Ui::PageFuncPlot)
{
	ui->setupUi(this);
}

PageFuncPlot::~PageFuncPlot()
{
	delete ui;
}

