#include "expr.h"
#include <unordered_set>
namespace expr
{
constexpr double pi=3.14159265;
constexpr double e=2.718281828;

exprMeta::exprMeta(double num)
{
  this->type=Type::NUMBER;
  this->meta.num=num;
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
//判断是否为数值
bool isNumber(const std::string expr,int i)
{
	if(i>=expr.size())
		return false;
	switch(expr[i])
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
bool isXkey(const std::string& expr,int i)
{
	if(i>=expr.size())
		return false;
	switch (expr[i])
	{
		case 'x':
		case 'y':
		case 'z':
		case 'w':
			return true;
		default:
			return false;
	}
}

//得到number 会移动i
double getNumber(const std::string& expr,int &i)
{
	auto len=expr.length();
	double sign=1;//符号
	if(i<len&&expr[i]=='-'){
		sign=-1;
		++i;
	}
	if(i<len&&expr[i]=='p'){
		i+=2;
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
		ret = ret * 10 + expr[i] - '0';
		i++;
	}
	double point=1;//小数点
	if(i<len&&expr[i]=='.')
	{
		point=0;
		++i;
		while (i < len && expr[i]>='0'&&expr[i]<='9')
		{
			ret = ret * 10 + expr[i] - '0';
			point+=10;
			i++;
		}
	}
	return ret*sign/point;
}

//获取操作符 会移动i
optEnum getOpt(const std::string& expr,int &i)
{
	auto len=expr.length();
	if(i<len)
		switch (expr[i])
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
				//函数长度为2
				if(i+2<len)
				{
					std::string tmp;
					tmp.insert(tmp.begin(),expr.begin()+i,expr.begin()+i+2);
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
					else if(tmp=="COT")
						return optEnum::COT;
					else if(tmp=="abs")
						return optEnum::ABS;
				}
				return optEnum::UNKNOWN;
			}
//			case 'l':
//				i+=2;
//				if(i-1<len)
//					return expr[i-1];

		}
	return optEnum::UNKNOWN;
}

//获取优先级别
//优先级 '(' < 加减 < 乘除 < 函数 < 指数
int getPriority(optEnum opt)
{
	switch (opt)
	{
		case optEnum::ADD:
			break;
		case optEnum::UNKNOWN:
			break;
		case optEnum::SUB:
			break;
		case optEnum::MUL:
			break;
		case optEnum::DIV:
			break;
		case optEnum::SIN:
			break;
		case optEnum::POWER:
			break;
		case optEnum::COS:
			break;
		case optEnum::TAN:
			break;
		case optEnum::LN:
			break;
		case optEnum::LG:
			break;
	}
}
}

