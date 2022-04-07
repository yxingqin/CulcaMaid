//
// Created by 24100 on 2022/4/5.
//

#ifndef CALCULMAID_MAINWIN_H
#define CALCULMAID_MAINWIN_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWin;
}
QT_END_NAMESPACE
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QPoint>
#include "Forms/PopMenu/PopMenu.h"


class MainWin : public QWidget
{
Q_OBJECT

public:
	explicit MainWin(QWidget *parent = nullptr);
	~MainWin() override;
public:
	void mouseMoveEvent(QMouseEvent *event)override;
	void mousePressEvent(QMouseEvent *event)override;
	void mouseReleaseEvent(QMouseEvent *event)override;
	void mouseDoubleClickEvent(QMouseEvent *event)override;
	bool eventFilter(QObject *watched, QEvent *event) override;
	bool event(QEvent *event)override;
	void paintEvent(QPaintEvent *event)override;
private slots:
	void switchMenu();
	void switchSubPage();
	void switchPageCal(int row);//切换计算器的主页页面和子页面
	//void switchPageCv(int row);//切换转换器的页面
private:
	void resizeEvent(QResizeEvent *event)override;
	int getPosArea(const QPoint& point);//返回 11 12 13 .... 33 标记 鼠标所在区域
	void stretch(const QPoint& point);//拉伸 窗口,返回是否拉伸了窗口 如果拉伸的窗口 取消拖动窗口
private:
	Ui::MainWin *ui;
	QPoint mouseRPos;//鼠标相对位置窗口左上角 用于拖动窗口
	bool canMove;//可以拖动
	PopMenu *mPopMenu;
	QPropertyAnimation *animationMenu;
	QPropertyAnimation *animationSub1;
};


#endif //CALCULMAID_MAINWIN_H
