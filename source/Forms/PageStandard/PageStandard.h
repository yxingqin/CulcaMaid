//
// Created by 24100 on 2022/4/4.
//

#ifndef CALCULMAID_PAGESTANDARD_H
#define CALCULMAID_PAGESTANDARD_H

#include <QWidget>
#include "KeyBoard/StandardKB.h"
#include <QLineEdit>
#include <InputText/InputText.h>

class PageStandard : public QWidget
{
	Q_OBJECT

public:
	explicit PageStandard(QWidget *parent = nullptr);
	~PageStandard() override;
	void  onKeyPress(QKeyEvent *event);//数字输入 等按键消息
signals:
	void sendHistory(const QString& expr,const QString& result);
private:
	void  initUi();
private slots:

	/**
	 * @brief 输入字符发生变化时触发
	 * 尝试计算，将结果显示到 output中
	 */
	void onInputTextChanged();
	/**
	 * @brief 当按下等于号时
	 */
	void onEnter();
private:
	StandardKB *fm_kb;
	InputText *input;
	QLineEdit *output;
};

#endif // CALCULMAID_PAGESTANDARD_H
