//
// Created by 24100 on 2022/4/20.
//

#ifndef CALCUMAID_INPUTTEXT_H
#define CALCUMAID_INPUTTEXT_H
#include <QLineEdit>

class InputText:public QLineEdit
{
public:
	explicit InputText(QWidget* parent = nullptr);
	void keyPressEvent(QKeyEvent *event)override;//处理按键事件 阻止QLineEdit 的输入事件 转移到 onKeyPress 中去处理
public slots:
	void onKeyPress(QKeyEvent* event);
	//输入
	void enterNumber(const QString &t);
	void enterOpt(const QString &t);
	void enterPoint();
	void enterClear();
	void enterBackspace();
	void enterParenLeft();
	void enterParenRight();
	void enterFunc(const QString &t); //输入 函数 如 abs lg sin cos 等
	void enterValue(const QString& t);//输入特殊值 如 pi e  未知数x
	void enterFrequentExpr1(const QString& t);//输入 平凡使用的表达式
	void enterFrequentExpr2(const QString& t);//输入 平凡使用的表达式
private slots:
	void onCurChanged(int oldPos, int newPos);//光标发生变化
private:
	/**
	 * @brief 千分位格式化
	 */
	 static QString thousandFormat(const QString& numStr);
	/**
	 * @brief 判断 char 是否为 符号 + - x 等
	 */
	bool isOpt(const QChar& qChar);
	/**
	 * @brief 判断是否为 数值类型 如  x e pi  0~9 等
	 */
	bool isValue(const QChar& qChar);
private:
//	QString m_oldText;// 对输入前的字串存档
};


#endif //CALCUMAID_INPUTTEXT_H
