//
// Created by 24100 on 2022/3/27.
//

#ifndef CALCULMAID_MAINWIN_H
#define CALCULMAID_MAINWIN_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include "Forms/PopMenu/PopMenu.h"
QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWin;
}
QT_END_NAMESPACE
/**
 * @brief 主窗口
 *
 */
class MainWin : public QMainWindow
{
Q_OBJECT

public:
	explicit MainWin(QWidget *parent = nullptr);
	~MainWin() override;
private slots:
	void switchMenu();
	void switchHistory();
	void switchPageCal(int row);//切换计算器的主页页面和子页面
	//void switchPageCv(int row);//切换转换器的页面
private:
	void resizeEvent(QResizeEvent *event)override;
	bool eventFilter(QObject *watched, QEvent *event)override;
private:
	Ui::MainWin *ui;
	PopMenu* mPopMenu;
	QGraphicsDropShadowEffect* shadowEffect;
};


#endif //CALCULMAID_MAINWIN_H
