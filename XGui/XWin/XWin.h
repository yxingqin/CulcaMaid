#ifndef XGUI_XWIN_H
#define XGUI_XWIN_H
#include <QObject>
#include <QWidget>
#include <QInternal>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

class XWin;

/**
 * @brief 自定义标题栏
 */
class XWinTitle:public QWidget
{
	friend class XWin;
Q_OBJECT
public:
	XWinTitle(QWidget *parent);
signals://传递给父窗口
	void clickMax();
	void clickMin();
	void clickClose();
	void clickIcon();
private:
	QHBoxLayout *horizontalLayout;
	QPushButton *btn_icon;
	QLabel *lbl_title;
	QSpacerItem *horizontalSpacer;
	QPushButton *btn_max;
	QPushButton *btn_min;
	QPushButton *btn_close;
private:
	static const char* styleSheet;
};


/**
 * @brief 自定义 无边框QWidget
 *
 * @note
 * 构造参数中传入 客户区窗口
 */
class XWin:public QWidget
{
	Q_OBJECT
public:
	XWin(QWidget* Client,QWidget *parent= nullptr);//Client 内部客户区
	virtual ~XWin();
	/** 设置页面属性 **/
	//设置 widget
	void setClient(QWidget* client);
	void setStyleSheet(const QString& styleSheet);
	void setTitleStyleSheet(const QString& styleSheet);

	//标题栏
	void setTitleText(const QString& text);
	void setWinIcon(const QIcon &icon);
	void setMaxIcon(const QIcon &icon);
	void setMinIcon(const QIcon &icon);
	void setCloseIcon(const QIcon &icon);
	//其他属性
	void setPadding(int padding);
	void setTitleHeight(int titleHeight);
	/** 获取部分属性 **/
	int getTitleHeight() const;
	int getPadding() const;
	/** 事件 **/
	void resizeEvent(QResizeEvent *event)override;//手动布局
	void showEvent(QShowEvent *event)override;//
	/** 事件过滤 **/
	bool eventFilter(QObject *watched, QEvent *event);//处理 鼠标拖动位置拖动大小 等事件
private:
	void onMousePressed(QMouseEvent* event);
	void onHover(QHoverEvent *event);
	unsigned short getMouseArea(const QPoint& pos);//获取鼠标所在的区域的标记 ，用于设置光标样式和  窗口被划分为9个区域 横向 3 纵向 3 res 个位标y 十位标记x .
	void setMouseCursor(const QHoverEvent *event);//设置鼠标光标
	void stretchWindow(const QHoverEvent *event);//窗口拖动改变大小
private:
	QWidget* mClient;//内部客户区
	XWinTitle* mWinTitle;//窗口标题栏
	QFrame* mFrame;
	int padding;//内边距
	int titleHeight;//标题栏高度
	int shadowSize;//阴影宽度
	QPoint oldPos;//鼠标按下时 鼠标全局位置
	QRect oldRect;//鼠标按下时 窗口位置和大小
	int mouseArea;//当鼠标按下时 鼠标所在区域 用于判定是否可以拖动大小
	bool moveEnable;//当前是否可以 拖动窗口
private:
	static const char* styleSheet;
};




#endif
