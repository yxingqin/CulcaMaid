#include "LoadFile.h"
#include <QFile>

namespace Load
{
QString loadStyle(const QString &fileName)
{
	QFile fileQss(fileName);
	fileQss.open(QFile::ReadOnly);
	QString qss=fileQss.readAll();
	fileQss.close();
	return qss;
}

}