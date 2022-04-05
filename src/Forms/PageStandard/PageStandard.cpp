#include <LoadFile.h>
#include "PageStandard.h"
#include "ui_PageStandard.h"
#include <QDebug>

#include <chrono>




PageStandard::PageStandard(QWidget *parent) :
		QWidget(parent), ui(new Ui::PageStandard)
{
	ui->setupUi(this);
	setStyleSheet(Load::loadStyle(":/res/qss/standard.qss"));
	//输入法禁用
	ui->ledt_out2->setAttribute(Qt::WA_InputMethodEnabled,false);
}

PageStandard::~PageStandard()
{
	delete ui;
}



