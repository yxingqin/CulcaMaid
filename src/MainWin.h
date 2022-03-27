//
// Created by 24100 on 2022/3/27.
//

#ifndef CALCULMAID_MAINWIN_H
#define CALCULMAID_MAINWIN_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWin;
}
QT_END_NAMESPACE

class MainWin : public QMainWindow
{
Q_OBJECT

public:
	explicit MainWin(QWidget *parent = nullptr);
	~MainWin() override;

private:
	Ui::MainWin *ui;
};


#endif //CALCULMAID_MAINWIN_H
