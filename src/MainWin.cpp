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
	mPopMenu->show();
	mPopMenu->stackUnder(ui->btn_popMune);
	mPopMenu->hide();
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
		int x=ui->btn_popMune->x();
		int y=ui->btn_popMune->y();
		mPopMenu->move(x,y);
		mPopMenu->show();
		ui->btn_popMune->activateWindow();


	}else
		mPopMenu->hide();
}

