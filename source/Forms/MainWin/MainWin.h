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
#include "PopMenu/PopMenu.h"

class MainWin : public QWidget
{
	Q_OBJECT

public:
	explicit MainWin(QWidget *parent = nullptr);
	~MainWin() override;

public:
	bool eventFilter(QObject *watched, QEvent *event) override;
	bool event(QEvent *event) override;
private slots:
	void switchMenu();
	void switchSubPage();
	/**
	 * row  ：swg_main 的索引 titile
	 */
	void switchPage(int row, QString title); //切换计算器的主页页面和子页面
											 // void switchPageCv(int row);//切换转换器的页面
private:
	void resizeEvent(QResizeEvent *event) override;
	void keyPressEvent(QKeyEvent *event)override;
private:
	Ui::MainWin *ui;
	PopMenu *mPopMenu;
	QPropertyAnimation *animationMenu;
	QPropertyAnimation *animationSub1;
};

#endif // CALCULMAID_MAINWIN_H
