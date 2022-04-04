//
// Created by 24100 on 2022/3/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWin.h" resolved
#include <QDesktopWidget>
#include <QAbstractButton>
#include "MainWin.h"
#include <QDebug>
#include <QResizeEvent>
#include "ui_MainWin.h"


MainWin::MainWin(QWidget *parent) :
		QMainWindow(parent), ui(new Ui::MainWin)
{
	ui->setupUi(this);

    QDesktopWidget *desktop = QApplication::desktop();//窗口居中
	this->setGeometry((desktop->width() - width())/ 2,height()/2,420,610);

	//弹出式菜单
	mPopMenu=new PopMenu(ui->centralwidget);
	mPopMenu->move(-mPopMenu->width(),0);
	ui->btn_popMune->raise();//防止被遮挡
	connect(ui->btn_popMune,&QPushButton::clicked,this,&MainWin::popMenu);
	//历史记录
	ui->swdg_sub->hide();
	ui->page_sub1->hide();
	connect(ui->btn_history,&QPushButton::clicked,this,&MainWin::popHistory);


	connect(mPopMenu->list_culca,&QListWidget::currentRowChanged,this,[this](int row){

		ui->swdg_main->setCurrentIndex(row);
		popMenu();
	});

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
		int w=this->width()/2;
		w=w>256?256:w;
		mPopMenu->resize(w,this->height());
		pAnimation->setStartValue(QPoint(-w,0));
		pAnimation->setEndValue(QPoint(0,0));
		pAnimation->setEasingCurve(QEasingCurve::OutCurve);
		pAnimation->setDuration(150);
	}else
	{
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
	auto size=event->size();

	if(mPopMenu->x()>=0)//调整菜单高度
	{
		int w=this->width()/2;
		w=w>256?256:w;
		mPopMenu->resize(w,this->height());
	}
	//280+380 显示history
	if(size.width()>=660)
	{
		ui->btn_history->hide();
		ui->page_sub1->setParent(ui->swdg_sub);
		ui->page_sub1->setGeometry(0,0, 280,this->height());
		ui->page_sub1->show();
		ui->swdg_sub->show();
	}
	else
	{
		ui->btn_history->show();
		ui->swdg_sub->hide();
		ui->page_sub1->hide();
	}
	QWidget::resizeEvent(event);
}

void MainWin::popHistory()
{
	if(this->width()<660)
	{
		if(ui->page_sub1->isHidden())
		{
			ui->page_sub1->setParent(this);
			ui->page_sub1->setGeometry(0,this->height()/2, this->width(),this->height()/2);
			ui->page_sub1->show();
		}
		else
			ui->page_sub1->hide();
	}
}



