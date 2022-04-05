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
	void mouseReleaseEvent(QMouseEvent *event);
	bool eventFilter(QObject *watched, QEvent *event) override;
private slots:
	void switchMenu();
	void switchSubPage();
	void switchPageCal(int row);//切换计算器的主页页面和子页面
	//void switchPageCv(int row);//切换转换器的页面
private:
	void resizeEvent(QResizeEvent *event)override;
private:
	Ui::MainWin *ui;
	QPoint mouseRPos;//鼠标相对位置窗口左上角 用于拖动窗口
	bool canMove;
	PopMenu *mPopMenu;
	QPropertyAnimation *animationMenu;
	QPropertyAnimation *animationSub1;
};


#endif //CALCULMAID_MAINWIN_H
