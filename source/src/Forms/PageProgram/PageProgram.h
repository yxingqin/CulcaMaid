//
// Created by 24100 on 2022/4/5.
//

#ifndef CALCULMAID_PAGEPROGRAM_H
#define CALCULMAID_PAGEPROGRAM_H

#include <QFrame>


QT_BEGIN_NAMESPACE
namespace Ui
{
class PageProgram;
}
QT_END_NAMESPACE

class PageProgram : public QFrame
{
Q_OBJECT

public:
	explicit PageProgram(QWidget *parent = nullptr);
	~PageProgram() override;

private:
	Ui::PageProgram *ui;
};


#endif //CALCULMAID_PAGEPROGRAM_H
