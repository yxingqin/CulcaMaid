//
// Created by 24100 on 2022/4/29.
//


#include <QHBoxLayout>
#include "PlotEdit.h"
#include <QDebug>


PlotEdit::PlotEdit(QWidget *parent) :
		QWidget(parent)
{
	initUi();
}

PlotEdit::~PlotEdit()
{

}

void PlotEdit::setExpr(const QString &expr)
{
	lineEdit->setText(expr);
}

void PlotEdit::initUi()
{
	label = new QLabel(this);
	label->setObjectName("label");
	label->setText("f(x)=");
	lineEdit = new InputText(this);
	lineEdit->setObjectName("lineEdit");
	lineEdit->enableThousandFormat(false);
	QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
	horizontalLayout->addWidget(label);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	lineEdit->setSizePolicy(sizePolicy);
	horizontalLayout->addWidget(lineEdit);
}

QString PlotEdit::getExpr() const
{
	return lineEdit->text();
}
