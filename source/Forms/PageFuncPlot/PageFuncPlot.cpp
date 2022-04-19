#include "PageFuncPlot.h"
#include "ui_PageFuncPlot.h"

#include <QDebug>
#include <QResizeEvent>
#include <QPainter>
#include <cmath>
PageFuncPlot::PageFuncPlot(QWidget *parent)
	: QFrame(parent), ui(new Ui::PageFuncPlot), scaleFont("微软雅黑", 10, QFont::Thin, true),
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
	//白色背景
	painter.setFont(scaleFont);
	painter.setPen(Qt::white);
	painter.setBrush(Qt::white);
	painter.drawRect(rect());
	painter.setRenderHint(QPainter::SmoothPixmapTransform);
	drawGridAxis(painter);
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

	double dr = 1 + 0.1 * event->angleDelta().y() / 120;
	double maxX1 = maxX * dr;
	double minX1 = minX * dr;
	if (dr > 1 || maxX - minX > 0.01)
	{
		maxX = maxX1;
		minX = minX1;
	}
	double maxY1 = maxY * dr;
	double minY1 = minY * dr;
	if (dr > 1 || maxY - minY > 0.01)
	{
		maxY = maxY1;
		minY = minY1;
	}
	update();
	QFrame::wheelEvent(event);
}

void PageFuncPlot::drawGridAxis(QPainter &painter)
{
	painter.setPen(QPen("#c2c2c2"));
	painter.setFont(scaleFont);
	//绘制网格
	// Y 方向 间距 space 划线开始点 begin
	double rangeX = maxX - minX;
	double spaceX = pow(10, ceil(log10(rangeX)));
	spaceX = rangeX > spaceX / 2 ? spaceX / 50 : spaceX / 100;
	for (double beginX = spaceX * ceil(minX / spaceX); beginX < maxX; beginX += spaceX)
	{
		int dx = LxToDx(beginX);
		painter.drawLine(dx, 0, dx, height());
	}
	// X 方向 间距 space 划线开始点 begin
	double rangeY = maxY - minY;
	double spaceY = pow(10, ceil(log10(rangeY)));
	spaceY = rangeY > spaceY / 2 ? spaceY / 50 : spaceY / 100;
	for (double beginY = spaceY * ceil(minY / spaceY); beginY < maxY; beginY += spaceY)
	{
		int dy = LyToDy(beginY);
		painter.drawLine(0, dy, width(), dy);
	}

	//绘制 坐标轴
	painter.setPen(Qt::black);
	int Ox = LyToDy(0);
	int Oy = LxToDx(0);

	//锁定 轴的范围
	if (Ox > 0 && Ox < height())
	{
		painter.drawLine(0, Ox, width(), Ox);
		painter.drawLine(width(), Ox, width() - 5, Ox + 5);
		painter.drawLine(width(), Ox, width() - 5, Ox - 5);
	}
	if (Oy > 0 && Oy < width())
	{
		painter.drawLine(Oy, 0, Oy, height());
		painter.drawLine(Oy, 0, Oy - 5, 5);
		painter.drawLine(Oy, 0, Oy + 5, 5);
	}

	//绘制刻度
	// Y 方向
	spaceX *= 5;
	int fh = scaleFm.ascent();
	if (Ox < 0)
		Ox = fh;
	if (Ox > height())
		Ox = height() - fh;
	Ox = Ox + fh / 2;
	for (double i = ceil(minX / spaceX) * spaceX; i < maxX; i += spaceX)
	{

		QString text = abs(i) > 0.001 && (spaceX > 10000 || spaceX < 1) ? QString::number(i, 'g', 0) : QString::number(i, 'f', 0);
		// QString text = (spaceX > 100 || spaceX < 1) ? QString::number(i, 'e', 0) : QString::number(i, 'f', 0);
		text.replace("e+", "· 10^");
		int w = scaleFm.horizontalAdvance(text);
		int di = LxToDx(i) - w / 2;
		painter.setPen(Qt::white);
		painter.drawRect(di, Ox, w, -fh);
		painter.setPen(Qt::black);
		painter.drawText(di, Ox, text);
	}
	// X 方向
	spaceY *= 5;

	for (double i = ceil(minY / spaceY) * spaceY; i < maxY; i += spaceY)
	{
		if (abs(i) < 0.001)
			continue;
		QString text = (spaceY > 10000 || spaceY < 1) ? QString::number(i, 'g', 0) : QString::number(i, 'f', 0);
		text.replace("e+", "· 10^");
		int w = scaleFm.horizontalAdvance(text);
		int di = LyToDy(i);
		int y = Oy - w / 2;
		if (y < 0)
			y = 0;
		if (y > width())
			y = width() - w;
		painter.setPen(Qt::white);
		painter.drawRect(y, di, w, -fh);
		painter.setPen(Qt::black);
		painter.drawText(y, di, text);
	}
}
