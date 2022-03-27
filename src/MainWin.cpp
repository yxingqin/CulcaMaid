//
// Created by 24100 on 2022/3/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWin.h" resolved
#include <QDesktopWidget>
#include "MainWin.h"
#include "ui_MainWin.h"


MainWin::MainWin(QWidget *parent) :
		QMainWindow(parent), ui(new Ui::MainWin)
{
	ui->setupUi(this);
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width() - width())/ 2,height()/2);//窗口居中
}

MainWin::~MainWin()
{
	delete ui;
}

