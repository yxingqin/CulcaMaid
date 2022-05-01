//
// Created by 24100 on 2022/4/5.
//

#ifndef CALCULMAID_PAGEDATE_H
#define CALCULMAID_PAGEDATE_H

#include <QFrame>
#include <qmath.h>
#include <QTime>
#include <QStackedWidget>
#include "XCalendar.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class PageDate;
}
QT_END_NAMESPACE

class PageDate : public QFrame
{
Q_OBJECT

public:
	explicit PageDate(QWidget *parent = nullptr);
	~PageDate() override;

private:
	void addDate(const QDate& startDate, int addNumber);
	QDate date1;
	QDate date2;
	QDate date3;

	int intervalDate(QDate startDate, QDate endDate);


private slots:
	void on_pushButton_clicked();
	void on_startDayBtn_clicked();	
	void on_comboBox_currentIndexChanged(const QString &arg1);
	void selectDate1(const QDate& intoDate);
	void selectDate2(const QDate& intoDate);
	void selectDate3(const QDate& intoDate);

private:
	Ui::PageDate *ui;


};


#endif //CALCULMAID_PAGEDATE_H
