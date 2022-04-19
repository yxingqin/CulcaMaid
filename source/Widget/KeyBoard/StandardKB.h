#ifndef CALCUMAID_STANDARDKB_H
#define CALCUMAID_STANDARDKB_H

#include <QFrame>
#include <QPushButton>
#include <QHash>
#include <QGridLayout>


/**
 * @brief 标准计算器的键盘
 */
class StandardKB : public QFrame
{
	Q_OBJECT
public:
	explicit StandardKB(QWidget *parent = nullptr);
	~StandardKB() override;
signals:
	void pressNum(const QString& num);				//数值  0-9
	void pressOpt(const QString &opt);		//运算符 + - x ÷
	void pressPoint();					//小数点按下
	void pressBackspace();				//退格键按下
	void pressClear();					//清空
	void pressEnter();					//等于
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
		KEY_POINT
	};
	struct btnInfo {int index;QPushButton* btn;};
	static const struct BtnDescription
	{
		QString text;	 //按钮text
		ButtonID id;	 //按钮枚举值名
		int row;		 //行
		int column;		 //列
		int rowcount;	 //所占行数
		int columncount; //所占列数
	} btnDescriptions[];

private:
signals:
	void btnPress(ButtonID);
private slots:
	void onBtnPress(ButtonID);
private:
	void initUi();
	inline QPushButton* findBtnById(ButtonID);
private:
	//按键表 用于判别发出何种信号
	QHash<ButtonID,btnInfo> btnSet;
	QGridLayout *gridLayout; //按钮们的布局
};

#endif // CALCUMAID_STANDARDKB_H
