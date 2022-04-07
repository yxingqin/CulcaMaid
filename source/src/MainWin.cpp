#include <QDesktopWidget>
#include <QAbstractButton>
#include <QMouseEvent>
#include "MainWin.h"
#include <QDebug>
#include <QPainter>
#include <QStylePainter>
#include "LoadFile.h"
#include "ui_MainWin.h"
constexpr int NARROW_WIDTH = 660;
constexpr int MENU_WIDTH = 256;
constexpr int WIN_TITLE_HEIGHT = 32;
constexpr int MARGIN  = 2;//边距
MainWin::MainWin(QWidget *parent) :
		QWidget(parent), ui(new Ui::MainWin), canMove(false)
{
	ui->setupUi(this);
	//加载qss
	setStyleSheet(Load::loadStyle(":/res/qss/mainwin.qss"));
	//去除边框
	setWindowFlag(Qt::FramelessWindowHint, true);
	//this->setAttribute(Qt::WA_TranslucentBackground);
	//主页面阴影
//	auto shadow=new QGraphicsDropShadowEffect(this);
//	shadow->setColor("#778899");
//	shadow->setOffset(2,0);
//	shadow->setBlurRadius(8);
//	this->setGraphicsEffect(shadow);
	//跟踪鼠标位置
	setMouseTracking(true);
	//title
	connect(ui->btn_close,&QPushButton::clicked,this,&QWidget::close);
	connect(ui->btn_minsize,&QPushButton::clicked,this,&QWidget::showMinimized);
	connect(ui->btn_maxsize,&QPushButton::clicked,this,&QWidget::showMaximized);
	//窗口位置
	QDesktopWidget *desktop = QApplication::desktop();//窗口居中
	this->setGeometry((desktop->width() - width()) / 2, height() / 2, 420, 610);
	//弹出式菜单
	mPopMenu = new PopMenu(ui->wdg_main);

	mPopMenu->move(-mPopMenu->width(), 0);
	ui->btn_popMune->raise();//防止被遮挡
	connect(ui->btn_popMune, &QPushButton::clicked, this, &MainWin::switchMenu);
	//子界面显示
	connect(ui->btn_tool, &QPushButton::clicked, this, &MainWin::switchSubPage);
	//设置页面切换
	connect(mPopMenu->list_culca, &QListWidget::currentRowChanged, this, &MainWin::switchPageCal);
	ui->swdg_main->setCurrentIndex(0);
	ui->swdg_sub->setCurrentIndex(0);
	//处理某部分事件
	mPopMenu->installEventFilter(this);
	ui->page_sub1->installEventFilter(this);
	ui->lbl_title->installEventFilter(this);
	//动画
	animationMenu = new QPropertyAnimation(mPopMenu, "pos", this);
	animationSub1 = new QPropertyAnimation(ui->swdg_sub, "geometry", this);

}

MainWin::~MainWin()
{
	delete ui;
}

void MainWin::switchMenu()//切换菜单 调整大小 添加动画
{

	if (mPopMenu->x() < 0)
	{
		int w = this->width() / 2;
		w = w > MENU_WIDTH ? MENU_WIDTH : w;
		mPopMenu->resize(w, ui->wdg_main->height());
		animationMenu->setStartValue(QPoint(-w, 2));
		animationMenu->setEndValue(QPoint(0, 2));
		animationMenu->setEasingCurve(QEasingCurve::OutCurve);
		animationMenu->setDuration(150);
	} else
	{
		animationMenu->setStartValue(QPoint(0, 2));
		animationMenu->setEndValue(QPoint(-mPopMenu->width(), 2));
		animationMenu->setEasingCurve(QEasingCurve::InQuad);
		animationMenu->setDuration(100);
	}

	animationMenu->start();
	if (ui->swdg_sub->y() < this->height())//如果subpage显示关闭子窗口
		switchSubPage();
}

void MainWin::resizeEvent(QResizeEvent *event)
{
	auto size = event->size();
	//调整界面的高度
	ui->win_title->setGeometry(0,0,this->width(),WIN_TITLE_HEIGHT);
	int height=this->height()-WIN_TITLE_HEIGHT;
	//手动调整子页面和主页面的大小与位置
	if (size.width() >= NARROW_WIDTH)
	{
		//280+380    subpage移动主窗口的左边
		ui->btn_tool->hide();
		int w = this->width() / 5;
		w = w < 280 ? 280 : w;
		ui->wdg_main->setGeometry(0, WIN_TITLE_HEIGHT, this->width() - w, height);
		ui->swdg_sub->setGeometry(ui->wdg_main->width(), WIN_TITLE_HEIGHT, w, height);
		ui->swdg_sub->setGraphicsEffect(nullptr);
	} else
	{
		//subpage移动到窗口下面 主页面 占满布局
		ui->btn_tool->show();
		ui->wdg_main->setGeometry(0, WIN_TITLE_HEIGHT, this->width(), height);
		ui->swdg_sub->move(0, this->height());
	}


	if (mPopMenu->x() >= 0)//调整MENU的高度
	{
		int w = this->width() / 2;
		w = w > 256 ? 256 : w;
		mPopMenu->setGeometry(0,2,w, ui->wdg_main->height());
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
		} else//隐藏
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

void MainWin::switchPageCal(int row)
{
	ui->swdg_main->setCurrentIndex(row);
	switchMenu();
}

void MainWin::mouseMoveEvent(QMouseEvent *event)
{

	stretch(event->pos());

	//拖动窗口
	if(canMove == true)
		this->move(event->globalPos()+mouseRPos);
}//TODO: 窗口拖动大小


void MainWin::mousePressEvent(QMouseEvent *event)
{
	mouseRPos=this->pos()-event->globalPos();//记录相对位置
	canMove=ui->win_title->geometry().contains(event->pos())?true:false;//可以拖动

}

void MainWin::mouseReleaseEvent(QMouseEvent *event)
{
	canMove= false;

	QWidget::mouseReleaseEvent(event);
}

int MainWin::getPosArea(const QPoint &point)
{
	int posX = point.x();
	int posY = point.y();
	int Width = width();
	int Height = height();
	int X = 0;//x所在区域
	int Y = 0;//y所在区域
	//判断x所在区域
	if (posX > (Width - MARGIN))
		X = 3;
	else if (posX < MARGIN)
		X = 1;
	else
		X = 2;

	//判断y所在区域
	if (posY > (Height - MARGIN))
		Y = 3;
	else if (posY < MARGIN)
		Y = 1;
	else
		Y = 2;
	return Y*10+X;
}

void MainWin::mouseDoubleClickEvent(QMouseEvent *event)
{
	if(ui->win_title->geometry().contains(event->pos()))
		showMaximized();
	QWidget::mouseDoubleClickEvent(event);
}

void MainWin::stretch(const QPoint &point)
{
	//设置光标样式
	if(!isMaximized())
	{

		switch (getPosArea(point))
		{
			//左上 右下
			case 11:
			case 33:
				setCursor(Qt::SizeFDiagCursor);
				break;
				//右上 左下
			case 13:
			case 31:
				setCursor(Qt::SizeBDiagCursor);
				break;
				//上下
			case 12:
			case 32:
				setCursor(Qt::SizeVerCursor);
				break;
				//左右
			case 21:
			case 23:
				setCursor(Qt::SizeHorCursor);
				break;
			default:
				setCursor(Qt::ArrowCursor);

				break;
		}



	}

}

bool MainWin::event(QEvent *event)
{
	//qDebug()<<event;
	return QWidget::event(event);
}

void MainWin::paintEvent(QPaintEvent *event)
{
	QStyleOption option;
	option.init(this);
	QStylePainter stylePainter(this);
	stylePainter.drawPrimitive(QStyle::PE_Widget, option);
	QWidget::paintEvent(event);
}
