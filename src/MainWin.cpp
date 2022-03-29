//
// Created by 24100 on 2022/3/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWin.h" resolved
#include <QDesktopWidget>
#include <QAbstractButton>
#include "MainWin.h"
#include "ui_MainWin.h"
#include <QDebug>

MainWin::MainWin(QWidget *parent) :
		QMainWindow(parent), ui(new Ui::MainWin)
{
	ui->setupUi(this);

    QDesktopWidget *desktop = QApplication::desktop();//窗口居中
    move((desktop->width() - width())/ 2,height()/2);

	//弹出式菜单
	mPopMenu=new PopMenu(ui->centralwidget);
	mPopMenu->hide();
	ui->btn_popMune->raise();//防止被遮挡
	connect(ui->btn_popMune,&QPushButton::clicked,this,&MainWin::popMenu);
}

MainWin::~MainWin()
{
	delete ui;
}
//弹出菜单 位于 菜单按钮之上
void MainWin::popMenu()
{
	if(mPopMenu->isHidden())
	{
		mPopMenu->resize(this->width()/2,this->height());
		mPopMenu->move(0,0);
		mPopMenu->show();
		ui->btn_popMune->setStyleSheet("background-color:#FFF");
	}else
	{
		mPopMenu->hide();
		ui->btn_popMune->setStyleSheet("background-color:#eef4f9");
	}

}

