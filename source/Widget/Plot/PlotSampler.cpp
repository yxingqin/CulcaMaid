#include "PlotSampler.h"
void PlotSampler::Sampling(double min, double max, double step)
{
	double result=0;
	double begin;
	for(int i=0;i<listPlot->size();++i)
	{

		QList<point> ret;
		begin=min;
		while(begin<max)
		{
			if(expr::getResult(listPlot->at(i).post,result,begin))
				ret.push_back(std::make_pair(begin,result));
			begin+=step;
		}
		emit sendPoints(i,ret);
	}

}

PlotSampler::PlotSampler(QList<Plot>* listPlot,QObject *parent) : QObject(parent)
{
	this->listPlot=listPlot;
	qRegisterMetaType<QList<point>>("QList<point>");
}

void PlotSampler::Sampling(int index, double min, double max, double step)
{
	double result=0;
	QList<point> ret;
	while(min<max)
	{
		if(expr::getResult(listPlot->at(index).post,result,min))
			ret.push_back(std::make_pair(min,result));
		min+=step;
	}
	emit sendPoints(index,ret);
}
