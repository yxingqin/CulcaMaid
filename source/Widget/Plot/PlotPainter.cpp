#include "PlotPainter.h"

#include <QDebug>
#include <QResizeEvent>
#include <QPainter>
#include <cmath>
#include <QPainterPath>
#include <QPen>
#include <QBrush>
PlotPainter::PlotPainter(QWidget *parent)
	: QFrame(parent), scaleFont("微软雅黑", 10, QFont::Thin, true),
	  scaleFm(scaleFont)
{
	minX = minY = -10;
	maxX = maxY = 10;
	listPlot.push_back(Plot(""));

	m_thread=new QThread();
	m_thread->start();
	sampler=new PlotSampler(&listPlot, nullptr);
	sampler->moveToThread(m_thread);

	connect(this,qOverload<double,double,double>(&PlotPainter::doSampling),sampler,qOverload<double,double,double>(&PlotSampler::Sampling));
	connect(this,qOverload<int,double,double,double>(&PlotPainter::doSampling),sampler,qOverload<int,double,double,double>(&PlotSampler::Sampling));
	connect(sampler,&PlotSampler::sendPoints,this,&PlotPainter::recPoints);
	updatePlot();
}

PlotPainter::~PlotPainter()
{
	m_thread->quit();
	m_thread->wait();
	delete m_thread;
	delete sampler;
}

void PlotPainter::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	//白色背景
	painter.setFont(scaleFont);

	painter.setPen(Qt::white);
	painter.setBrush(Qt::white);
	painter.drawRect(rect());

	painter.setBrush(Qt::BrushStyle::NoBrush);
	drawGridAxis(painter);
	drawPlot(painter);
}
void PlotPainter::drawPlot(QPainter &painter)
{
	painter.setRenderHint(QPainter::Antialiasing, true);

	for(const auto& plot:listPlot)
	{
		QPainterPath path;
		if(!plot.listPoint.isEmpty())
		{
			path.moveTo(LxToDx(plot.listPoint[0].first),LyToDy(plot.listPoint[0].second));
			for(const auto&point:plot.listPoint)
			{
				path.lineTo(LxToDx(point.first),LyToDy(point.second));
			}
			painter.setPen( QPen(plot.color,plot.width,plot.style));
			painter.drawPath(path);
		}

	}
}
void PlotPainter::drawGridAxis(QPainter &painter)
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



void PlotPainter::mousePressEvent(QMouseEvent *event)
{
	pressX = event->x();
	pressY = event->y();
	pminX = minX;
	pminY = minY;
	pmaxX = maxX;
	pmaxY = maxY;
	QFrame::mousePressEvent(event);
}

void PlotPainter::mouseMoveEvent(QMouseEvent *event)
{

	double offsetX = (pressX - event->x()) * (maxX - minX) / width();
	double offsetY = (event->y() - pressY) * (maxY - minY) / height();
	minX = pminX + offsetX;
	maxX = pmaxX + offsetX;
	minY = pminY + offsetY;
	maxY = pmaxY + offsetY;
	updatePlot();
	QFrame::mouseMoveEvent(event);
}

void PlotPainter::wheelEvent(QWheelEvent *event)
{
	//滚轮缩放  x 方向
	double dx = (maxX-minX)* 0.1 * event->angleDelta().y() / 120;
	double xl=  dx * event->position().x() / width();
	double minX1=minX-xl;
	double maxX1=maxX+dx-xl;
	if (dx > 0 || maxX1 - minX1 > 0.01)
	{
		maxX = maxX1;
		minX = minX1;
	}
	//y 方向
	double dy = (maxY-minY)* 0.1 * event->angleDelta().y() / 120;
	double yt= dy*event->position().y()/height();
	double maxY1=yt+maxY;
	double minY1=minY-dy+yt;
	if (dy > 0 || maxY1 - minY1 > 0.01)
	{
		maxY = maxY1;
		minY = minY1;
	}
	updatePlot();
	QFrame::wheelEvent(event);

}

void PlotPainter::recPoints(int index, const QList<point> &listPoint)
{
	listPlot[index].listPoint=listPoint;
	update();

}

void PlotPainter::updatePlot()
{
	emit doSampling(minX,maxX,(maxX-minX)/width());
}
void PlotPainter::updatePlot(int index)
{
	emit doSampling(index,minX,maxX,(maxX-minX)/width());
}

void PlotPainter::recExpr(const QString &expr)
{
	listPlot[0].expr=expr;
	if(listPlot[0].parseExpr())
	{
		updatePlot(0);
	}
}

