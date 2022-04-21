//
// Created by 24100 on 2022/4/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PageDate.h" resolved

#include "PageDate.h"
#include "ui_PageDate.h"
#include <QDebug>


PageDate::PageDate(QWidget *parent) :
		QFrame(parent), ui(new Ui::PageDate)
{
	ui->setupUi(this);
	XCalendar *calendar = new XCalendar(this);
	ui->horizontalLayout->addWidget(calendar);


}

PageDate::~PageDate()
{
	delete ui;
}

QDate PageDate::addDate(QDate startDate, int addNumber)
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
		addDate(QDate::currentDate(),4);
	}
	if(ui->comboBox->currentIndex()==1)
	{
		qDebug()<<"1被调用";
		intervalDate(QDate::currentDate(),QDate::currentDate().addDays(3));
	}
}




