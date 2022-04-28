//
// Created by 24100 on 2022/4/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_StandardKB.h" resolved

#include <QGridLayout>
#include "Load.h"
#include "StandardKB.h"
#include <QDebug>

const StandardKB::BtnDescription StandardKB::btnDescriptions[] =
	{
			//u'(', u')', u'＋', u'－', u'×', u'÷', u'^'
		{"C", KEY_CLEAR, 0, 0, 1, 1},
		{"÷", KEY_DIV, 0, 1, 1, 1},
		{"×", KEY_MULT, 0, 2, 1, 1},
		{"", KEY_BACKSPACE, 0, 3, 1, 1},

		{"7", KEY_7, 1, 0, 1, 1},
		{"8", KEY_8, 1, 1, 1, 1},
		{"9", KEY_9, 1, 2, 1, 1},
		{"－", KEY_SUB, 1, 3, 1, 1},

		{"4", KEY_4, 2, 0, 1, 1},
		{"5", KEY_5, 2, 1, 1, 1},
		{"6", KEY_6, 2, 2, 1, 1},
		{"＋", KEY_PLUS, 2, 3, 1, 1},

		{"1", KEY_1, 3, 0, 1, 1},
		{"2", KEY_2, 3, 1, 1, 1},
		{"3", KEY_3, 3, 2, 1, 1},
		{"=", KEY_EQUALS, 3, 3, 2, 1},

		{"%", KEY_PERCENT, 4, 0, 1, 1},
		{"0", KEY_0, 4, 1, 1, 1},
		{".", KEY_POINT, 4, 2, 1, 1},

};

StandardKB::StandardKB(QWidget *parent) : QFrame(parent)
{

	initUi();

	setStyleSheet(Load::loadStyle(":/qss/standardkb.qss"));

	findBtnById(KEY_BACKSPACE)->setIcon(QIcon(":/icon/backspace.png"));
	findBtnById(KEY_BACKSPACE)->setIconSize({28, 28});
}

StandardKB::~StandardKB()
{
}

void StandardKB::initUi()
{
	gridLayout = new QGridLayout(this);
	gridLayout->setSpacing(0);
	gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
	gridLayout->setContentsMargins(0, 0, 0, 0);

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
		connect(btn, &QPushButton::clicked, this, [this, d]
				{ onBtnPress(d.id); });
	}
}

void StandardKB::onBtnPress(StandardKB::ButtonID id)
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
	}
}

