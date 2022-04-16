#include <LoadFile.h>
#include "PageStandard.h"
#include "ui_PageStandard.h"
#include <QDebug>
#include "expr.h"

PageStandard::PageStandard(QWidget *parent) : QWidget(parent), ui(new Ui::PageStandard)
{
	ui->setupUi(this);
	setStyleSheet(Load::loadStyle(":/res/qss/standard.qss"));

	ui->ledt_out1->setAttribute(Qt::WA_InputMethodEnabled, false); //输入法禁用
	this->startTimer(1000);

	// 输入 处理
	for (auto it : ui->fm_calcuKb->findChildren<QPushButton *>())
		if (it->objectName() != "btn_kb54" && it->objectName() != "btn_kb11" && it->objectName() != "btn_kb14")
			connect(it, &QPushButton::clicked, this, &PageStandard::btnInput);
	connect(ui->ledt_out1, &QLineEdit::textChanged, this, &PageStandard::inputFilter);
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

void PageStandard::on_btn_kb54_clicked()
{
	qDebug() << "=";
}

void PageStandard::on_btn_kb11_clicked()
{
	ui->ledt_out1->clear();
}

void PageStandard::on_btn_kb14_clicked()
{
	ui->ledt_out1->backspace();
}

void PageStandard::inputFilter(const QString &text)
{
	//过滤
	QString old = ui->ledt_out1->displayText();
	qDebug() << "old" << old;
	qDebug() << "text" << text;
	ui->ledt_out1->setText(formatThousands(text));

	// 计算
	expr::Postfix post;
	if (expr::getPostfix(text, post))
	{
		double result;
		expr::getResult(post, result);
		ui->ledt_out2->setText(QString::number(result));
	}
	else
	{
		ui->ledt_out2->clear();
	}
}

void PageStandard::timerEvent(QTimerEvent *event)
{
	ui->ledt_out1->setFocus();
}

QString PageStandard::formatThousands(const QString &text) const
{
	QString ret(text);
	for (int i = 0; i < ret.length(); ++i)
	{
		int n = 0;
		while (i < ret.length() && ret[i].isDigit())
		{
			if (n != 0 && n % 3 == 0)
			{
				ret.insert(i, ',');
			}

			++i;
			++n;
		}
	}
	return ret;
}
