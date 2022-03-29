#include <QApplication>
#include <QPushButton>
#include "MainWin.h"
#include "unit/LoadFile.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Load::setStyle(":/res/qss/all.qss");

	MainWin w;
	w.show();

	return QApplication::exec();
}
