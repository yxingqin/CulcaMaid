//
// Created by 24100 on 2022/3/29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PopMenuItem.h" resolved

#include "PopMenuItem.h"
#include "ui_PopMenuItem.h"


PopMenuItem::PopMenuItem(QWidget *parent,QString title,QString ico) :
		QWidget(parent), ui(new Ui::PopMenuItem)
{
	ui->setupUi(this);
	ui->lbl_title->setText(title);

	QPixmap pixmap(ico);
	pixmap.scaled(ui->lbl_icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	ui->lbl_icon->setScaledContents(true);
	ui->lbl_icon->setPixmap(pixmap);
}

PopMenuItem::~PopMenuItem()
{
	delete ui;
}

