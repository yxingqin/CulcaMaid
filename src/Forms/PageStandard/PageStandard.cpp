#include "PageStandard.h"
#include "ui_PageStandard.h"


PageStandard::PageStandard(QWidget *parent) :
		QWidget(parent), ui(new Ui::PageStandard)
{
	ui->setupUi(this);
}

PageStandard::~PageStandard()
{
	delete ui;
}

