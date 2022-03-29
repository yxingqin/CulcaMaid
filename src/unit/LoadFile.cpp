#include "LoadFile.h"
#include <QFile>
#include <QApplication>
namespace Load
{
void setStyle(const QString &fileName)
{
	QFile fileQss(fileName);
	fileQss.open(QFile::ReadOnly);
	qApp->setStyleSheet(fileQss.readAll());
	fileQss.close();
}

}