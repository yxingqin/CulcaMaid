//
// Created by 24100 on 2022/3/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWin.h" resolved
#include <QDesktopWidget>
#include <QAbstractButton>
#include "MainWin.h"
#include "ui_MainWin.h"
#include <QDebug>
#include <QEvent>
MainWin::MainWin(QWidget *parent) :
		QMainWindow(parent), ui(new Ui::MainWin)
{
	ui->setupUi(this);

    QDesktopWidget *desktop = QApplication::desktop();//窗口居中
    move((desktop->width() - width())/ 2,height()/2);


	//弹出式菜单
	mPopMenu=new PopMenu(ui->centralwidget);
	mPopMenu->move(-mPopMenu->width(),0);
	ui->btn_popMune->raise();//防止被遮挡
	connect(ui->btn_popMune,&QPushButton::clicked,this,&MainWin::popMenu);
	//历史记录

}

MainWin::~MainWin()
{
	delete ui;

}

void MainWin::popMenu()//弹出菜单
{
	QPropertyAnimation *pAnimation = new QPropertyAnimation(mPopMenu, "pos",mPopMenu);
	if(mPopMenu->x()<0)
	{
		ui->btn_popMune->setStyleSheet("background-color:#FFF");
		int w=this->width()/2;
		w=w>150?150:w;
		mPopMenu->resize(w,this->height());
		pAnimation->setStartValue(QPoint(-w,0));
		pAnimation->setEndValue(QPoint(0,0));
		pAnimation->setEasingCurve(QEasingCurve::OutCurve);
		pAnimation->setDuration(150);
	}else
	{
		ui->btn_popMune->setStyleSheet("background-color:#eef4f9");
		pAnimation->setStartValue(QPoint(0,0));
		pAnimation->setEndValue(QPoint(-mPopMenu->width(),0));
		pAnimation->setEasingCurve(QEasingCurve::InQuad);
		pAnimation->setDuration(100);
	}
	pAnimation->start();
	mPopMenu->show();
}

void MainWin::resizeEvent(QResizeEvent *event)
{
	if(mPopMenu->x()>=0)//调整菜单高度
	{
		int w=this->width()/2;
		w=w>150?150:w;
		mPopMenu->resize(w,this->height());
	}

	QWidget::resizeEvent(event);
}



