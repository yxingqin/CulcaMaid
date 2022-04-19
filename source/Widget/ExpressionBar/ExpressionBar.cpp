//
// Created by 24100 on 2022/4/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ExpressionBar.h" resolved

#include <QVBoxLayout>
#include "Load.h"
#include "expr.h"
#include "ExpressionBar.h"
#include <QKeyEvent>
#include <QDebug>


ExpressionBar::ExpressionBar(QWidget *parent) : QFrame(parent)
{
	initFrame();
	input->setAttribute(Qt::WA_InputMethodEnabled, false); //禁止中文输入法
	output->setFocusPolicy(Qt::StrongFocus);
	output->setReadOnly(true);
	input->setAlignment(Qt::AlignRight);
	output->setAlignment(Qt::AlignRight);
	input->installEventFilter(this);
	this->installEventFilter(this);
	connect(input,&QLineEdit::textChanged,this,[this](const QString& text){

		expr::Postfix  postfix;
		double result;
		if(expr::getPostfix(text,postfix))
		{
			if(expr::getResult(postfix,result))
				output->setText(QString::number(result));
		}
	});
}

ExpressionBar::~ExpressionBar()
{
}

void ExpressionBar::initFrame()
{
	input = new QLineEdit(this);
	input->setObjectName("input");
	input->setMinimumHeight(80);
	output = new QLineEdit(this);
	output->setObjectName("output");
	output->setMinimumHeight(30);
	//布局
	QVBoxLayout *verticalLayout = new QVBoxLayout(this);
	verticalLayout->setSpacing(0);
	verticalLayout->setContentsMargins(0, 0, 0, 0);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
	input->setSizePolicy(sizePolicy);
	output->setSizePolicy(sizePolicy);
	verticalLayout->addWidget(input);
	verticalLayout->addWidget(output);
	setStyleSheet(Load::loadStyle(":/qss/exprbar.qss"));
}

bool ExpressionBar::eventFilter(QObject *watched, QEvent *event)
{

	if(watched==input&&event->type()==QEvent::KeyPress)//过滤掉 input 按键输入
	{
		onKeyPress(static_cast<QKeyEvent*>(event));
		return true;
	}
	return QObject::eventFilter(watched, event);
}

void ExpressionBar::enterNumber(const QString &text)
{
	if(!output->hasFocus())
		output->setFocus();
	input->insert(text);
}

void ExpressionBar::enterOpt(const QString &text)
{

}

void ExpressionBar::enterPoint(const QString &text)
{

}

void ExpressionBar::enterClear(const QString &text)
{
	input->clear();
}

void ExpressionBar::enterEqual(const QString &text)
{
	input->setText(output->text());
}

void ExpressionBar::enterBackspace(const QString &text)
{

}

void ExpressionBar::enterFunc(const QString &text)
{

}

void ExpressionBar::onKeyPress(QKeyEvent *event)
{
	switch (event->key())
	{
		case Qt::Key_0:
			enterNumber("0");
			break;
		case Qt::Key_1:
			enterNumber("1");
			break;
		case Qt::Key_2:
			enterNumber("2");
			break;
		case Qt::Key_3:
			enterNumber("3");
			break;
		case Qt::Key_4:
			enterNumber("4");
			break;
		case Qt::Key_5:
			enterNumber("5");
			break;
		case Qt::Key_6:
			enterNumber("6");
			break;
		case Qt::Key_7:
			enterNumber("7");
			break;
		case Qt::Key_8:
			enterNumber("8");
			break;
		case Qt::Key_9:
			enterNumber("9");
			break;
		default:
			break;
	}
}
