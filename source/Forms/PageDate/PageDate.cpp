//
// Created by 24100 on 2022/4/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PageDate.h" resolved

#include "PageDate.h"
#include "ui_PageDate.h"
#include <QDebug>
#include<QDate>
#include"Load.h"
PageDate::PageDate(QWidget *parent) :
		QFrame(parent), ui(new Ui::PageDate)
{
	ui->setupUi(this);
	ui->label_into->setText( QDate::currentDate().toString("yyyy年MM月dd日"));
	connect(ui->widget, SIGNAL(SetCalendarTime(const QDate& )),this, SLOT(selectDate(const QDate& )));
	//connect(ui->widget,&XCalendar::SetCalendarTime,this,&PageDate::selectDate);

	setStyleSheet(Load::loadStyle(":/qss/pagedata.qss"));

}

PageDate::~PageDate()
{
	delete ui;
}

QDate PageDate::addDate(const QDate &startDate, int addNumber)
{
	qDebug()<<startDate.addDays(addNumber);
	return startDate.addDays(addNumber);
}

int PageDate::intervalDate(QDate startDate, QDate endDate)
{
	qDebug()<<endDate;
	return 0;
}

void PageDate::on_comboBox_currentIndexChanged(const QString &arg1)
{
	if(ui->comboBox->currentIndex()==0)
	{
		qDebug()<<"0被调用";
		ui->stackedWidget->setCurrentIndex(0);





		//addDate(QDate::currentDate(),4);
	}
	if(ui->comboBox->currentIndex()==1)
	{
		ui->stackedWidget->setCurrentIndex(1);
		qDebug()<<"1被调用";
		//intervalDate(QDate::currentDate(),QDate::currentDate().addDays(3));
	}
}

void PageDate::selectDate(const QDate& intoDate)
{
	qDebug()<<"槽函数被调用";
	date1 = intoDate.toString("yyyy年MM月dd日");
	ui->label_into->setText(date1);
}





