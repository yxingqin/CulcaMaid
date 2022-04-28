//
// Created by 24100 on 2022/4/5.
//

#ifndef CALCULMAID_PAGESCIENCE_H
#define CALCULMAID_PAGESCIENCE_H

#include <QFrame>
#include <QLineEdit>
#include "InputText/InputText.h"
#include "KeyBoard/ScienceKB.h"


class PageScience : public QFrame
{
Q_OBJECT

public:
	explicit PageScience(QWidget *parent = nullptr);
	~PageScience() override;
signals:
	void sendHistory(const QString& expr,const QString& result);
private:
	void initUi();
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
	ScienceKB *m_kb;
	InputText *input;
	QLineEdit *output;
};


#endif //CALCULMAID_PAGESCIENCE_H
