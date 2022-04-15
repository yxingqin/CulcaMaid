#include "PageFuncPlot.h"
#include "ui_PageFuncPlot.h"

#include <QDebug>
#include <QResizeEvent>
#include <QPainter>
#include <cmath>
PageFuncPlot::PageFuncPlot(QWidget *parent)
	: QFrame(parent), ui(new Ui::PageFuncPlot), scaleFont("微软雅黑", 10, QFont::Bold, true),
	  scaleFm(scaleFont)
{
	ui->setupUi(this);

	minX = minY = -10;
	maxX = maxY = 10;
}

PageFuncPlot::~PageFuncPlot()
{
	delete ui;
}

void PageFuncPlot::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setFont(scaleFont);
	painter.setPen(QPen("#f3f7fa"));
	painter.setBrush(QBrush("#f3f7fa"));
	painter.drawRect(rect());
	painter.setRenderHint(QPainter::SmoothPixmapTransform);
	drawGrid(painter);
	drawAxis(painter);
}

void PageFuncPlot::mousePressEvent(QMouseEvent *event)
{
	pressX = event->x();
	pressY = event->y();
	pminX = minX;
	pminY = minY;
	pmaxX = maxX;
	pmaxY = maxY;

	QFrame::mousePressEvent(event);
}

void PageFuncPlot::mouseMoveEvent(QMouseEvent *event)
{

	double offsetX = (pressX - event->x()) * (maxX - minX) / width();
	double offsetY = (event->y() - pressY) * (maxY - minY) / height();
	minX = pminX + offsetX;
	maxX = pmaxX + offsetX;
	minY = pminY + offsetY;
	maxY = pmaxY + offsetY;
	update();
	QFrame::mouseMoveEvent(event);
}

void PageFuncPlot::wheelEvent(QWheelEvent *event)
{
	double day = event->angleDelta().y() / 1200;
	QFrame::wheelEvent(event);
}

void PageFuncPlot::drawGrid(QPainter &painter)
{
	painter.setPen(QPen("#c2c2c2"));
	// Y 方向
	double rangeX = maxX - minX;
	//计算间距 space 划线开始点 begin
	double tmpX = pow(10, ceil(log10(rangeX)));
	double spaceX = rangeX > tmpX / 2 ? tmpX / 50 : tmpX / 100;
	double beginX = spaceX * ceil(minX / spaceX);
	for (; beginX < maxX; beginX += spaceX)
	{
		int dx = LxToDx(beginX);
		painter.drawLine(dx, 0, dx, height());

		if (static_cast<int>(beginX / spaceX) % 5 == 0)
		{
			QString str = QString::asprintf("%.0f", beginX);
			painter.drawText(dx - scaleFm.horizontalAdvance(str) / 2, height(), str);
		}
	}

	// X 方向
	double rangeY = maxY - minY;
	//计算间距 space 划线开始点 begin
	double tmpY = pow(10, ceil(log10(rangeY)));
	double spaceY = rangeX > tmpY / 2 ? tmpY / 50 : tmpY / 100;
	double beginY = spaceY * ceil(minY / spaceY);
	for (; beginY < maxY; beginY += spaceY)
	{
		int dy = LyToDy(beginY);
		painter.drawLine(0, dy, width(), dy);
		if (static_cast<int>(beginY / spaceY) % 5 == 0)
			painter.drawText(0, dy + scaleFm.ascent() / 2, QString::asprintf("%.0f", beginY));
	}
}

void PageFuncPlot::drawAxis(QPainter &painter)
{

	//绘制 坐标轴
	painter.setPen(QPen("#000"));
	int Ox = LyToDy(0);
	int Oy = LxToDx(0);
	if (Ox < height() && Ox > 0)
	{
		painter.drawLine(0, Ox, width(), Ox);
		painter.drawLine(width(), Ox, width() - 5, Ox + 5);
		painter.drawLine(width(), Ox, width() - 5, Ox - 5);
	}
	if (Oy < width() && Oy > 0)
	{
		painter.drawLine(Oy, 0, Oy, height());
		painter.drawLine(Oy, 0, Oy - 5, 5);
		painter.drawLine(Oy, 0, Oy + 5, 5);
	}
}
