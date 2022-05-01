#ifndef CALCUMAID_PLOT_H
#define CALCUMAID_PLOT_H

#include <utility>
#include <QString>
#include"expr.h"
#include "QDebug"
#include <QColor>
using point = std::pair<double, double>;
struct Plot
{
	Plot(const QString text="")
			:expr(text),color(Qt::blue),style(Qt::SolidLine),width(2)
	{
		parseExpr();
	}
	inline bool parseExpr()
	{
		expr::Postfix postfix;
		if(expr::getPostfix(expr,postfix))
		{
			post=postfix;
			return true;
		}
		qDebug()<<postfix;
		return false;
	}
	QString expr;
	QColor color;
	Qt::PenStyle style;
	int width;
	QList<point> listPoint;
	expr::Postfix post;
};

#endif //CALCUMAID_PLOT_H
