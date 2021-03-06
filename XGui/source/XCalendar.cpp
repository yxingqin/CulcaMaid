//
// Created by xzl01 on 2022/4/15.
//
#include <QCalendarWidget>
#include "../include/XCalendar.h"
#include <QDebug>
#include <QDebug>
XCalendar::XCalendar(QWidget *parent)
	: QWidget(parent)
{

	
	initControl();
	
}

XCalendar::~XCalendar()
{
}

void XCalendar::initControl() //主要设置
{
	calendar = new QCalendarWidget(this);
	setLocale(QLocale(QLocale::Chinese));								  //设置中文
	calendar->setNavigationBarVisible(false);							  //关闭导航条
	calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader); //去掉列表头
	calendar->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
	calendar->setSelectionMode(QCalendarWidget::SingleSelection); //单选
	calendar->setMinimumSize(100, 120);//设置日历组件大小
	calendar->setAttribute(Qt::WA_TranslucentBackground);




	QTextCharFormat format; //设置文本框的显示
	format.setForeground(QColor(51, 51, 51));
	format.setBackground(QColor("#EDF5F9"));
	format.setFontFamily("Microsoft YaHei"); //后期这里要改掉 可能有版权风险
	format.setFontPointSize(8);
	format.setFontWeight(QFont::Medium);
	calendar->setWeekdayTextFormat(Qt::Saturday, format);
	calendar->setWeekdayTextFormat(Qt::Sunday, format);

	QWidget *topWidget= initTopWidget(); //初始化上面的插件
	QWidget *bottomWidget =  initBottomWidget();
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(topWidget);
	mainLayout->addWidget(calendar);
	mainLayout->addWidget(bottomWidget);

	connect(calendar, SIGNAL(currentPageChanged(int, int)), this, SLOT(setDataLabelText(int, int)));
}

QWidget * XCalendar::initTopWidget()
{
	QWidget *topWidget = new QWidget(this);
	topWidget->setObjectName("CalendarTopWidget");
	topWidget->setFixedHeight(40);
	topWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

	QHBoxLayout *hboxLayout_top = new QHBoxLayout();  //水平布局
	hboxLayout_top->setContentsMargins(12, 0, 12, 0); //设置边距
	hboxLayout_top->setSpacing(4);					  //各个控件之间的上下边距

	leftMonthBtn = new QPushButton(this);
	rightMonthBtn = new QPushButton(this);
	leftYearBtn = new QPushButton(this);
	rightYearBtn = new QPushButton(this);
	dataLabel = new QLabel;

	leftMonthBtn->setText("<"); //左右切换图标
	rightMonthBtn->setText(">");
	leftYearBtn->setText("<<");
	rightYearBtn->setText(">>");


	leftMonthBtn->setObjectName("XCalendarLeftButton");
	rightMonthBtn->setObjectName("XCalendarRightButton");
	rightYearBtn->setObjectName("XCalendarRightYearButton");
	leftYearBtn->setObjectName("XCalendarLeftYearButton");
	dataLabel->setObjectName("XCalendarDataLabel");
	dataLabel->setStyleSheet("XCalendarDataLabel{font-size:10pt;}");
	// btn大小设置
	leftMonthBtn->setFixedSize(25, 25);
	rightMonthBtn->setFixedSize(25, 25);
	leftYearBtn->setFixedSize(35,25);
	rightYearBtn->setFixedSize(35,25);
	//布局设置
	hboxLayout_top->addStretch(); //设计师中的弹簧
	hboxLayout_top->addWidget(leftYearBtn);
	hboxLayout_top->addWidget(leftMonthBtn);
	hboxLayout_top->addWidget(dataLabel);
	hboxLayout_top->addWidget(rightMonthBtn);
	hboxLayout_top->addWidget(rightYearBtn);
	hboxLayout_top->addStretch();
	hboxLayout_top->setAlignment(Qt::AlignCenter); //设置居中

	topWidget->setLayout(hboxLayout_top);


	connect(leftMonthBtn, &QPushButton::clicked, this, &XCalendar::onBtnClicked);
	connect(rightMonthBtn, &QPushButton::clicked, this, &XCalendar::onBtnClicked);
	connect(rightYearBtn, &QPushButton::clicked, this, &XCalendar::onBtnClicked);
	connect(leftYearBtn, &QPushButton::clicked, this, &XCalendar::onBtnClicked);

	setDataLabelText(calendar->selectedDate().year(), calendar->selectedDate().month());
	return topWidget;
}

QWidget * XCalendar::initBottomWidget()
{
	QWidget *bottomWidget = new QWidget;
	bottomWidget->setObjectName("XCalendarBottomWidget");
	bottomWidget->setFixedHeight(40);
	bottomWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

	QHBoxLayout *hboxLayout_bottom = new QHBoxLayout();

	ensureBtn = new QPushButton(this);
	ensureBtn->setObjectName("XCalendarEnusreBtn");
	ensureBtn->setText("OK");
	ensureBtn->setFixedSize(70, 22);

	todayBtn = new QPushButton(this);
	todayBtn->setObjectName("XCanlendarOkBtn");
	todayBtn->setText("ToDay");
	todayBtn->setFixedSize(70, 22);

	hboxLayout_bottom->setContentsMargins(12, 0, 12, 0);
	hboxLayout_bottom->setSpacing(4);
	hboxLayout_bottom->addStretch();
	hboxLayout_bottom->addWidget(todayBtn);
	hboxLayout_bottom->addWidget(ensureBtn);
	bottomWidget->setLayout(hboxLayout_bottom);


	connect(ensureBtn, &QPushButton::clicked, this, &XCalendar::onBtnClicked);
	connect(todayBtn, &QPushButton::clicked, this, &XCalendar::onBtnClicked);
	return bottomWidget;
}

void XCalendar::onBtnClicked() //重写鼠标点击事件
{
	QPushButton *senderBtn = qobject_cast<QPushButton *>(sender()); //记录信号发出的对象
	if (senderBtn == leftMonthBtn)
	{
		calendar->showPreviousMonth();
	}
	else if (senderBtn == rightMonthBtn)
	{
		calendar->showNextMonth();
	}
	else if(senderBtn == leftYearBtn)
	{
		calendar->showPreviousYear();
	}
	else if(senderBtn == rightYearBtn)
	{
		calendar->showNextYear();
	}
	else if (senderBtn == todayBtn)
	{
		calendar->showToday(); //展示到今天
	}
	else if(senderBtn == ensureBtn)
	{
		//signalSetCalendarTime(calendar->selectedDate());
		emit SetCalendarTime(calendar->selectedDate());
		qDebug()<<calendar->selectedDate();
	}
}
void XCalendar::setDataLabelText(int year, int month)
{
	dataLabel->setText(QStringLiteral("%1年%2月").arg(year).arg(month));
}

