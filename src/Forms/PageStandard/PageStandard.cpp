#include <LoadFile.h>
#include "PageStandard.h"
#include "ui_PageStandard.h"


PageStandard::PageStandard(QWidget *parent) :
		QWidget(parent), ui(new Ui::PageStandard)
{
	ui->setupUi(this);
	setStyleSheet(Load::loadStyle(":/res/qss/standard.qss"));
}

PageStandard::~PageStandard()
{
	delete ui;
}

