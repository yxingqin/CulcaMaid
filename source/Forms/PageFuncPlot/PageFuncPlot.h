//
// Created by 24100 on 2022/4/5.
//

#ifndef CALCULMAID_PAGEFUNCPLOT_H
#define CALCULMAID_PAGEFUNCPLOT_H
#include <QGraphicsScene>
#include <QFrame>

QT_BEGIN_NAMESPACE
namespace Ui
{
	class PageFuncPlot;
}
QT_END_NAMESPACE

class PageFuncPlot : public QFrame
{
	Q_OBJECT

public:
	explicit PageFuncPlot(QWidget *parent = nullptr);
	~PageFuncPlot() override;

private:
	//事件
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;
	//绘图
	void drawGridAxis(QPainter &painter); //绘制 网格和坐标轴
	// 设备坐标和逻辑坐标转换
	inline double DxToLx(int x) const
	{
		return minX + x * (maxX - minX) / width();
	}
	inline double DyToLy(int y) const
	{
		return minY + (height() - y) * (maxY - minY) / height();
	}
	inline int LxToDx(double x) const
	{
		return static_cast<int>(((x - minX) * width() / (maxX - minX)));
	}
	inline int LyToDy(double y) const
	{
		return static_cast<int>(height() + ((minY - y) * height() / (maxY - minY)));
	}

private:
	Ui::PageFuncPlot *ui;

	//绘图相关
	double minX, maxX, minY, maxY; //显示范围

	//操纵相关
	int pressX, pressY;				   //鼠标按下时的位置
	double pminX, pmaxX, pminY, pmaxY; //鼠标按下时 显示的范围
	QFont scaleFont;
	QFontMetrics scaleFm;
};

#endif // CALCULMAID_PAGEFUNCPLOT_H
