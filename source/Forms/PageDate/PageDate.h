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
	QDate addDate(QDate startDate, int addNumber);
	int intervalDate(QDate startDate, QDate endDate);


private slots:
	void on_comboBox_currentIndexChanged(const QString &arg1);
private:
	Ui::PageDate *ui;


};


#endif //CALCULMAID_PAGEDATE_H
