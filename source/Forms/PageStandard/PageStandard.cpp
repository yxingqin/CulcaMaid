#include "PageStandard.h"
#include <QVBoxLayout>
#include <QKeyEvent>

PageStandard::PageStandard(QWidget *parent) : QWidget(parent)
{
	initUi();
	connect(fm_kb, &StandardKB::pressNum, fm_bar, &ExpressionBar::enterNumber);

}

PageStandard::~PageStandard()
{
}


void PageStandard::initUi()
{
	QVBoxLayout *verticalLayout = new QVBoxLayout(this);
	verticalLayout->setSpacing(0);
	verticalLayout->setContentsMargins(0, 0, 0, 0);

	fm_bar = new ExpressionBar(this);
	fm_bar->setMinimumSize(QSize(0, 160));
	fm_bar->setFrameShape(QFrame::StyledPanel);
	fm_bar->setFrameShadow(QFrame::Raised);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(fm_bar->sizePolicy().hasHeightForWidth());
	fm_bar->setSizePolicy(sizePolicy);
	verticalLayout->addWidget(fm_bar);

	fm_kb = new StandardKB(this);
	QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(0);
	sizePolicy1.setHeightForWidth(fm_kb->sizePolicy().hasHeightForWidth());
	fm_kb->setSizePolicy(sizePolicy1);
	fm_kb->setFrameShape(QFrame::StyledPanel);
	fm_kb->setFrameShadow(QFrame::Raised);
	verticalLayout->addWidget(fm_kb);
}

void PageStandard::onKeyPress(QKeyEvent *event)
{
	fm_bar->onKeyPress(event);
}



