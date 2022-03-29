#include "LoadFile.h"
#include <QFile>
#include <QApplication>
namespace Load
{
void setStyle(const QString &fileName)
{
	qApp->setStyleSheet(loadStyle(fileName));
}

QString loadStyle(const QString &fileName)
{
	QFile fileQss(fileName);
	fileQss.open(QFile::ReadOnly);
	QString qss=  fileQss.readAll();
	fileQss.close();
	return qss;
}

}