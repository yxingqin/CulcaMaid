#include "XWin.h"
#include <QResizeEvent>
#include <QStyle>
#include <QDesktopWidget>
#include <QApplication>
#include <QGraphicsDropShadowEffect>

const char *XWin::styleSheet = R"(
		#frame {
	      border:none;
		  border-radius: 8px;
		  background:#FFF;
		}
	)";
const char *XWinTitle::styleSheet = R"(
		QPushButton {
		    margin: 0px 8px;
		    border: none;
		}
		.QLabel {
		    margin: 0px 10px;
			font-size:12pt;
		}
)";

XWin::XWin(QWidget *Client, QWidget *parent)
	: QWidget(parent), mClient(Client), moveEnable(false), padding(15), titleHeight(32), shadowSize(6)
{
	oldPos = {};
	oldRect = {};
	mouseArea = 22;
	//设置窗口属性
	this->setWindowFlags(windowFlags() | Qt::Window);	//作为一个单独窗口显示
	this->setWindowFlag(Qt::FramelessWindowHint, true); //设置无边框属性
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setAttribute(Qt::WA_Hover, true);
	this->setObjectName("Main");
	//界面设置
	setStyleSheet(styleSheet);
	mFrame = new QFrame(this);
	mFrame->setObjectName("frame");
	mWinTitle = new XWinTitle(mFrame); //标题栏
	mWinTitle->resize(0, titleHeight);
	setClient(Client);
	// setMinimumSize(300, 300);
#if 1
	auto shadowEffect = new QGraphicsDropShadowEffect(mFrame);
	shadowEffect->setColor({"#000"});
	shadowEffect->setOffset(0, 0);
	shadowEffect->setBlurRadius(shadowSize);
	mFrame->setGraphicsEffect(shadowEffect);
#endif
	this->installEventFilter(this);
	mWinTitle->installEventFilter(this);

	auto lambda = [this]()
	{ isMaximized() ? showNormal() : showMaximized(); };

	connect(mWinTitle, &XWinTitle::clickMin, this, &QWidget::showMinimized);
	connect(mWinTitle, &XWinTitle::clickMax, this, lambda);
	connect(mWinTitle, &XWinTitle::clickClose, this, &QWidget::close);
}

XWinTitle::XWinTitle(QWidget *parent) : QWidget(parent)
{
	setStyleSheet(styleSheet);
	setAttribute(Qt::WA_StyledBackground, true);
	//控件
	btn_icon = new QPushButton(this);
	btn_icon->setIcon(style()->standardIcon(QStyle::SP_TitleBarMenuButton));
	btn_max = new QPushButton(this);
	btn_max->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
	btn_min = new QPushButton(this);
	btn_min->setIcon(style()->standardIcon(QStyle::SP_TitleBarMinButton));
	btn_close = new QPushButton(this);
	btn_close->setIcon(style()->standardIcon(QStyle::SP_DialogCloseButton));
	lbl_title = new QLabel("标题栏", this);
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
	connect(btn_min, &QPushButton::clicked, this, &XWinTitle::clickMin);
	connect(btn_max, &QPushButton::clicked, this, &XWinTitle::clickMax);
	connect(btn_close, &QPushButton::clicked, this, &XWinTitle::clickClose);
	connect(btn_icon, &QPushButton::clicked, this, &XWinTitle::clickIcon);
}

XWin::~XWin() = default;

void XWin::onResize(QResizeEvent *event)
{
	int w = event->size().width() - 2 * shadowSize;
	int h = event->size().height() - 2 * shadowSize;

	mWinTitle->setGeometry(0, 0, w, titleHeight);
	if (mClient != nullptr)
	{
		mClient->setGeometry(0, mWinTitle->height(), w, h - mWinTitle->height());
		mFrame->setGeometry(shadowSize, shadowSize, mClient->width(), mClient->height() + mWinTitle->height());
	}
	else
		mFrame->setGeometry(shadowSize, shadowSize, w, h);
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
	int X; // x所在区域
	int Y; // y所在区域
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
	return Y * 10 + X;
}

bool XWin::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == this)
	{
		switch (event->type())
		{
		case QEvent::Resize:
			onResize(static_cast<QResizeEvent *>(event));
			return true;
		case QEvent::HoverMove:
			onHover(static_cast<QHoverEvent *>(event));
			break;
		case QEvent::MouseButtonPress:
			onMousePressed(static_cast<QMouseEvent *>(event));
			break;
		case QEvent::MouseButtonRelease:
			mouseArea = 22;
			moveEnable = false;
			setCursor(Qt::ArrowCursor);
			break;
		default:
			break;
		}
	}
	else if (watched == mWinTitle && event->type() == QEvent::MouseButtonDblClick)
		isMaximized() ? showNormal() : showMaximized();
	return QObject::eventFilter(watched, event);
}

void XWin::onMousePressed(QMouseEvent *event)
{
	oldPos = event->globalPos(); //鼠标相对于 左上角的偏移
	oldRect = this->geometry();
	mouseArea = getMouseArea(event->pos());
	moveEnable = mWinTitle->geometry().contains(event->pos()); //标记可以拖动位置
}

void XWin::onHover(QHoverEvent *event)
{
	auto curArea = getMouseArea(event->pos());
	setMouseCursor(curArea);
	stretchWindow(curArea);
}

void XWin::setClient(QWidget *client)
{
	if (client != nullptr)
	{
		mClient = client;
		mClient->setParent(mFrame);
		resize(mClient->minimumWidth() + 2 * shadowSize, mClient->minimumHeight() + mWinTitle->height() + 2 * shadowSize);
		setMinimumSize(this->size());
	}
}

void XWin::setStyleSheet(const QString &styleSheet)
{
	QWidget::setStyleSheet(XWin::styleSheet + styleSheet);
}

void XWin::setTitleStyleSheet(const QString &styleSheet)
{
	mWinTitle->setStyleSheet(XWinTitle::styleSheet + styleSheet);
}

void XWin::showEvent(QShowEvent *event)
{
	//解决有时候窗体重新显示的时候假死不刷新的BUG
	setAttribute(Qt::WA_Mapped);
	QWidget::showEvent(event);
}

void XWin::setMouseCursor(unsigned short area)
{
	switch (area)
	{
	//左上 右下
	case 11:
	case 33:
		setCursor(Qt::SizeFDiagCursor);
		break;
		//左下 右上
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
void XWin::stretchWindow(unsigned short area)
{
	auto curPos = QCursor::pos();
	if (mouseArea != 22)
	{
		int offsetW = oldPos.x() - curPos.x();
		int offsetH = oldPos.y() - curPos.y();
		QRect rect; //窗口被拖动之后的大小
		switch (mouseArea)
		{
		//左上
		case 11:
			rect.setRect(curPos.x(), curPos.y(), oldRect.width() + offsetW, oldRect.height() + offsetH);
			break;
			//右下
		case 33:
			rect.setRect(oldRect.x(), oldRect.y(), oldRect.width() - offsetW, oldRect.height() - offsetH);
			break;
			//右上
		case 13:
			rect.setRect(curPos.x() - oldRect.width() + offsetW, curPos.y(), oldRect.width() - offsetW,
						 oldRect.height() + offsetH);
			break;
			//左下
		case 31:
			rect.setRect(curPos.x(), curPos.y() + offsetH - oldRect.height(), oldRect.width() + offsetW,
						 oldRect.height() - offsetH);
			break;
			//上
		case 12:
			rect.setRect(oldRect.x(), oldRect.y() - offsetH, oldRect.width(), oldRect.height() + offsetH);
			break;
			//下
		case 32:
			rect.setRect(oldRect.x(), oldRect.y(), oldRect.width(), oldRect.height() - offsetH);
			break;
			//左右
		case 21:
			rect.setRect(oldRect.x() - offsetW, oldRect.y(), oldRect.width() + offsetW, oldRect.height());
			break;
		case 23:
			rect.setRect(oldRect.x(), oldRect.y(), oldRect.width() - offsetW, oldRect.height());
			break;
		default:
			break;
		}

		if (rect.width() >= this->minimumWidth() && rect.height() >= this->minimumHeight())
			setGeometry(rect);
	}
	//拖动窗口
	if (moveEnable && mouseArea == 22)
		this->move(curPos + (QPoint{oldRect.x(), oldRect.y()} - oldPos)); //全局位置+偏移== 移动位置
}

void XWin::keyPressEvent(QKeyEvent *event)
{
#if 0
	QKeyEvent* copyEvent=new QKeyEvent(QEvent::KeyPress,event->key(),Qt::NoModifier);
	QApplication::postEvent(mClient,copyEvent);
	event->ignore();
#else
	QWidget::keyPressEvent(event);
#endif
}
