#include "PageDate.h"
#include "ui_PageDate.h"


PageDate::PageDate(QWidget *parent) :
		QWidget(parent), ui(new Ui::PageDate)
{
	ui->setupUi(this);
}

PageDate::~PageDate()
{
	delete ui;
}

