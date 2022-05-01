//
// Created by 24100 on 2022/4/29.
//

#ifndef CALCUMAID_PLOTEDIT_H
#define CALCUMAID_PLOTEDIT_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "InputText/InputText.h"



class PlotEdit : public QWidget
{
Q_OBJECT

public:
	explicit PlotEdit(QWidget *parent = nullptr);
	~PlotEdit() override;
	void setExpr(const QString& expr);
	QString getExpr()const;
private:
	void initUi();
private:

	QLabel *label;
	InputText *lineEdit;
};


#endif //CALCUMAID_PLOTEDIT_H
