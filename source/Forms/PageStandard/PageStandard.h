//
// Created by 24100 on 2022/4/4.
//

#ifndef CALCULMAID_PAGESTANDARD_H
#define CALCULMAID_PAGESTANDARD_H

#include <QWidget>
#include "ExpressionBar/ExpressionBar.h"
#include "KeyBoard/StandardKB.h"


class PageStandard : public QWidget
{
	Q_OBJECT

public:
	explicit PageStandard(QWidget *parent = nullptr);
	~PageStandard() override;
	void  onKeyPress(QKeyEvent *event);//数字输入 等按键消息
private:
	void  initUi();
private:

	ExpressionBar *fm_bar;
	StandardKB *fm_kb;
};

#endif // CALCULMAID_PAGESTANDARD_H
