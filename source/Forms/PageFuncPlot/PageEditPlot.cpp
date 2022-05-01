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
	ui->frame->setMode(1);
	connect(ui->frame,&ScienceKB::pressNum,ui->lineEdit,&InputText::enterNumber);
	connect(ui->frame,&ScienceKB::pressOpt,ui->lineEdit,&InputText::enterOpt);
	connect(ui->frame,&ScienceKB::pressBackspace,ui->lineEdit,&InputText::enterBackspace);
	connect(ui->frame,&ScienceKB::pressPoint,ui->lineEdit,&InputText::enterPoint);
	connect(ui->frame,&ScienceKB::pressParenLeft,ui->lineEdit,&InputText::enterParenLeft);
	connect(ui->frame,&ScienceKB::pressParenRight,ui->lineEdit,&InputText::enterParenRight);
	connect(ui->frame,&ScienceKB::pressFrequentExpr1,ui->lineEdit,&InputText::enterFrequentExpr1);
	connect(ui->frame,&ScienceKB::pressFrequentExpr2,ui->lineEdit,&InputText::enterFrequentExpr2);
	connect(ui->frame,&ScienceKB::pressClear,ui->lineEdit,&InputText::enterClear);
	connect(ui->frame,&ScienceKB::pressValue,ui->lineEdit,&InputText::enterValue);
	connect(ui->frame,&ScienceKB::pressFunc,ui->lineEdit,&InputText::enterFunc);
	connect(ui->lineEdit,&QLineEdit::textChanged,this,&PageEditPlot::sendExpr);
}

PageEditPlot::~PageEditPlot()
{
	delete ui;

}