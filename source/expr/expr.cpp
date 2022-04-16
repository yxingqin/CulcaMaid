#include "expr.h"
#include <cmath>

namespace expr
{
	constexpr double pi = 3.14159265;
	constexpr double e = 2.718281828;

	exprMeta::exprMeta(double num)
	{
		this->type = Type::NUMBER;
		this->meta.num = num;
	}
	exprMeta::exprMeta(XKey key)
	{
		this->type = Type::XKEY;
		this->meta.xkey = key;
	}
	exprMeta::exprMeta(optEnum opt)
	{
		this->type = Type::OPT;
		this->meta.opt = opt;
	}

	//判断是否为 未知数
	bool isXkey(const QString &expr, int i)
	{
		if (i >= expr.size())
			return false;
		switch (expr[i].unicode())
		{
		case u'-':
		{
			//当前一个字符为左括号 或者 位于第0个  而且后一个字符为 未知数
			if ((i == 0 || (i >= 1 && expr[i - 1] == '(')) && ++i < expr.size())
			{
				auto c = expr[i].unicode();
				return c == u'x' || c == u'y' || c == u'z' || c == u'w';
			}
			return false;
		}
		case u'x':
		case u'y':
		case u'z':
		case u'w':
			return true;
		default:
			return false;
		}
	}
	//判断是否为数值 不会移动i
	bool isNumber(const QString &expr, int i)
	{
		if (i >= expr.size())
			return false;
		switch (expr[i].unicode())
		{
		case u'-':
		{
			//当前一个字符为左括号 或者 位于第0个  而且后一个字符为数值
			return (i == 0 || (i >= 1 && expr[i - 1] == '(')) && ++i < expr.size() && expr[i].isDigit();
		}
		case u'0':
		case u'1':
		case u'2':
		case u'3':
		case u'4':
		case u'5':
		case u'6':
		case u'7':
		case u'8':
		case u'9':
		case u'p':
		case u'e':
			return true;
		default:
			return false;
		}
	}

	//得到number 会移动i
	double getNumber(const QString &expr, int &i)
	{
		int len = expr.length();
		double sign = 1; // 标记负号
		if (i < len && expr[i] == u'-')
		{
			sign = -1;
			++i;
		}
		if (i < len && expr[i] == u'p')
		{
			i += 2; // pi 移动两位
			return pi * sign;
		}
		if (i < len && expr[i] == u'e')
		{
			++i;
			return pi * e;
		}
		//处理实数
		double ret = 0;
		while (i < len && expr[i].isDigit())
		{
			ret = ret * 10 + expr[i].digitValue();
			i++;
		}
		double point = 1; //小数点
		if (i < len && expr[i] == '.')
		{
			point = 0;
			++i;
			while (i < len && expr[i].isDigit())
			{
				ret = ret * 10 + expr[i].digitValue();
				point += 10;
				i++;
			}
		}
		return ret * sign / point;
	}
	XKey getXkey(const QString &expr, int &i)
	{
		if (expr[i] == '-')
		{
			i += 2;
			switch (expr[i - 1].unicode())
			{
			case u'x':
				return XKey::nx;
			case u'y':
				return XKey::ny;
			case u'z':
				return XKey::nz;
			case u'w':
				return XKey::nw;
			default:
				return XKey::UNKNOWN;
			}
		}
		switch (expr[i++].unicode())
		{
		case u'x':
			return XKey::px;
		case u'y':
			return XKey::py;
		case u'z':
			return XKey::pz;
		case u'w':
			return XKey::pw;
		default:
			return XKey::UNKNOWN;
		}
	}

	//获取操作符 会移动i
	optEnum getOpt(const QString &expr, int &i)
	{
		auto len = expr.length();
		if (i >= len)
			return optEnum::UNKNOWN;

		switch (expr[i].unicode())
		{
		case u'+':
			++i;
			return optEnum::ADD;
		case u'-':
			++i;
			return optEnum::SUB;
		case u'×':
			++i;
			return optEnum::MUL;
		case u'÷':
			++i;
			return optEnum::DIV;
		case u'^':
			++i;
			return optEnum::POWER;
		case u'%':
			return optEnum::MOD;
		case u'(':
			++i;
			return optEnum::LEFT;
		case u')':
			++i;
			return optEnum::RIGHT;
		case u's':
		case u'c':
		case u't':
		case u'a':
		{
			if (i + 2 < len)
			{

				QString tmp = expr.mid(i, 3);
				qDebug() << tmp;
				i += 3;
				if (tmp == u"sin")
					return optEnum::SIN;
				if (tmp == u"sec")
					return optEnum::SEC;
				else if (tmp == u"cos")
					return optEnum::COS;
				else if (tmp == u"csc")
					return optEnum::CSC;
				else if (tmp == u"tan")
					return optEnum::TAN;
				else if (tmp == u"cot")
					return optEnum::COT;
				else if (tmp == u"abs")
					return optEnum::ABS;
			}
			return optEnum::UNKNOWN;
		}
		case u'l':
		{
			// lg //ln
			if (i + 1 < len)
			{
				QString tmp = expr.mid(i, 2);
				i += 2;
				if (tmp == u"ln")
					return optEnum::LN;
				else if (tmp == u"lg")
					return optEnum::LG;
			}
			return optEnum::UNKNOWN;
		}
		default:
			return optEnum::UNKNOWN;
		}
	}
	//获取优先级别
	//优先级 '(' < 加减 < 乘除 < 函数 < 指数
	int getPriority(optEnum opt)
	{
		switch (opt)
		{

		case optEnum::UNKNOWN:
		case optEnum::LEFT:
		case optEnum::RIGHT:
			return 0;
		case optEnum::ADD:
		case optEnum::SUB:
			return 1;
		case optEnum::MUL:
		case optEnum::DIV:
		case optEnum::MOD:
			return 2;
		case optEnum::POWER:
			return 4;
		case optEnum::ABS:
		case optEnum::SIN:
		case optEnum::SEC:
		case optEnum::COS:
		case optEnum::CSC:
		case optEnum::TAN:
		case optEnum::COT:
		case optEnum::LN:
		case optEnum::LG:
			return 3;
		default:
			return 0;
		}
	}

	//判断是否 为 运算函数
	inline bool isFunc(optEnum opt)
	{
		return opt > optEnum::POWER;
	}
	//检查后缀表达式 正确性 ，这里主要检查表达式的中的操作数和操作符号是否匹配
	bool checkPost(const Postfix &post)
	{

		int n = 0; //数值类型的个数
		for (auto &item : post)
		{
			if (item.isNumber())
				++n;
			else
			{
				auto opt = item.getOpt();
				if (isFunc(opt)) //取走一个 放回一个
				{
					if (n < 1)
						return false;
				}
				else if (n >= 2) //取走两个 放回一个
					--n;
				else
					return false;
			}
		}
		return n == 1;
	}

	//使栈做媒介进行转换
	bool getPostfix(const QString &expr, Postfix &ret)
	{
		if (expr.isEmpty())
			return false;
		ret.clear();

		std::vector<optEnum> stack; //符号栈
		int i = 0;
		int len = expr.length();

		while (i < len)
		{
			//数值直接进栈
			if (isXkey(expr, i))
				ret.push_back(getXkey(expr, i));
			else if (isNumber(expr, i))
				ret.push_back(getNumber(expr, i));
			else //符号进行优先级比较
			{
				int ii = i;
				auto nowOpt = getOpt(expr, i);
				if (nowOpt == optEnum::UNKNOWN)
					return false;
				if (nowOpt == optEnum::RIGHT) //如果遇到右括号，则符号栈一直pop，pop的符号push到总栈中，直到遇到左括号，消除括号
				{
					while (!stack.empty() && stack.back() != optEnum::LEFT)
					{
						ret.push_back(stack.back());
						stack.pop_back();
					}
					if (!stack.empty())
						stack.pop_back();
				}
				else if (stack.empty() || nowOpt == optEnum::LEFT || stack.back() == optEnum::LEFT) // 如果当前符号栈为空或遇到左括号或栈顶是左括号，直接入符号栈
					stack.push_back(nowOpt);
				else //比较优先级
				{
					if (getPriority(nowOpt) > getPriority(stack.back()) || (isFunc(nowOpt) && isFunc(stack.back()))) //当前运算符优先级高，或者都是栈顶和now都是fun 那么入栈
						stack.push_back(nowOpt);
					else
					{
						// 运算符小于或等于 栈顶运算符的优先级，则pop出栈顶符号，push到总栈中，回溯 i
						ret.push_back(stack.back());
						stack.pop_back();
						i = ii;
					}
				}
			}
		}
		//符号栈不为空 全部push dao ret
		while (!stack.empty())
		{
			ret.push_back(stack.back());
			stack.pop_back();
		}
		return checkPost(ret);
	}

	double optCalcul(optEnum opt, double num1, double num2) //符号计算
	{
		switch (opt)
		{
		case optEnum::ADD:
			return num1 + num2;
		case optEnum::SUB:
			return num2 - num1;
		case optEnum::MUL:
			return num2 * num1;
		case optEnum::DIV:
			return num2 / num1;
		case optEnum::MOD:
			return num2 / num1;
		case optEnum::POWER:
			return pow(num2, num1);
		default:
			return 0;
		}
	}
	double funcCalcul(optEnum opt, double num)
	{
		switch (opt)
		{
		case optEnum::ABS:
			return abs(num);
		case optEnum::SIN:
			return sin(num);
		case optEnum::SEC:
			return 1 / cos(num);
		case optEnum::COS:
			return cos(num);
		case optEnum::CSC:
			return 1 / sin(num);
		case optEnum::TAN:
			return tan(num);
		case optEnum::COT:
			return 1 / tan(num);
		case optEnum::LN:
			return log(num);
		case optEnum::LG:
			return log10(num);
		default:
			return 0;
		}
	}

	bool getResult(const Postfix &post, double &ret, double keyVal)
	{
		std::vector<double> stack;

		try //计算可能发生异常
		{
			for (auto &it : post)
			{
				if (it.getType() == exprMeta::Type::XKEY)
				{
					if (it.getXkey() >= XKey::nx)
						stack.push_back(-keyVal);
					else
						stack.push_back(keyVal);
				}
				else if (it.getType() == exprMeta::Type::NUMBER)
					stack.push_back(it.getNumber());
				else //符号
				{
					if (isFunc(it.getOpt()))
					{
						double num = stack.back();
						stack.pop_back();
						stack.push_back(funcCalcul(it.getOpt(), num));
					}
					else
					{
						double num1 = stack.back();
						stack.pop_back();
						double num2 = stack.back();
						stack.pop_back();
						stack.push_back(optCalcul(it.getOpt(), num1, num2));
					}
				}
			}
		}
		catch (...)
		{
			return false;
		}

		if (stack.size() != 1)
			return false;
		ret = stack.back();
		return true;
	}
	QDebug& operator<<(QDebug& dbg, const expr::exprMeta &meta)
	{
		switch (meta.getType())
		{
		case expr::exprMeta::Type::UNKNOWN:
			dbg << "?";
			break;
		case expr::exprMeta::Type::NUMBER:
			dbg << meta.getNumber();
			break;
		case expr::exprMeta::Type::OPT:
			switch (meta.getOpt())
			{
			case optEnum::UNKNOWN:
				dbg << "unknown";
				break;
			case optEnum::LEFT:
				dbg << "(";
				break;
			case optEnum::RIGHT:
				dbg << ")";
				break;
			case optEnum::ADD:
				dbg << "+";
				break;
			case optEnum::SUB:
				dbg << "-";
				break;
			case optEnum::MUL:
				dbg << "×";
				break;
			case optEnum::DIV:
				dbg << "÷";
				break;
			case optEnum::MOD:
				dbg << "%";
				break;
			case optEnum::POWER:
				dbg << "^";
				break;
			case optEnum::ABS:
				dbg << "abs";
				break;
			case optEnum::SIN:
				dbg << "sin";
				break;
			case optEnum::SEC:
				dbg << "sec";
				break;
			case optEnum::COS:
				dbg << "cos";
				break;
			case optEnum::CSC:
				dbg << "scs";
				break;
			case optEnum::TAN:
				dbg << "tan";
				break;
			case optEnum::COT:
				dbg << "cot";
				break;
			case optEnum::LN:
				dbg << "ln";
				break;
			case optEnum::LG:
				dbg << "lg";
				break;
			default:
				dbg << "?";
			}
			break;
		case expr::exprMeta::Type::XKEY:
			switch(meta.getXkey())
			{
				case XKey::UNKNOWN:
					dbg<<"?x";
					break;
				case XKey::px:
					dbg<<"x";
					break;
				case XKey::py:
					dbg<<"y";
					break;
				case XKey::pz:
					dbg<<"z";
					break;
				case XKey::pw:
					dbg<<"w";
					break;
				case XKey::nx:
					dbg<<"-x";
					break;
				case XKey::ny:
					dbg<<"-y";
					break;
				case XKey::nz:
					dbg<<"-z";
					break;
				case XKey::nw:
					dbg<<"-w";
					break;
			}
			break;
		default:
			dbg << "?";
		}
		return dbg;
	}

}
