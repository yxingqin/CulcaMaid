//
// Created by 24100 on 2022/3/27.
//

#ifndef CALCULMAID_MAINWIN_H
#define CALCULMAID_MAINWIN_H

#include <QMainWindow>
#include <QPropertyAnimation>
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
private:
	void popMenu();
	void resizeEvent(QResizeEvent *event)override;
private:
	Ui::MainWin *ui;
	PopMenu* mPopMenu;
};


#endif //CALCULMAID_MAINWIN_H
