//
// Created by 24100 on 2022/4/30.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PageEditPlot.h" resolved

#include "PageEditPlot.h"
#include "ui_PageEditPlot.h"
#include "Plot/PlotModel.h"
#include "Plot/PlotDelegate.h"
#include "Load.h"


PageEditPlot::PageEditPlot(QWidget *parent) :
		QFrame(parent), ui(new Ui::PageEditPlot)
{
	ui->setupUi(this);

	setStyleSheet(Load::loadStyle(":/qss/pageplotedit.qss"));

	delegate=new PlotDelegate(this);
	ui->listView->setItemDelegate(delegate);
	//ui->listView->openPersistentEditor({});
}

PageEditPlot::~PageEditPlot()
{
	delete ui;
	m_model->deleteLater();
	delegate->deleteLater();
}

void PageEditPlot::setModel(PlotModel *model)
{
	m_model=model;
	ui->listView->setModel(model);
}

void PageEditPlot::enterNumber(const QString &t)
{
	auto delegate=ui->listView->itemDelegate(ui->listView->currentIndex());

}

void PageEditPlot::enterOpt(const QString &t)
{

}

void PageEditPlot::enterPoint()
{

}

void PageEditPlot::enterClear()
{

}

void PageEditPlot::enterBackspace()
{

}

void PageEditPlot::enterParenLeft()
{

}

void PageEditPlot::enterParenRight()
{

}

void PageEditPlot::enterFunc(const QString &t)
{

}

void PageEditPlot::enterValue(const QString &t)
{

}

void PageEditPlot::enterFrequentExpr1(const QString &t)
{

}

void PageEditPlot::enterFrequentExpr2(const QString &t)
{

}
