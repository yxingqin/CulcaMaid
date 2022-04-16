#ifndef TEMPLATE_QT_EXPR_H
#define TEMPLATE_QT_EXPR_H

#include <QString>
#include <vector>
#include <QDebug>
/**
 * @brief 表达式处理 工具
 *
 * 由于QCHAR 是 UTF16编码 这里也顺势仅支持 UTF16编码
 */

namespace expr
{
	enum class optEnum;
	class exprMeta;						   //后缀表达式的基本组成单元
	using Postfix = std::vector<exprMeta>; //后缀表达式类型

	/**
	 * @brief 所有运算符的枚举
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
		MOD, //取模
		POWER,

		//一元函数
		ABS, //绝对值
		SIN,
		SEC,
		COS,
		CSC,
		TAN,
		COT,
		LN,
		LG
		//	ROOT2//平方根号
	};
	/**
	 * @brief 未知数的枚举
	 * p 正  n 负
	 */
	enum class XKey
	{
		UNKNOWN = 0,
		px,
		py,
		pz,
		pw,
		nx,
		ny,
		nz,
		nw
	};
	/**
	 * @brief 中缀变后缀
	 *
	 *  将中缀表达式（QString）转为 后缀变表达式 Vector<exprMeta>
	 *	expr 应该都为小写
	 *
	 * @param expr  表达式
	 * @param ret   处理后的后缀表达式
	 * @return false 表面表达式有误
	 */

	bool getPostfix(const QString &expr, Postfix &ret);

	/**
	 * @brief  求解含有一个未知数 的表达式
	 * @param post 后缀表达式
	 * @param ret 结果
	 * @param keyVal  未知数值  这里未知数 值的是 x
	 * @return  false 计算有误
	 */
	bool getResult(const Postfix &post, double &ret, double keyVal);
	// bool getResult(const Postfix& post,double&ret,...)//带多个未知数的

	/**
	 * @brief 后缀表达式的基本组成单元
	 *
	 * 注意 构造时写入数据，后续只读不写
	 */
	class exprMeta
	{
	public:
		enum class Type
		{
			UNKNOWN = 0,
			NUMBER,
			OPT,
			XKEY //未知数
		};

	public:
		exprMeta() = delete;
		//允许隐式类型转换
		exprMeta(optEnum opt);
		exprMeta(double num);
		exprMeta(XKey key);
		inline Type getType() const
		{
			return this->type;
		}
		inline bool isNumber() const
		{
			return type==Type::NUMBER;
		}
		inline XKey getXkey() const
		{
			return meta.xkey;
		}
		inline optEnum getOpt() const
		{
			return meta.opt;
		}
		inline double getNumber() const
		{
			return meta.num;
		}
		friend QDebug& operator<<(QDebug& dbg, const expr::exprMeta &meta);

	private:
		Type type;
		union
		{
			double num;
			optEnum opt;
			XKey xkey;
		} meta;
	};

}

#endif // TEMPLATE_QT_EXPR_H
