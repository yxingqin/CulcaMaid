//
// Created by 24100 on 2022/4/18.
//

#ifndef CALCUMAID_EXPRESSIONBAR_H
#define CALCUMAID_EXPRESSIONBAR_H

#include <QFrame>
#include <QLineEdit>

class ExpressionBar : public QFrame
{
Q_OBJECT

public:
	explicit ExpressionBar(QWidget *parent = nullptr);
	~ExpressionBar() override;
	bool eventFilter(QObject *watched, QEvent *event) override;
public slots:
	void onKeyPress(QKeyEvent* event);
	//输入
	void enterNumber(const QString &text);
	void enterOpt(const QString &text);
	void enterPoint(const QString &text);
	void enterClear(const QString &text);
	void enterEqual(const QString &text);
	void enterBackspace(const QString &text);
	void enterFunc(const QString &text);
private:
	void initFrame();

private:
	QLineEdit *input;
	QLineEdit *output;
	int curPos;//光标位置

};


#endif //CALCUMAID_EXPRESSIONBAR_H
