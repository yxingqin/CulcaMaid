#include <QApplication>
#include <QPushButton>
#include <QDesktopWidget>
#include <XWin.h>
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
#endif
#if (QT_VERSION > QT_VERSION_CHECK(5,4,0))
	QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
#endif
#ifdef Q_OS_WIN
	QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
	QApplication a(argc, argv);
	qApp->setStyleSheet(Load::loadStyle(":/res/qss/all.qss"));
	XWin w(new MainWin());
	w.show();
	w.resize(400,620);
	w.setTitleText("计算姬");
	w.move((QApplication::desktop()->width()-w.width())/2,305);
	w.setWinIcon(QIcon(":/res/icon/calcu.png"));
	w.setMaxIcon(QIcon(":/res/icon/max.png"));
	w.setMinIcon(QIcon(":/res/icon/min.png"));
	w.setCloseIcon(QIcon(":/res/icon/close.png"));
	w.setStyleSheet("#frame {background-color:#edf5f9}");
	return QApplication::exec();
}
