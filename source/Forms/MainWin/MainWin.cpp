#include "MainWin.h"
#include "Load.h"
#include "ui_MainWin.h"
#include <QDebug>

#include <QCalendarWidget>

constexpr int NARROW_WIDTH = 660;
constexpr int MENU_WIDTH = 256;
MainWin::MainWin(QWidget *parent) : QWidget(parent), ui(new Ui::MainWin)
{
	ui->setupUi(this);
	//加载qss
	setStyleSheet(Load::loadStyle(":/qss/mainwin.qss"));
	setAttribute(Qt::WA_StyledBackground, true);
	//跟踪鼠标位置
	setMouseTracking(true);
	//弹出式菜单
	mPopMenu = new PopMenu(ui->wdg_main);
	mPopMenu->move(-mPopMenu->width() - 5, 0);
	ui->btn_popMune->raise(); //防止被遮挡
	connect(ui->btn_popMune, &QPushButton::clicked, this, &MainWin::switchMenu);
	//子界面显示
	ui->swdg_sub->raise(); //防止被遮挡
	connect(ui->btn_tool, &QPushButton::clicked, this, &MainWin::switchSubPage);
	//设置页面切换
	connect(mPopMenu, &PopMenu::switchPage, this, &MainWin::switchPage);
	ui->swdg_main->setCurrentIndex(0);
	ui->swdg_sub->setCurrentIndex(0);
	//处理某部分事件
	mPopMenu->installEventFilter(this);
	ui->page_sub1->installEventFilter(this);
	ui->lbl_title->installEventFilter(this);
	//动画
	animationMenu = new QPropertyAnimation(mPopMenu, "pos", this);
	animationSub1 = new QPropertyAnimation(ui->swdg_sub, "geometry", this);



	//槽 链接
	connect(ui->pStandard,&PageStandard::sendHistory,ui->pHistory,&PageHistory::addHistory);
	connect(ui->pScience,&PageScience::sendHistory,ui->pHistory,&PageHistory::addHistory);


	setMinimumSize(320, 500);
	ui->lbl_title->setText("标准");
	ui->swdg_main->currentWidget()->setFocus();
	ui->swdg_main->setCurrentIndex(4);
	//ui->swdg_main->setCurrentIndex(0);
}

MainWin::~MainWin()
{
	delete ui;
}

void MainWin::switchMenu() //切换菜单 调整大小 添加动画
{

	if (mPopMenu->x() < 0)
	{
		int w = this->width() / 2;
		w = w > MENU_WIDTH ? MENU_WIDTH : w;
		mPopMenu->resize(w, ui->wdg_main->height());
		animationMenu->setStartValue(QPoint(-w - 5, 2));
		animationMenu->setEndValue(QPoint(0, 2));
		animationMenu->setEasingCurve(QEasingCurve::OutCurve);
		animationMenu->setDuration(150);
	}
	else
	{
		animationMenu->setStartValue(QPoint(0, 2));
		animationMenu->setEndValue(QPoint(-mPopMenu->width() - 5, 2));
		animationMenu->setEasingCurve(QEasingCurve::InQuad);
		animationMenu->setDuration(100);
	}

	animationMenu->start();
	if (ui->swdg_sub->y() < this->height()) //如果subpage显示关闭子窗口
		switchSubPage();
}

void MainWin::resizeEvent(QResizeEvent *event)
{
	auto size = event->size();
	//手动调整子页面和主页面的大小与位置
	if (size.width() >= NARROW_WIDTH)
	{
		// 280+380    subpage移动主窗口的左边
		ui->btn_tool->hide();
		int w = this->width() / 5;
		w = w < 280 ? 280 : w;
		ui->wdg_main->setGeometry(0, 0, size.width() - w, size.height());
		ui->swdg_sub->setGeometry(ui->wdg_main->width(), 0, w, size.height());
		ui->swdg_sub->setGraphicsEffect(nullptr);
	}
	else
	{
		// subpage移动到窗口下面 主页面 占满布局
		ui->btn_tool->show();
		ui->wdg_main->setGeometry(0, 0, this->width(), size.height());
		ui->swdg_sub->move(0, this->height());
	}

	if (mPopMenu->x() >= 0) //调整MENU的高度
	{
		int w = this->width() / 2;
		w = w > 256 ? 256 : w;
		mPopMenu->setGeometry(0, 0, w, ui->wdg_main->height());
	}

	QWidget::resizeEvent(event);
}

void MainWin::switchSubPage()
{
	if (this->width() < NARROW_WIDTH)
	{
		if (ui->swdg_sub->y() >= this->height()) //显示
		{
			animationSub1->setStartValue(QRect(0, this->height(), this->width(), this->height() / 2));
			animationSub1->setEndValue(QRect(0, this->height() / 2, this->width(), this->height() / 2));
			animationSub1->setEasingCurve(QEasingCurve::OutCurve);
			animationSub1->setDuration(150);
			//阴影
			auto shadowEffect = new QGraphicsDropShadowEffect(ui->swdg_sub);
			shadowEffect->setColor({"#778899"});
			shadowEffect->setOffset(0, 0);
			shadowEffect->setBlurRadius(22);
			ui->swdg_sub->setGraphicsEffect(shadowEffect);
			if (mPopMenu->x() >= 0)
				switchMenu();
		}
		else //隐藏
		{
			animationSub1->setStartValue(QRect(0, this->height() / 2, this->width(), this->height() / 2));
			animationSub1->setEndValue(QRect(0, this->height(), this->width(), this->height() / 2));
			animationSub1->setEasingCurve(QEasingCurve::OutCurve);
			animationSub1->setDuration(150);
		}
		animationSub1->start();
	}
}

bool MainWin::eventFilter(QObject *watched, QEvent *event)
{

	switch (event->type())
	{
	case QEvent::Leave:
	{
		if (mPopMenu->x() >= 0)
			switchMenu();
		if (ui->swdg_sub->y() < this->height())
			switchSubPage();
		break;
	}
	case QEvent::MouseButtonPress:
	{
		if (watched == ui->lbl_title)
			switchMenu();
		break;
	}
	default:
		break;
	}
	return QObject::eventFilter(watched, event);
}

void MainWin::switchPage(int row, QString title)
{
	ui->swdg_main->setCurrentIndex(row);
	ui->lbl_title->setText(title);
	ui->btn_tool->show();
	ui->swdg_main->currentWidget()->setFocus();
	switchMenu();
}

bool MainWin::event(QEvent *event)
{
	return QWidget::event(event);
}

void MainWin::keyPressEvent(QKeyEvent *event)
{
	if(ui->swdg_main->currentIndex()==0)
		ui->pStandard->onKeyPress(event);
	QWidget::keyPressEvent(event);
}
