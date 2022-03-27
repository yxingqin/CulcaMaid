#ifndef TEMPLATE_QT_EXPR_H
#define TEMPLATE_QT_EXPR_H
/**
 * @brief 表达式处理 工具
 */
namespace expr
{
//运算符的枚举
/**
 * @brief 定义了
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
	MOD,//取模

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

//存储运算符和数据
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
