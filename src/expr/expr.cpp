#include "expr.h"
#include <cmath>

namespace expr
{
constexpr double pi=3.14159265;
constexpr double e=2.718281828;

exprMeta::exprMeta(double num)
{
  this->type=Type::NUMBER;
  this->meta.num=num;
}
exprMeta::exprMeta(char key)
{
	this->type=Type::XKEY;
	this->meta.xkey=key;
}
exprMeta::exprMeta(optEnum opt)
{
	this->type=Type::OPT;
	this->meta.opt=opt;
}

exprMeta::Type exprMeta::getType() const
{
	return this->type;
}

optEnum exprMeta::getOpt() const
{
	return this->meta.opt;
}

double exprMeta::getNumber() const
{
	return this->meta.num;
}

char exprMeta::getXkey() const
{
	return meta.xkey;
}

bool exprMeta::isDigit() const
{
	return type==Type::NUMBER||type==Type::XKEY;
}


//判断是否为数值 不会移动i
bool isNumber(const QString& expr,int i)
{
	if(i>=expr.size())
		return false;
	char c= expr[i].toLatin1();

	switch(c)
	{
		case '-':
			return ++i<expr.size()&&expr[i]>='0'&&expr[i]<='9';
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'p':
		case 'e':
			return true;
		default:
			return false;
	}
}
//判断是否为 未知数
bool isXkey(const QString& expr,int i)
{
	if(i>=expr.size())
		return false;
	char c=expr[i].toLatin1();
	switch (c)
	{
		case '-':
			if(++i>=expr.length())
				return false;
			c=expr[i].toLatin1();
			return c=='x'||c=='y'||c=='z'||c=='w';
		case 'x':
		case 'y':
		case 'z':
		case 'w':
			return true;
		default:
			return false;
	}
}

bool isFunc(optEnum opt)
{
	return opt>optEnum::POWER;
}

//得到number 会移动i
double getNumber(const QString& expr,int &i)
{
	int len=expr.length();
	double sign=1;// 标记负号
	if(i<len&&expr[i]=='-'){
		sign=-1;
		++i;
	}
	if(i<len&&expr[i]=='p'){
		i+=2;//pi 移动两位
		return pi*sign;
	}
	if(i<len&&expr[i]=='e'){
		++i;
		return pi*e;
	}
	//处理实数
	double ret=0;
	while (i < len && expr[i]>='0'&&expr[i]<='9')
	{
		ret = ret * 10 + expr[i].digitValue();
		i++;
	}
	double point=1;//小数点
	if(i<len&&expr[i]=='.')
	{
		point=0;
		++i;
		while (i < len && expr[i]>='0'&&expr[i]<='9')
		{
			ret = ret * 10 + expr[i].digitValue();
			point+=10;
			i++;
		}
	}
	return ret*sign/point;
}
//得到未知数 大写字母表示 负数 小写字母表示负数
char getXkey(const QString& expr,int &i)
{
	if(expr[i]=='-')
	{
		i+=2;
		return expr[i-1].toUpper().toLatin1();
	}
	return expr[i++].toLatin1();
}


//获取操作符 会移动i
optEnum getOpt(const QString& expr,int &i)
{
	auto len=expr.length();
	if(i>=len)
		return optEnum::UNKNOWN;

	switch (expr[i].toLatin1())
	{
		case '+':
			++i;
			return optEnum::ADD;
		case '-':
			++i;
			return optEnum::SUB;
		case '*':
			++i;
			return optEnum::MUL;
		case '/':
			++i;
			return optEnum::DIV;
		case '^':
			++i;
			return optEnum::POWER;
		case '%':
			return optEnum::MOD;
		case '(':
			++i;
			return optEnum::LEFT;
		case ')':
			++i;
			return optEnum::RIGHT;
		case 's':
		case 'c':
		case 't':
		case 'a':
		{
			if(i+2<len)
			{

				QString tmp=expr.mid(i,3);
				qDebug()<<tmp;
				i+=3;
				if(tmp=="sin")
					return optEnum::SIN;
				if(tmp=="sec")
					return optEnum::SEC;
				else if(tmp=="cos")
					return optEnum::COS;
				else if(tmp=="csc")
					return optEnum::CSC;
				else if(tmp=="tan")
					return optEnum::TAN;
				else if(tmp=="cot")
					return optEnum::COT;
				else if(tmp=="abs")
					return optEnum::ABS;
			}
			return optEnum::UNKNOWN;
		}
		case 'l':
		{
			//lg //ln
			if(i+1<len)
			{
				QString tmp=expr.mid(i,2);
				i+=2;
				if(tmp=="ln")
					return optEnum::LN;
				else if(tmp=="lg")
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


//检查后缀表达式 正确性 ，这里主要检查表达式的中的操作数和操作符号是否匹配
bool checkPost(const Postfix& post)
{

	int n=0;//数值类型的个数
	for(auto& item:post)
	{
		if(item.isDigit())
			++n;
		else
		{
			auto opt=item.getOpt();
			if(isFunc(opt))//取走一个 放回一个
			{
				if(n<1)
					return false;
			}else if(n>=2)//取走两个 放回一个
				--n;
			else
				return false;
		}
	}
	return true;
}


//使栈做媒介进行转换
bool getPostfix(const QString &expr, Postfix &ret)
{
	if(expr.isEmpty())
		return false;
	ret.clear();

	std::vector<optEnum> stack;//符号栈
	int i=0;
	int len=expr.length();

	while(i<len)
	{
		//数值直接进栈
		if(isXkey(expr,i))
			ret.push_back(getXkey(expr,i));
		else if(isNumber(expr,i))
			ret.push_back(getNumber(expr,i));
		else//符号进行优先级比较
		{
			int ii=i;
			auto nowOpt= getOpt(expr,i);
			if(nowOpt==optEnum::UNKNOWN)
				return false;
			if(nowOpt ==optEnum::RIGHT)//如果遇到右括号，则符号栈一直pop，pop的符号push到总栈中，直到遇到左括号，消除括号
			{
				while(!stack.empty()&&stack.back()!=optEnum::LEFT)
				{
					ret.push_back(stack.back());
					stack.pop_back();
				}
				if(!stack.empty())
					stack.pop_back();
			}else if(stack.empty()||nowOpt==optEnum::LEFT||stack.back()==optEnum::LEFT)// 如果当前符号栈为空或遇到左括号或栈顶是左括号，直接入符号栈
				stack.push_back(nowOpt);
			else//比较优先级
			{
				if(getPriority(nowOpt)>getPriority(stack.back())||(isFunc(nowOpt)&& isFunc(stack.back())) )//当前运算符优先级高，或者都是栈顶和now都是fun 那么入栈
					stack.push_back(nowOpt);
				else
				{
					// 运算符小于或等于 栈顶运算符的优先级，则pop出栈顶符号，push到总栈中，回溯 i
					ret.push_back(stack.back());
					stack.pop_back();
					i=ii;
				}
			}
		}
	}
	//符号栈不为空 全部push dao ret
	while(!stack.empty())
	{
		ret.push_back(stack.back());
		stack.pop_back();
	}
	return checkPost(ret);
}

double optCalcul(optEnum opt,double num1,double num2)//符号计算 + - * / % ^
{
	switch (opt)
	{
		case optEnum::ADD:
			return num1+num2;
		case optEnum::SUB:
			return num2-num1;
		case optEnum::MUL:
			return num2*num1;
		case optEnum::DIV:
			return num2/num1;
		case optEnum::MOD:
			return num2/num1;
		case optEnum::POWER:
			return pow(num2,num1);
		default:
			return 0;
	}
}
double funcCalcul(optEnum opt,double num)
{
	switch (opt)
	{
		case optEnum::ABS:
			return abs(num);
		case optEnum::SIN:
			return sin(num);
		case optEnum::SEC:
			return 1/cos(num);
		case optEnum::COS:
			return cos(num);
		case optEnum::CSC:
			return 1/ sin(num);
		case optEnum::TAN:
			return tan(num);
		case optEnum::COT:
			return 1/tan(num);
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

	try//计算可能发生异常
	{
		for(auto& it:post)
		{
			if(it.getType()==exprMeta::Type::XKEY)
				stack.push_back(keyVal);
			else if(it.getType()==exprMeta::Type::NUMBER)
				stack.push_back(it.getNumber());
			else//符号
			{

				if(isFunc(it.getOpt()))
				{
					double num=stack.back();
					stack.pop_back();
					stack.push_back(funcCalcul(it.getOpt(),num));
				}
				else
				{
					double num1=stack.back();
					stack.pop_back();
					double num2=stack.back();
					stack.pop_back();
					stack.push_back(optCalcul(it.getOpt(),num1,num2));
				}
			}
		}

	}catch(...)
	{
		return false;
	}

	if(stack.size()!=1)
		return false;
	ret=stack.back();
	return true;
}
QDebug operator <<(QDebug dbg,const expr::exprMeta& meta)
{
	switch (meta.getType())
	{
		case expr::exprMeta::Type::UNKNOWN:
			dbg<<"?";
			break;
		case expr::exprMeta::Type::NUMBER:
			dbg<<meta.getNumber();
			break;
		case expr::exprMeta::Type::OPT:
			switch (meta.getOpt())
			{

				case optEnum::UNKNOWN:
					dbg<<"unknown";
					break;
				case optEnum::LEFT:
					dbg<<"(";
					break;
				case optEnum::RIGHT:
					dbg<<")";
					break;
				case optEnum::ADD:
					dbg<<"+";
					break;
				case optEnum::SUB:
					dbg<<"-";
					break;
				case optEnum::MUL:
					dbg<<"*";
					break;
				case optEnum::DIV:
					dbg<<"/";
					break;
				case optEnum::MOD:
					dbg<<"%";
					break;
				case optEnum::POWER:
					dbg<<"^";
					break;
				case optEnum::ABS:
					dbg<<"abs";
					break;
				case optEnum::SIN:
					dbg<<"sin";
					break;
				case optEnum::SEC:
					dbg<<"sec";
					break;
				case optEnum::COS:
					dbg<<"cos";
					break;
				case optEnum::CSC:
					dbg<<"scs";
					break;
				case optEnum::TAN:
					dbg<<"tan";
					break;
				case optEnum::COT:
					dbg<<"cot";
					break;
				case optEnum::LN:
					dbg<<"ln";
					break;
				case optEnum::LG:
					dbg<<"lg";
					break;
			}
			break;
		case expr::exprMeta::Type::XKEY:
			dbg<<meta.getXkey();
			break;
	}
	return dbg;
}


}

