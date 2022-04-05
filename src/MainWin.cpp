#include <QDesktopWidget>
#include <QAbstractButton>
#include <QMouseEvent>
#include "MainWin.h"
#include <QDebug>
#include "LoadFile.h"
#include "ui_MainWin.h"


MainWin::MainWin(QWidget *parent) :
		QMainWindow(parent), ui(new Ui::MainWin)
{
	ui->setupUi(this);
	//加载qss
	setStyleSheet(Load::loadStyle(":/res/qss/mainwin.qss"));

//    qputenv("QT_SCALE_FACTOR", "1.25");
	QDesktopWidget *desktop = QApplication::desktop();//窗口居中
	this->setGeometry((desktop->width() - width()) / 2, height() / 2, 420, 610);
	//阴影
	shadowEffect=new QGraphicsDropShadowEffect(this);
	shadowEffect->setColor("#778899");
	shadowEffect->setOffset(0,0);
	shadowEffect->setBlurRadius(22);
	//弹出式菜单
	mPopMenu = new PopMenu(ui->centralwidget);
	mPopMenu->move(-mPopMenu->width(), 0);
	ui->btn_popMune->raise();//防止被遮挡
	connect(ui->btn_popMune, &QPushButton::clicked, this, &MainWin::switchMenu);
	//历史记录页面切换
	ui->page_sub1->setParent(this);
	ui->page_sub1->setGeometry(0, this->height(), this->width(), this->height() / 2);
	ui->page_sub1->show();
	connect(ui->btn_history, &QPushButton::clicked, this, &MainWin::switchHistory);
	//设置页面切换
	connect(mPopMenu->list_culca, &QListWidget::currentRowChanged, this, &MainWin::switchPageCal);
	ui->swdg_main->setCurrentIndex(0);
	ui->swdg_sub->setCurrentIndex(0);
	//处理某部分事件
	installEventFilter(this);

}

MainWin::~MainWin()
{
	delete ui;
}

void MainWin::switchMenu()//切换菜单
{
	QPropertyAnimation *pAnimation = new QPropertyAnimation(mPopMenu, "pos", mPopMenu);
	if (mPopMenu->x() < 0)
	{
		int w = this->width() / 2;
		w = w > 256 ? 256 : w;
		mPopMenu->resize(w, this->height());
		pAnimation->setStartValue(QPoint(-w, 0));
		pAnimation->setEndValue(QPoint(0, 0));
		pAnimation->setEasingCurve(QEasingCurve::OutCurve);
		pAnimation->setDuration(150);
	} else
	{
		pAnimation->setStartValue(QPoint(0, 0));
		pAnimation->setEndValue(QPoint(-mPopMenu->width(), 0));
		pAnimation->setEasingCurve(QEasingCurve::InQuad);
		pAnimation->setDuration(100);
	}
	pAnimation->start();
	if (ui->page_sub1->y()<this->height())
		switchHistory();
}

void MainWin::resizeEvent(QResizeEvent *event)
{
	auto size = event->size();

	if (mPopMenu->x() >= 0)//调整菜单高度
	{
		int w = this->width() / 2;
		w = w > 256 ? 256 : w;
		mPopMenu->resize(w, this->height());
	}
	//280+380 显示子窗口
	if (size.width() >= 660)
	{
		ui->btn_history->hide();
		ui->page_sub1->setParent(ui->swdg_sub);
		ui->page_sub1->setGeometry(0, 0, 280, this->height());
		ui->swdg_sub->show();
		ui->page_sub1->setGraphicsEffect(nullptr);
	} else
	{
		ui->btn_history->show();
		ui->swdg_sub->hide();
	}
	QWidget::resizeEvent(event);
}

void MainWin::switchHistory()
{
	if (this->width() < 660)
	{
		ui->page_sub1->setParent(this);
		ui->page_sub1->setGraphicsEffect(shadowEffect);
		QPropertyAnimation *pAnimation = new QPropertyAnimation(ui->page_sub1, "geometry", ui->page_sub1);
		if (ui->page_sub1->y() >= this->height() ) //显示
		{
			pAnimation->setStartValue(QRect(0, this->height(), this->width(), this->height() / 2));
			pAnimation->setEndValue(QRect(0, this->height() / 2, this->width(), this->height() / 2));
			pAnimation->setEasingCurve(QEasingCurve::OutCurve);
			pAnimation->setDuration(150);
			if (mPopMenu->x() >= 0)
				switchMenu();
		} else//隐藏
		{
			pAnimation->setStartValue(QRect(0, this->height()/2, this->width(), this->height() / 2));
			pAnimation->setEndValue(QRect(0, this->height(), this->width(), this->height() / 2));
			pAnimation->setEasingCurve(QEasingCurve::OutCurve);
			pAnimation->setDuration(150);
		}
		pAnimation->start();
	}
}

bool MainWin::eventFilter(QObject *watched, QEvent *event)
{
	if(event->type()==QEvent::MouseButtonPress)
	{
		QMouseEvent* mouseEvent=static_cast<QMouseEvent*>(event);
		auto pos=mouseEvent->pos();
		if(!mPopMenu->geometry().contains(pos)&&mPopMenu->x() >= 0)
			switchMenu();
		if(!ui->page_sub1->geometry().contains(pos)&&!ui->page_sub1->y()>=this->height())
			switchHistory();
	}
	return QObject::eventFilter(watched, event);
}

void MainWin::switchPageCal(int row)
{
	ui->swdg_main->setCurrentIndex(row);
	switchMenu();
}









