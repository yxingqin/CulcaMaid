#ifndef CALCUMAID_PLOTSAMPLER_H
#define CALCUMAID_PLOTSAMPLER_H

#include <QObject>
#include "Plot.h"

class PlotSampler :public  QObject
{
	Q_OBJECT

public:
	PlotSampler(QList<Plot>* listPlot,QObject* parent= nullptr);
	signals:
	void sendPoints(int index, const QList<point> &listPoint);
public slots:
	void Sampling(double min,double max,double step);
	void Sampling(int index,double min,double max,double step);
private:
	QList<Plot>* listPlot;
};




#endif //CALCUMAID_PLOTSAMPLER_H
