//
// Created by 24100 on 2022/4/4.
//

#ifndef CALCULMAID_PAGESTANDARD_H
#define CALCULMAID_PAGESTANDARD_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
	class PageStandard;
}
QT_END_NAMESPACE

class PageStandard : public QWidget
{
	Q_OBJECT

public:
	explicit PageStandard(QWidget *parent = nullptr);
	~PageStandard() override;
private slots:
	void btnInput();					   //按钮输入
	void on_btn_kb54_clicked();			   //等于号
	void on_btn_kb11_clicked();			   // clear
	void on_btn_kb14_clicked();			   // 退格
	void inputFilter(const QString &text); //输入过滤
private:
	void timerEvent(QTimerEvent *event) override; //维持输入焦点
	QString formatThousands(const QString &text) const;

private:
	Ui::PageStandard *ui;
};

#endif // CALCULMAID_PAGESTANDARD_H
