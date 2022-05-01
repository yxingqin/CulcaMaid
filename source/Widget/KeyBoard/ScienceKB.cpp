//
// Created by 24100 on 2022/4/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ScienceKB.h" resolved

#include <QGridLayout>
#include "Load.h"
#include "ScienceKB.h"
#include <QDebug>

const ScienceKB::BtnDescription ScienceKB::btnDescriptions[] =
		{
				//u'(', u')', u'＋', u'－', u'×', u'÷', u'^'
				{"三角函数", KEY_TRIANGLE,  0, 0, 1, 1},
				{"函数",   KEY_FUNC,      0, 1, 1, 1},
				{"π",    KEY_PI,         0, 2, 1, 1},
				{"e",    KEY_E,         0, 3, 1, 1},
				{"C",    KEY_CLEAR,     0, 4, 1, 1},
				{"",     KEY_BACKSPACE, 0, 5, 1, 1},


				{"x",    KEY_X,         1, 0, 1, 1},
				{"1/x",  KEY_X1,        1, 1, 1, 1},
				{"|x|",  KEY_ABS,       1, 2, 1, 1},
				{"(",    KEY_LEFT,      1, 3, 1, 1},
				{")",    KEY_RIGHT,     1, 4, 1, 1},
				{"÷",    KEY_DIV,       1, 5, 1, 1},

				{"x²",   KEY_SQR,       2, 0, 1, 1},
				{"x³",   KEY_CUBE,      2, 1, 1, 1},
				{"7",    KEY_7,         2, 2, 1, 1},
				{"8",    KEY_8,         2, 3, 1, 1},
				{"9",    KEY_9,         2, 4, 1, 1},
				{"×",    KEY_MULT,      2, 5, 1, 1},


				{"²√x",  KEY_SQRROOT,   3, 0, 1, 1},
				{"³√x",  KEY_CUBEROOT,  3, 1, 1, 1},
				{"4",    KEY_4,         3, 2, 1, 1},
				{"5",    KEY_5,         3, 3, 1, 1},
				{"6",    KEY_6,         3, 4, 1, 1},
				{"－",    KEY_SUB,       3, 5, 1, 1},

				{"xʸ",   KEY_POWER,     4, 0, 1, 1},
				{"ʸ√x",  KEY_YROOT,     4, 1, 1, 1},
				{"1",    KEY_1,         4, 2, 1, 1},
				{"2",    KEY_2,         4, 3, 1, 1},
				{"3",    KEY_3,         4, 4, 1, 1},
				{"＋",    KEY_PLUS,      4, 5, 1, 1},

				{"10ˣ",   KEY_10N,     5, 0, 1, 1},
				{"2ˣ",  KEY_2N,     5, 1, 1, 1},
				{"%",    KEY_PERCENT,         5, 2, 1, 1},
				{"0",    KEY_0,   5, 3, 1, 1},
				{".",    KEY_POINT,         5, 4, 1, 1},
				{"=",    KEY_EQUALS,     5, 5, 1, 1},

		};


ScienceKB::ScienceKB(QWidget *parent) : QFrame(parent)
{


	initUi();

	setStyleSheet(Load::loadStyle(":/qss/sciencekb.qss"));

	findBtnById(KEY_BACKSPACE)->setIcon(QIcon(":/icon/backspace.png"));
	findBtnById(KEY_BACKSPACE)->setIconSize({28, 28});
	findBtnById(KEY_TRIANGLE)->setIcon(QIcon(":/icon/down.png"));
	findBtnById(KEY_FUNC)->setIcon(QIcon(":/icon/down.png"));

	popFunc = new PopKbFunc(this);
	popKbTriangle=new PopKbTriangle(this);
	connect(popFunc,&PopKbFunc::pressFunc,this,&ScienceKB::pressFunc);
	connect(popKbTriangle,&PopKbTriangle::pressFunc,this,&ScienceKB::pressFunc);
}

ScienceKB::~ScienceKB()
{
}

void ScienceKB::initUi()
{
	gridLayout = new QGridLayout(this);
	gridLayout->setSpacing(0);
	gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
	gridLayout->setContentsMargins(0, 0, 0, 0);
	this->setObjectName("ScienceKB");
	int count = sizeof(btnDescriptions) / sizeof(btnDescriptions[0]);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	for (int i = 0; i < count; ++i)
	{
		BtnDescription d = btnDescriptions[i];
		QPushButton *btn = new QPushButton(this);
		btn->setObjectName(QString("btn_kb%1%2").arg(d.row).arg(d.column));
		btn->setText(d.text);
		btn->setSizePolicy(sizePolicy);
		gridLayout->addWidget(btn, d.row, d.column, d.rowcount, d.columncount);
		btnSet.insert(d.id, {i, btn});
		connect(btn, &QPushButton::clicked, this, [this, d] { onBtnPress(d.id); });
	}
}

void ScienceKB::onBtnPress(ScienceKB::ButtonID id)
{
	switch (id)
	{
		case KEY_CLEAR:
			emit pressClear();
			break;
		case KEY_BACKSPACE:
			emit pressBackspace();
			break;
		case KEY_PLUS:
		case KEY_SUB:
		case KEY_MULT:
		case KEY_DIV:
		case KEY_PERCENT:
		case KEY_POWER:
			emit pressOpt(btnDescriptions[btnSet.find(id).value().index].text);
			break;
		case KEY_7:
		case KEY_8:
		case KEY_9:
		case KEY_4:
		case KEY_5:
		case KEY_6:
		case KEY_1:
		case KEY_2:
		case KEY_3:
		case KEY_0:
			emit pressNum(btnDescriptions[btnSet.find(id).value().index].text);
			break;
		case KEY_EQUALS:
			pressEnter();
			break;
		case KEY_POINT:
			pressPoint();
			break;
		case KEY_PI:
		case KEY_E:
		case KEY_X:
			pressValue(btnDescriptions[btnSet.find(id).value().index].text);
			break;
		case KEY_LEFT:
			pressParenLeft();
			break;
		case KEY_RIGHT:
			pressParenRight();
			break;
		case KEY_CUBEROOT:
			pressFrequentExpr1("^(1÷3)");
			break;
		case KEY_X1:
			pressFrequentExpr1("^(－1)");
			break;
		case KEY_SQR:
			pressFrequentExpr1("^(2)");
			break;
		case KEY_CUBE:
			pressFrequentExpr1("^(3)");
			break;
		case KEY_YROOT:
			pressFrequentExpr1("^(1÷");
			break;
		case KEY_2N:
			pressFrequentExpr2("2^");
			break;
		case KEY_10N:
			pressFrequentExpr2("10^");
			break;
		case KEY_ABS:
			pressFunc("abs");
			break;
		case KEY_SQRROOT:
			pressFunc("√");
			break;
		case KEY_TRIANGLE:
			popFunc->hide();
			popKbTriangle->popup(findBtnById(KEY_TRIANGLE),200,120);
			break;
		case KEY_FUNC:
			popKbTriangle->hide();
			popFunc->popup(findBtnById(KEY_FUNC));
			break;

	}
}

void ScienceKB::setMode(int mode)
{
	if(mode==0)
	{
		findBtnById(KEY_X)->setEnabled(false);
	}else
	{
		findBtnById(KEY_X)->setEnabled(true);
		findBtnById(KEY_EQUALS)->setText("Enter");
	}
}

PopKbFunc::PopKbFunc(QWidget *parent): PopKb(parent)
{
	initUi();
	setStyleSheet(Load::loadStyle(":/qss/popkb.qss"));

	connect(btn_Log,&QPushButton::clicked, this,[this](){
		emit pressFunc("lg");
	});
	connect(btn_Ln,&QPushButton::clicked, this,[this](){
		emit pressFunc("ln");
	});
	hide();
	raise();
}

void PopKbFunc::initUi()
{
	this->setObjectName("popKb");
	btn_Ln=new QPushButton(this);
	btn_Log=new QPushButton(this);
	btn_Ln->setText("ln");
	btn_Log->setText("lg");
	QGridLayout* gridLayout = new QGridLayout(this);
	gridLayout->setSpacing(0);
	gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
	gridLayout->setContentsMargins(0, 0, 0, 0);
	gridLayout->addWidget(btn_Log, 0, 0, 1, 1);
	gridLayout->addWidget(btn_Ln, 0, 1, 1, 1);
}

void PopKb::popup(QPushButton *btn,int w,int h)
{
	if(isHidden())
	{
		this->setGeometry(btn->x(),btn->y()+btn->height(),btn->width()*3,btn->height()*2);
		this->show();
	}else
		hide();
}

void PopKb::leaveEvent(QEvent *event)
{
	hide();
	QWidget::leaveEvent(event);
}

/*
 * 	SIN,
	SEC,
	COS,
	CSC,
	TAN,
	COT,
 */
QList<QString> PopKbTriangle::funList={"sin","cos","tan","sec","csc","cot"};

void PopKbTriangle::initUi()
{
	this->setObjectName("popKb");
	QGridLayout* gridLayout = new QGridLayout(this);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0, 0, 0, 0);
	gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
	for(int i=0;i<funList.size();++i)
	{
		QPushButton* btn=new QPushButton(this);
		if(i<3)
			gridLayout->addWidget(btn, 0, i, 1, 1);
		else
			gridLayout->addWidget(btn, 1, i-3, 1, 1);
		btn->setText(funList[i]);
		connect(btn,&QPushButton::clicked,this,[this,btn](){
			emit pressFunc(btn->text());
		});
	}
}

PopKbTriangle::PopKbTriangle(QWidget *parent):PopKb(parent)
{
	initUi();
	setStyleSheet(Load::loadStyle(":/qss/popkb.qss"));
	hide();
	raise();
}
