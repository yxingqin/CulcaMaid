//
// Created by 24100 on 2022/4/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PageDate.h" resolved

#include "PageDate.h"
#include "ui_PageDate.h"
#include <QDebug>
#include <QString>
#include<QDate>
#include"Load.h"
PageDate::PageDate(QWidget *parent) :
		QFrame(parent), ui(new Ui::PageDate)
{
	ui->setupUi(this);
	ui->label_into->setText( QDate::currentDate().toString("yyyy年MM月dd日"));
	connect(ui->widget, SIGNAL(SetCalendarTime(const QDate& )),this, SLOT(selectDate1(const QDate& )));//界面1选中
	connect(ui->widget_2, SIGNAL(SetCalendarTime(const QDate &)),this, SLOT(selectDate2(const QDate &)));
	connect(ui->widget_3, SIGNAL(SetCalendarTime(const QDate &)),this, SLOT(selectDate3(const QDate &)));
	ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));

	ui->stackedWidget->setCurrentIndex(0);
	setStyleSheet(Load::loadStyle(":/qss/pagedata.qss"));
	ui->label_into->setText("选择启始日期");
	ui->pushButton->setEnabled(false);


}

PageDate::~PageDate()
{
	delete ui;
}

void PageDate::addDate(const QDate &startDate, int addNumber)
{
	qDebug()<<startDate.addDays(addNumber);
	//return startDate.addDays(addNumber);
	ui->label->setText(startDate.addDays(addNumber).toString("yyyy年MM月dd日"));
}


int PageDate::intervalDate(QDate startDate, QDate endDate)
{
	qDebug()<<endDate;
	return 0;
}
void PageDate::on_pushButton_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
	QString input = ui->lineEdit->text();
	if(ui->radioButton->isChecked())
	{

		if(!input.isEmpty())
		{
			addDate(date1,input.toInt());
		} else
		{
			ui->label->setText("请输入要添加的天数");
		}
	} else if (ui->radioButton_2->isChecked())
	{
		if (!input.isEmpty())
		{
			addDate(date1, -input.toInt());
		} else
		{
			ui->label->setText("请输入要添加的天数");
		}
	}
}

void PageDate::on_comboBox_currentIndexChanged(const QString &arg1)
{
	if(ui->comboBox->currentIndex()==0)
	{
		ui->stackedWidget->setCurrentIndex(0);
	}
	if(ui->comboBox->currentIndex()==1)
	{
		ui->stackedWidget->setCurrentIndex(1);
		qDebug()<<"1被调用";
		//intervalDate(QDate::currentDate(),QDate::currentDate().addDays(3));
	}
}



void PageDate::selectDate1(const QDate& intoDate)
{
	qDebug()<<"槽函数被调用1";
	date1 = intoDate;
	ui->label_into->setText(date1.toString("yyyy年MM月dd日"));
	ui->pushButton->setEnabled(true);
}
void PageDate::selectDate2(const QDate& intoDate)
{
	qDebug()<<"槽函数被调用2";
	date2 = intoDate;

}
void PageDate::selectDate3(const QDate& intoDate)
{
	qDebug()<<"槽函数被调用3";
	date3 = intoDate;

}





