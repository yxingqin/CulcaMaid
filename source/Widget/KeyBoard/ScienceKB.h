#ifndef CALCUMAID_SCIENCEKB_H
#define CALCUMAID_SCIENCEKB_H


#include <QPushButton>
#include <QHash>
#include <QGridLayout>
#include <QFrame>

/**
 * @brief 弹出的键盘
 * 200x100
 */
class PopKb : public QFrame
{
	Q_OBJECT
public:
	using QFrame::QFrame;
	void popup(QPushButton* btn ,int w=120,int h=60);
	void leaveEvent(QEvent *event)override;
	signals:
	void pressFunc(const QString& t);
private:
	virtual void initUi()=0;
};
class PopKbFunc : public PopKb
{
Q_OBJECT
public:
	PopKbFunc(QWidget* parent= nullptr);
private:
	void initUi()override;
	QPushButton* btn_Log;
	QPushButton* btn_Ln;
};

class PopKbTriangle: public PopKb
{
Q_OBJECT
public:
	PopKbTriangle(QWidget* parent= nullptr);
private:
	void initUi()override;
	static QList<QString> funList;
};

/**
 * @brief 科学计算器中的键盘
 */
class ScienceKB : public QFrame
{
Q_OBJECT
public:
	explicit ScienceKB(QWidget *parent = nullptr);
	~ScienceKB() override;
	void setMode(int mode);
signals:
	void pressNum(const QString &num);    //数值  0-9
	void pressOpt(const QString &opt);    //运算符 + - x ÷
	void pressPoint();                    //小数点按下
	void pressBackspace();                //退格键按下
	void pressClear();                    //清空
	void pressEnter();                    //等于
	void pressX();
	void pressFunc(const QString &t); //输入 函数 如 abs lg sin cos 等
	void pressValue(const QString& t);//输入特殊值 如 pi e
	void pressFrequentExpr1(const QString& t);//输入 平凡使用的表达式 ^(-1) ^(1/y 等
	void pressFrequentExpr2(const QString& t);//输入 平凡使用的表达式 如 2^ 10^ 等
	void pressParenLeft();
	void pressParenRight();

private:
	enum ButtonID
	{
		KEY_CLEAR,
		KEY_BACKSPACE,
		KEY_PLUS,
		KEY_SUB,
		KEY_MULT,
		KEY_DIV,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_EQUALS,
		KEY_PERCENT,
		KEY_0,
		KEY_POINT,
		//上面两行
		KEY_PI,
		KEY_E,
		KEY_ABS,
		KEY_LEFT,
		KEY_RIGHT,
		//左边两列
		KEY_X,       //X
		KEY_X1,      //1/x
		KEY_SQR,     //x^2
		KEY_CUBE,   //x^3
		KEY_SQRROOT,   //x^(1/2)
		KEY_CUBEROOT,//x^(1/3)
		KEY_POWER,   //^
		KEY_YROOT,   //
		KEY_2N,      //2^x
		KEY_10N,     //10^x
		//弹出菜单
		KEY_TRIANGLE, //三角函数
		KEY_SIN,
		KEY_COS,
		KEY_TAN,
		KEY_FUNC,      //特殊函数 lg ln 等
	};
	struct btnInfo
	{
		int index;
		QPushButton *btn;
	};
	static const struct BtnDescription
	{
		QString text;     //按钮text
		ButtonID id;     //按钮枚举值名
		int row;         //行
		int column;         //列
		int rowcount;     //所占行数
		int columncount; //所占列数
	} btnDescriptions[];

private:
	void onBtnPress(ButtonID);
private:
	void initUi();

	inline QPushButton *findBtnById(ButtonID id)
	{
		if (btnSet.contains(id))
			return btnSet.find(id).value().btn;
		return nullptr;
	}

private:
	//按键表 用于判别发出何种信号
	QHash<ButtonID, btnInfo> btnSet;
	QGridLayout *gridLayout; //按钮们的布局

	PopKbFunc* popFunc;
	PopKbTriangle* popKbTriangle;
};




#endif // CALCUMAID_STANDARDKB_H
