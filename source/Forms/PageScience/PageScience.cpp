//
// Created by 24100 on 2022/4/5.
//


#include "PageScience.h"
#include "Load.h"
#include "expr.h"


PageScience::PageScience(QWidget *parent) :
		QFrame(parent)
{
	initUi();
	input->setAlignment(Qt::AlignRight);
	output->setReadOnly(true);
	output->setAlignment(Qt::AlignRight);
	m_kb->setMode(0);
	connect(m_kb,&ScienceKB::pressNum,input,&InputText::enterNumber);
	connect(m_kb,&ScienceKB::pressOpt,input,&InputText::enterOpt);
	connect(m_kb,&ScienceKB::pressBackspace,input,&InputText::enterBackspace);
	connect(m_kb,&ScienceKB::pressPoint,input,&InputText::enterPoint);
	connect(m_kb,&ScienceKB::pressParenLeft,input,&InputText::enterParenLeft);
	connect(m_kb,&ScienceKB::pressParenRight,input,&InputText::enterParenRight);
	connect(m_kb,&ScienceKB::pressFrequentExpr1,input,&InputText::enterFrequentExpr1);
	connect(m_kb,&ScienceKB::pressFrequentExpr2,input,&InputText::enterFrequentExpr2);
	connect(m_kb,&ScienceKB::pressClear,input,&InputText::enterClear);
	connect(m_kb,&ScienceKB::pressClear,output,&QLineEdit::clear);
	connect(m_kb,&ScienceKB::pressValue,input,&InputText::enterValue);
	connect(m_kb,&ScienceKB::pressFunc,input,&InputText::enterFunc);
	connect(input,&QLineEdit::textChanged,this,&PageScience::onInputTextChanged);
	connect(m_kb,&ScienceKB::pressEnter,this,&PageScience::onEnter);
}

PageScience::~PageScience()
{

}

void PageScience::initUi()
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
	m_kb = new ScienceKB(this);
	QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(0);
	sizePolicy1.setHeightForWidth(m_kb->sizePolicy().hasHeightForWidth());
	m_kb->setSizePolicy(sizePolicy1);
	m_kb->setFrameShape(QFrame::StyledPanel);
	m_kb->setFrameShadow(QFrame::Raised);
	verticalLayout->addWidget(m_kb);

	setStyleSheet(Load::loadStyle(":/qss/culpage.qss"));
}

void PageScience::onInputTextChanged()
{
	expr::Postfix postfix;
	if(expr::getPostfix(input->text(),postfix))
	{

		double result;
		expr::getResult(postfix,result);
		output->setText(QString::number(result,'f',2));
	}
}

void PageScience::onEnter()
{
	if(!output->text().isEmpty())
	{
		emit sendHistory(input->text(),output->text());
		input->setText(output->text());
		output->clear();
	}
}

