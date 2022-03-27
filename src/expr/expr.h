#ifndef TEMPLATE_QT_EXPR_H
#define TEMPLATE_QT_EXPR_H
/**
 * @brief 表达式处理
 *
 *
 */
namespace expr
{
//运算符的枚举
/**
 * @brief 运算符枚举
 */
enum class optEnum
{
	UNKNOWN = 0,
	//括号
	LEFT,
	RIGHT,
	//二元运算符
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	POWER,
	//一元函数
	ABS,//绝对值
	SIN,
	SEC,
	COS,
	CSC,
	TAN,
	COT,
	LN,
	LG,
	SQUARE,//平方
	SQUAREROOT,
};

/**
 * @brief 后缀表达式的基本组成单元
 *
 * 存储信息： 数据类型 如 未知数，运算符，数值
 * 可读不可写
 */
class exprMeta
{
public:
	enum class Type
	{
		UNKNOWN = 0,
		NUMBER,
		OPT,
		XKEY//未知数
	};
public:
	exprMeta() = delete;
	exprMeta(optEnum opt);
	exprMeta(double num);
	Type getType() const;
	char getXkey()const;
	optEnum getOpt() const;
	double getNumber() const;
private:
	Type type;
	union
	{
		double num;
		optEnum opt;
		char xkey;
	} meta;
};
}


#endif //TEMPLATE_QT_EXPR_H
