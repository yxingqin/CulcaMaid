#include <QVBoxLayout>
#include <QKeyEvent>
#include "PageStandard.h"
#include "Load.h"
#include "expr.h"
PageStandard::PageStandard(QWidget *parent) : QWidget(parent)
{
	initUi();
	output->setReadOnly(true);
	output->setAlignment(Qt::AlignRight);

	//事件处理
	connect(fm_kb,&StandardKB::pressNum,input,&InputText::enterNumber);
	connect(fm_kb,&StandardKB::pressOpt,input,&InputText::enterOpt);
	connect(fm_kb,&StandardKB::pressBackspace,input,&InputText::enterBackspace);
	connect(fm_kb,&StandardKB::pressPoint,input,&InputText::enterPoint);
	connect(fm_kb,&StandardKB::pressClear,input,&InputText::enterClear);
	connect(fm_kb,&StandardKB::pressClear,output,&QLineEdit::clear);
	connect(input,&QLineEdit::textChanged,this,&PageStandard::onInputTextChanged);
	connect(fm_kb,&StandardKB::pressEnter,this,&PageStandard::onEnter);

	input->setAlignment(Qt::AlignRight);
}

PageStandard::~PageStandard()
{

}


void PageStandard::initUi()
{
	QVBoxLayout *verticalLayout = new QVBoxLayout(this);
	verticalLayout->setSpacing(0);
	verticalLayout->setContentsMargins(0, 0, 0, 0);

	//输入栏
	input = new InputText(this);
	input->setObjectName("input");
	input->setMinimumHeight(80);
	output = new QLineEdit(this);
	output->setObjectName("output");
	output->setMinimumHeight(30);
	QVBoxLayout *verticalLayout1 = new QVBoxLayout();
	verticalLayout1->setSpacing(0);
	verticalLayout1->setContentsMargins(0, 0, 0, 0);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
	input->setSizePolicy(sizePolicy);
	output->setSizePolicy(sizePolicy);
	verticalLayout1->addWidget(input);
	verticalLayout1->addWidget(output);
	verticalLayout->addLayout(verticalLayout1);

	//键盘
	fm_kb = new StandardKB(this);
	QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(0);
	sizePolicy1.setHeightForWidth(fm_kb->sizePolicy().hasHeightForWidth());
	fm_kb->setSizePolicy(sizePolicy1);
	fm_kb->setFrameShape(QFrame::StyledPanel);
	fm_kb->setFrameShadow(QFrame::Raised);
	verticalLayout->addWidget(fm_kb);

	setStyleSheet(Load::loadStyle(":/qss/culpage.qss"));
}

void PageStandard::onKeyPress(QKeyEvent *event)
{
	input->keyPressEvent(event);
}

void PageStandard::onInputTextChanged()
{
	expr::Postfix postfix;
	if(expr::getPostfix(input->text(),postfix))
	{
		double result;
		expr::getResult(postfix,result);
		output->setText(QString::number(result));
	}
}

void PageStandard::onEnter()
{
	if(!output->text().isEmpty())
	{
		emit sendHistory(input->text(),output->text());
		input->setText(output->text());
		output->clear();
	}
}



