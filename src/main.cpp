#include <QApplication>
#include <QPushButton>
#include "MainWin.h"
#include "LoadFile.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);//打开高分屏嗅探
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);//使用高分位图
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    //高分屏设置支持

	QApplication a(argc, argv);

	Load::setStyle(":/res/qss/all.qss");

	MainWin w;
	w.show();

	return QApplication::exec();
}
