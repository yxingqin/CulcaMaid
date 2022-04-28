#include <QApplication>

#include "TestWin.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	TestWin w;
	w.show();
	return QApplication::exec();
}