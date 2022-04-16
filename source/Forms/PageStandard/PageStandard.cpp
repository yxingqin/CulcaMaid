#include <LoadFile.h>
#include "PageStandard.h"
#include "ui_PageStandard.h"
#include <QDebug>
#include "expr.h"

PageStandard::PageStandard(QWidget *parent) : QWidget(parent), ui(new Ui::PageStandard)
{
	ui->setupUi(this);
	setStyleSheet(Load::loadStyle(":/res/qss/standard.qss"));
	//输入法禁用
	ui->ledt_out2->setAttribute(Qt::WA_InputMethodEnabled, false);
	//注册事件
	for (auto it : ui->fm_calcuKb->findChildren<QPushButton *>())
		connect(it, &QPushButton::clicked, this, &PageStandard::btnInput);
	connect(ui->btn_kb11, &QPushButton::clicked, this, []()
	{
		expr::Postfix post;
		expr::getPostfix("(-x)×1",post);
		qDebug()<<post;
		double  result;
		expr::getResult(post,result,0);
		qDebug()<<result;
	});
}

PageStandard::~PageStandard()
{
	delete ui;
}

void PageStandard::btnInput()
{
	QPushButton *btn = static_cast<QPushButton *>(QObject::sender());
	QString text = ui->ledt_out1->text();

	text.insert(ui->ledt_out1->cursorPosition(), btn->text());
	ui->ledt_out1->setText(text);
}
