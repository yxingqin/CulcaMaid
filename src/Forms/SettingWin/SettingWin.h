//
// Created by 24100 on 2022/3/30.
//

#ifndef CALCULMAID_SETTINGWIN_H
#define CALCULMAID_SETTINGWIN_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui
{
class SettingWin;
}
QT_END_NAMESPACE

class SettingWin : public QWidget
{
Q_OBJECT

public:
	explicit SettingWin(QWidget *parent = nullptr);
	~SettingWin() override;

private:
	Ui::SettingWin *ui;
};


#endif //CALCULMAID_SETTINGWIN_H
