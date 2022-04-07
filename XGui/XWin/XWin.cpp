#include "XWin.h"
#include <QResizeEvent>
#include <QStyle>
#include <QDesktopWidget>
#include <QApplication>
#include <QGraphicsDropShadowEffect>

XWin::XWin(QWidget *Client, QWidget *parent)
		: QWidget(parent), mClient(Client), moveEnable(false), resizeEnable(false), padding(10), titleHeight(32), shadowSize(5)
{
	oldPos={};
	oldRect={};

	//设置窗口属性
	this->setWindowFlags(windowFlags() | Qt::Window);//作为一个单独窗口显示
	this->setWindowFlag(Qt::FramelessWindowHint, true);//设置无边框属性
	this->setAttribute(Qt::WA_TranslucentBackground,true);
	this->setAttribute(Qt::WA_Hover, true);

	//界面设置
	setStyleSheet(R"(
		.QFrame {
		  background-color: #F3F3F3;
		  border: 1px black;
		  border-radius: 8px;
		}
	)");
	mFrame=new QFrame(this);
	mWinTitle = new XWinTitle(mFrame);//标题栏
	setClient(Client);
	auto shadowEffect = new QGraphicsDropShadowEffect(mFrame);
	shadowEffect->setColor({"#778899"});
	shadowEffect->setOffset(2, 2);
	shadowEffect->setBlurRadius(2*shadowSize);
	mFrame->setGraphicsEffect(shadowEffect);
	this->installEventFilter(this);

	connect(mWinTitle,&XWinTitle::clickMin,this,&QWidget::showMinimized);
	connect(mWinTitle,&XWinTitle::clickMax,this,[this](){
		isMaximized()?showMinimized():showMaximized();
	});
	connect(mWinTitle,&XWinTitle::clickClose,this,&QWidget::close);

}

XWinTitle::XWinTitle(QWidget *parent) : QWidget(parent)
{
	setStyleSheet(QString::fromUtf8("QPushButton{\n"
	                                "margin:0px 8px;\n"
	                                "\n"
	                                "border:none;\n"
	                                "}\n"
	                                "#btn_icon {\n"
	                                "margin:2px;\n"
	                                "}\n"
	                                "#lbl_title {\n"
	                                "margin:10px;\n"
	                                "}"));
	//控件
	btn_icon = new QPushButton(this);
	btn_icon->setIcon(style()->standardIcon(QStyle::SP_TitleBarMenuButton));
	btn_max = new QPushButton(this);
	btn_max->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
	btn_min = new QPushButton(this);
	btn_min->setIcon(style()->standardIcon(QStyle::SP_TitleBarMinButton));
	btn_close = new QPushButton(this);
	btn_close->setIcon(style()->standardIcon(QStyle::SP_DialogCloseButton));
	lbl_title = new QLabel("标题栏",this);
	//布局
	horizontalLayout = new QHBoxLayout(this);
	horizontalLayout->setSpacing(0);
	horizontalLayout->setContentsMargins(0, 0, 0, 0);
	horizontalLayout->addWidget(btn_icon);
	horizontalLayout->addWidget(lbl_title);
	horizontalSpacer = new QSpacerItem(40, 32, QSizePolicy::Expanding, QSizePolicy::Minimum);
	horizontalLayout->addItem(horizontalSpacer);
	horizontalLayout->addWidget(btn_min);
	horizontalLayout->addWidget(btn_max);
	horizontalLayout->addWidget(btn_max);
	horizontalLayout->addWidget(btn_close);
	//转发信号
	connect(btn_min,&QPushButton::clicked,this,&XWinTitle::clickMin);
	connect(btn_max,&QPushButton::clicked,this,&XWinTitle::clickMax);
	connect(btn_close,&QPushButton::clicked,this,&XWinTitle::clickClose);
	connect(btn_icon,&QPushButton::clicked,this,&XWinTitle::clickIcon);

}


XWin::~XWin()
{

}


void XWin::resizeEvent(QResizeEvent *event)//手动布局
{
	auto rect = event->size();
	mFrame->setGeometry(shadowSize,shadowSize,rect.width()-2*shadowSize,rect.height()-2*shadowSize);
	mWinTitle->setGeometry(0, 0,mFrame->width(), titleHeight);
	if (mClient != nullptr)
		mClient->setGeometry(0, mWinTitle->height(), mFrame->width(), mFrame->height() - mWinTitle->height());
	QWidget::resizeEvent(event);
}

int XWin::getTitleHeight() const
{
	return titleHeight;
}

void XWin::setTitleHeight(int titleHeight)
{
	XWin::titleHeight = titleHeight;
}

int XWin::getPadding() const
{
	return padding;
}

void XWin::setPadding(int padding)
{
	XWin::padding = padding;
}

void XWin::setTitleText(const QString &text)
{
	mWinTitle->lbl_title->setText(text);
}

void XWin::setWinIcon(const QIcon &icon)
{
	mWinTitle->btn_icon->setIcon(icon);
}

void XWin::setMaxIcon(const QIcon &icon)
{
	mWinTitle->btn_max->setIcon(icon);
}

void XWin::setMinIcon(const QIcon &icon)
{
	mWinTitle->btn_min->setIcon(icon);
}

void XWin::setCloseIcon(const QIcon &icon)
{
	mWinTitle->btn_close->setIcon(icon);
}

unsigned short XWin::getMouseArea(const QPoint &pos)
{
	int posX = pos.x();
	int posY = pos.y();
	int Width = width();
	int Height = height();
	int X = 0;//x所在区域
	int Y = 0;//y所在区域
	//判断x所在区域
	if (posX > (Width - padding))
		X = 3;
	else if (posX < padding)
		X = 1;
	else
		X = 2;

	//判断y所在区域
	if (posY > (Height - padding))
		Y = 3;
	else if (posY < padding)
		Y = 1;
	else
		Y = 2;
	return Y*10+X;
}

bool XWin::eventFilter(QObject *watched, QEvent *event)
{
	switch (event->type())
	{
		case QEvent::HoverMove:
			onHover(static_cast<QHoverEvent*>(event));
			break;
		case QEvent::MouseButtonPress:
			onMousePressed(static_cast<QMouseEvent*>(event));
			break;
		case QEvent::MouseButtonRelease:
			resizeEnable= false;
			moveEnable= false;
			setCursor(Qt::ArrowCursor);
			break;
		default:
			break;
	}
	return QObject::eventFilter(watched, event);
}

void XWin::onMousePressed(QMouseEvent *event)
{
	oldPos=event->globalPos();//鼠标相对于 左上角的偏移
	oldRect=this->geometry();

	mouseArea= getMouseArea(event->pos());

	resizeEnable= (mouseArea!=22);//标记可以调整大小
	moveEnable=mWinTitle->geometry().contains(event->pos());//标记可以拖动位置
}

void XWin::onHover(QHoverEvent *event)
{
	int area= getMouseArea(event->pos());
	auto curRect=this->geometry();
	auto curPos=QCursor::pos();
	int offsetW=oldPos.x()-curPos.x();
	int offsetH=oldPos.y()-curPos.y();
	switch (area)
	{
		//左上
		case 11:
		{
			if(resizeEnable)
				this->setGeometry(curPos.x(),curPos.y(),oldRect.width()+offsetW,oldRect.height()+offsetH);
			setCursor(Qt::SizeFDiagCursor);
			break;
		}
		//右下
		case 33:
		{
			if(resizeEnable)
				this->setGeometry(oldRect.x(),oldRect.y(),oldRect.width()-offsetW,oldRect.height()-offsetH);
			setCursor(Qt::SizeFDiagCursor);
			break;
		}
			//右上
		case 13:
		{
			if(resizeEnable)
				this->setGeometry(curPos.x()-oldRect.width()+offsetW,curPos.y(),oldRect.width()-offsetW,oldRect.height()+offsetH);
			setCursor(Qt::SizeBDiagCursor);
			break;
		}
		//左下
		case 31:
		{
			if(resizeEnable)
				this->setGeometry(curPos.x(),curPos.y()+offsetH-oldRect.height(),oldRect.width()+offsetW,oldRect.height()-offsetH);
			setCursor(Qt::SizeBDiagCursor);
			break;
		}
			//上
		case 12:
		{
			if(resizeEnable)
				this->setGeometry(oldRect.x(),oldRect.y()-offsetH,oldRect.width(),oldRect.height()+offsetH);
			setCursor(Qt::SizeVerCursor);
			break;
		}
		//下
		case 32:
		{
			if(resizeEnable)
				this->setGeometry(oldRect.x(),oldRect.y(),oldRect.width(),oldRect.height()-offsetH);
			setCursor(Qt::SizeVerCursor);
			break;
		}
			//左右
		case 21:
		{
			if(resizeEnable)
				this->setGeometry(oldRect.x()-offsetW,oldRect.y(),oldRect.width()+offsetW,oldRect.height());
			setCursor(Qt::SizeHorCursor);
			break;
		}
		case 23:
		{
			if(resizeEnable)
				this->setGeometry(oldRect.x(),oldRect.y(),oldRect.width()-offsetW,oldRect.height());
			setCursor(Qt::SizeHorCursor);
			break;
		}
		default:
			setCursor(Qt::ArrowCursor);
			break;
	}

	//拖动窗口
	if(moveEnable&&!resizeEnable)
		this->move(curPos+(QPoint{oldRect.x(),oldRect.y()}-oldPos));//全局位置+偏移== 移动位置
}



void XWin::setClient(QWidget *client)
{
	if(client!= nullptr)
	{
		mClient=client;
		mClient->setParent(mFrame);
	}
}


