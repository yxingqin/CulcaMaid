//
// Created by 24100 on 2022/4/5.
//

#ifndef CALCULMAID_PAGEFUNCPLOT_H
#define CALCULMAID_PAGEFUNCPLOT_H

#include <QFrame>
#include <QStyle>
#include <QThread>
#include "Plot.h"
#include "PlotSampler.h"


class PlotPainter : public QFrame
{
Q_OBJECT
public:
	explicit PlotPainter(QWidget *parent = nullptr);
	~PlotPainter() override;

	inline int plotCount()const
	{
		return listPlot.size();
	}
	inline const QString& getPlotExprAt(int index)const
	{
		return listPlot.at(index).expr;
	}
	inline void setPlotExprAt(int index,const QString& expr)
	{
		listPlot[index].expr=expr;
		if(listPlot[index].parseExpr())
			updatePlot(index);
	}


	signals:
	void doSampling(double min,double max,double step);
	void doSampling(int index,double min,double max,double step);
public slots:
	void recPoints(int index, const QList<point> &listPoint);
	void recExpr(const QString& expr);
private:
	//事件
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;
	//绘图
	void drawGridAxis(QPainter &painter); //绘制 网格和坐标轴
	void drawPlot(QPainter &painter);
	void updatePlot();
	void updatePlot(int index);
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

	//绘图相关
	double minX, maxX, minY, maxY; //显示范围
	//操纵相关
	int pressX{}, pressY{};                   //鼠标按下时的位置
	double pminX{}, pmaxX{}, pminY{}, pmaxY{}; //鼠标按下时 显示的范围
	QFont scaleFont;
	QFontMetrics scaleFm;

	//曲线的数据
	QList<Plot> listPlot;
	QThread* m_thread;
	PlotSampler* sampler;
};

#endif // CALCULMAID_PAGEFUNCPLOT_H
