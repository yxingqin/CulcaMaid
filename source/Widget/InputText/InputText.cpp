#include "InputText.h"
#include <QKeyEvent>
#include <QDebug>


InputText::InputText(QWidget *parent) : QLineEdit(parent)
{
	setAttribute(Qt::WA_InputMethodEnabled, false); //禁止中文输入法
	setFocusPolicy(Qt::StrongFocus);
	connect(this, &QLineEdit::cursorPositionChanged, this, &InputText::onCurChanged);
	numThousandFormatFlag= true;
}

void InputText::onKeyPress(QKeyEvent *event)
{
	switch (event->key())
	{
		case Qt::Key_0:
			enterNumber("0");
			break;
		case Qt::Key_1:
			enterNumber("1");
			break;
		case Qt::Key_2:
			enterNumber("2");
			break;
		case Qt::Key_3:
			enterNumber("3");
			break;
		case Qt::Key_4:
			enterNumber("4");
			break;
		case Qt::Key_5:
			enterNumber("5");
			break;
		case Qt::Key_6:
			enterNumber("6");
			break;
		case Qt::Key_7:
			enterNumber("7");
			break;
		case Qt::Key_8:
			enterNumber("8");
			break;
		case Qt::Key_9:
			enterNumber("9");
			break;

		case Qt::Key_Plus:
			enterOpt("＋");
			break;
		case Qt::Key_Minus:
			enterOpt("－");
			break;
		case Qt::Key_Slash:
			enterOpt("÷");
			break;
		case Qt::Key_Asterisk:
			enterOpt("×");
			break;
		case Qt::Key_Percent:
			enterOpt("%");
			break;
//		case Qt::Key_Enter:
//			enterEnter();
//			break;
		case Qt::Key_Period:
			enterPoint();
			break;
		case Qt::Key_ParenLeft:
			enterParenLeft();
			break;
		case Qt::Key_ParenRight:
			enterParenRight();
			break;
		case Qt::Key_Backspace:
			backspace();
			break;
		default:
			break;
	}
}

void InputText::enterNumber(const QString &t)
{
	//前一个 字符为 数值的时候 插入 乘号
	QString curText = text();
	if(cursorPosition()-1>=0&& isValue(curText[cursorPosition()-1]))
		insert("×");
	insert(t);
	curText = text();
	/**找到 当前数值的 字符串 方便后续处理**/
	int left = cursorPosition() - 1;//找到当前字串的边界
	int right = left;
	while (left > 0 && (curText[left - 1].isDigit() || curText[left - 1] == "," || curText[left - 1] == ".")) --left;
	while (right < curText.length() - 1 && (curText[right + 1].isDigit() || curText[right + 1] == ",")) ++right;
	int numLen = right - left + 1;
	QString numStr = curText.mid(left, numLen);
	//qDebug()<<"numStr"<<numStr;

	/**处理字符串**/
	if(numThousandFormatFlag)
	{
		curText.replace(left, numLen, thousandFormat(numStr));//千分位 格式化
	}

	setText(curText);
}

void InputText::enterOpt(const QString &t)
{
	/** 当前光标位置 以及 当前字符左右两边的字符 **/
	//u'＋', u'－', u'×', u'÷', u'^'
	QString curText = text();
	int curPos = cursorPosition();
	QChar cLeft(' '), cRight(' ');
	if (curPos > 0)
		cLeft = curText[curPos - 1];
	if (curPos < curText.length())
		cRight = curText[curPos];
	/**输入限制**/
	//右边一个字符 是符号的时候 取消插入
	if (isOpt(cRight))
		return;
	if (cRight == ',')
		curText.remove(curPos, 1);
	//当前输入的是 - 有可能输入的是 负号
	if (t == "－" && (cLeft == ' ' || cLeft == '('))
	{
		curText.insert(curPos, t);
		goto label_num;
	}
	//cLeft 是 运算符号的时候 替换前面一个运算符
	if (isOpt(cLeft))
	{
		curText[curPos - 1] = t[0];
		goto label_num;
	}
	//cLeft == ‘,’ 直接替换掉
	if (cLeft == ',')
	{
		curText[curPos - 1] = t[0];
		goto label_num;
	}
	//cLeft必须是数值时 或者 ‘)’ 'x' 'e' 'pi' 才能 插入
	if (cLeft.isNumber() ||isValue(cLeft))
	{
		curText.insert(curPos, t);
		goto label_num;
	}

	label_num:
	setText(curText);
}

void InputText::enterPoint()
{
	/** 当前光标位置 以及 当前字符左右两边的字符 **/
	QString curText = text();
	int curPos = cursorPosition();
	QChar cLeft(' '), cRight(' ');
	if (curPos > 0)
		cLeft = curText[curPos - 1];
	if (curPos < curText.length())
		cRight = curText[curPos];

	/** 输入限制  **/
	//检查 该数是否有有小数点 存在 取消插入
	for (int i = curPos - 1; i >= 0; --i)//左边
	{
		if (curText[i] == '.')
			return;
		if (!curText[i].isDigit() && curText[i] != ",")
			break;
	}
	for (int i = curPos - 1 > 0 ? curPos - 1 : 0; i < curText.length(); ++i)//右边
	{
		if (curText[i] == '.')
			return;
		if (!curText[i].isDigit() && curText[i] != ",")
			break;
	}
	if (cRight == ',')
		curText.remove(curPos, 1);
	//cLeft 是 空时 或者为运算符 时    自动补 0
	if (cLeft == ' ' || isOpt(cLeft))
	{
		curText.insert(curPos, "0.");
		goto label_point;
	}
	//cLeft == ‘,’ 直接替换掉
	if (cLeft == ',')
	{
		curText[curPos - 1] = '.';
		goto label_point;
	}
	//cLeft 为数值的时候 才能加入
	if (cLeft.isNumber())
	{
		curText.insert(curPos, ".");
		goto label_point;
	}
	label_point:
	setText(curText);
}

void InputText::enterClear()
{
	clear();
}


void InputText::enterBackspace()
{
	backspace();
}

void InputText::enterFunc(const QString &t)
{
	QString curText = text();
	int curPos = cursorPosition();
	QChar cLeft(' ')/*, cRight(' ')*/;
	if (curPos > 0)
		cLeft = curText[curPos - 1];
//	if (curPos < curText.length())
//		cRight = curText[curPos];

	//左边如果是 数值 x pi e 左括号 追加乘号
	if(cLeft.isNumber() ||isValue(cLeft))
	{
		curText.insert(curPos,"×"+t);
		goto label_func;
	}
//	//左边必须是运算符 空 才可以插入
//	if(cLeft==' '|| isOpt(cLeft)||cLeft=='(')
	curText.insert(curPos,t);
	label_func:
	setText(curText);
}

void InputText::enterParenLeft()
{
	QString curText = text();
	if(curText.length()>=1&& (isValue(curText[cursorPosition()-1])||curText[cursorPosition()-1].isDigit()))
		insert("×");
	insert("(");
}

void InputText::enterParenRight()
{
	QString curText = text();
	//先前查找左括号数 和右括号数 如果 右括号数 小于左括号才可以 插入
	int nLeft=0,nRight=0;
	for(auto& it:curText)
	{
		if(it=='(')
			++nLeft;
		if(it==')')
			++nRight;
	}
	if(nLeft>nRight)
		insert(")");
}


void InputText::keyPressEvent(QKeyEvent *event)
{
	onKeyPress(event);
}


QString InputText::thousandFormat(const QString &numStr)
{
	QString formatStr = numStr;

	formatStr.remove(',');
	int pointPos = formatStr.indexOf('.');
	if (pointPos == -1)
		pointPos = formatStr.length();
	if (pointPos > 3)
	{
		for (int i = 3; i < pointPos; i += 3)
		{
			formatStr.insert(pointPos - i, ',');
		}
	}

	return formatStr;
}

void InputText::onCurChanged(int oldPos, int newPos)
{
	//qDebug()<<"oldPos"<<oldPos<< "newPos" <<newPos;
}

bool InputText::isOpt(const QChar &qChar)
{
	//u'＋', u'－', u'×', u'÷', u'^'
	switch (qChar.unicode())
	{
		case u'＋':
		case u'－':
		case u'×':
		case u'÷':
		case u'^':
			return true;
	}
	return false;
}

void InputText::enterValue(const QString &t)
{
	QString curText = text();
	int curPos = cursorPosition();
	QChar cLeft(' '), cRight(' ');
	if (curPos > 0)
		cLeft = curText[curPos - 1];
	if (curPos < curText.length())
		cRight = curText[curPos];
	//如果左边为 数值  插入 乘号
	if(isValue(cLeft)|| cLeft.isDigit())
	{
		curText.insert(curPos,"×"+t);
		goto label_value;
	}
	curText.insert(curPos, t);
	//如果右边式数值的 自动补×
	if (cRight.isDigit())
		curText.insert(curPos + 1, u'×');
//	//左边 为 运算符或者 空 或者是右括号时 可以输入
//	if (cLeft == ' ' || isOpt(cLeft) || cLeft == '(')
//	{
//
//	}
	label_value:
	setText(curText);
}


bool InputText::isValue(const QChar &qChar)
{
	return  qChar == ')' || qChar == '%' || qChar == 'x' || qChar == 'e' || qChar == u'π';
}

void InputText::enterFrequentExpr1(const QString &t)
{
	QString curText = text();
	int curPos = cursorPosition();
	QChar cLeft(' '), cRight(' ');
	if (curPos > 0)
		cLeft = curText[curPos - 1];


	//前一个数是 数值类型 才可以 插入
	if(cLeft.isDigit()|| isValue(cLeft))
		insert(t);

}

void InputText::enterFrequentExpr2(const QString &t)
{
	QString curText = text();
	int curPos = cursorPosition();
	QChar cLeft(' '), cRight(' ');
	if (curPos > 0)
		cLeft = curText[curPos - 1];
	//前一个数是 数值类型  自动补充 ×
	if(cLeft.isDigit()|| isValue(cLeft))
		insert("x");
	insert(t);
}

void InputText::enableThousandFormat(bool enable)
{
	numThousandFormatFlag=enable;
}


