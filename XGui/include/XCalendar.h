//
// Created by xzl01 on 2022/4/15.
//

#ifndef CALCUMAID_XCALENDAR_H
#define CALCUMAID_XCALENDAR_H
#include <QWidget>
#include <QDate>
#include <QtUiPlugin/QDesignerExportWidget>
#include <QPushButton>
#include <QColor>
#include <QProxyStyle>
#include <QCalendarWidget>
#include <QLocale>
#include <QTextCharFormat>
#include <QSizePolicy>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>

class XCalendar: public QWidget
{
Q_OBJECT
	//Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor)//定义一个宏
public:
	 explicit XCalendar(QWidget *parent= nullptr);
	~XCalendar()override;

signals:
	void SetCalendarTime(const QDate& data);
private:
	void initControl();
	QWidget * initTopWidget();
	void paintCell(QPainter *painter,const QRect &rect,const QDate &date)const;//画选中的单元
	QWidget * initBottomWidget();





private slots:
	void onBtnClicked();
	void setDataLabelText(int year, int mounth);

protected:
	void paintCell(QPainter *painter,const QRect &rect,QDate &date)const;

private:
	QPushButton* leftYearBtn;//年 左侧按钮
	QPushButton* rightYearBtn;

	QPushButton* leftMonthBtn;
	QPushButton* rightMonthBtn;

	QPushButton* ensureBtn;//确认按键
	QPushButton* todayBtn;//今日按键
	QLabel* dataLabel;

	QCalendarWidget* calendar;//qt的日历类，实例化为为一个子对象

};

//class QCustomStyle :public QProxyStyle
//{
//public:
//	QCustomStyle(QWidget *parent);
//private:
//	void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
//	                   QPainter *painter, const QWidget *widget) const override;
//};

#endif //CALCUMAID_XCALENDAR_H
