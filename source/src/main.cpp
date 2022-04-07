#include <QApplication>
#include <QPushButton>
#include "MainWin.h"
#include "LoadFile.h"
int main(int argc, char *argv[])
{
	//高分屏 设置
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);
#endif
#if (QT_VERSION > QT_VERSION_CHECK(5,6,0))
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
	QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
#if (QT_VERSION > QT_VERSION_CHECK(5,4,0))
	QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
#endif

	QApplication a(argc, argv);

	Load::setStyle(":/res/qss/all.qss");

	MainWin w;
	w.show();

	return QApplication::exec();
}
