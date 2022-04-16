//
// Created by 24100 on 2022/4/5.
//

#ifndef CALCULMAID_PAGEHISTORY_H
#define CALCULMAID_PAGEHISTORY_H

#include <QFrame>


QT_BEGIN_NAMESPACE
namespace Ui
{
class PageHistory;
}
QT_END_NAMESPACE

class PageHistory : public QFrame
{
Q_OBJECT

public:
	explicit PageHistory(QWidget *parent = nullptr);
	~PageHistory() override;
public slots:
	void addHistory(const QString& expr,const QString& result);
private:
	Ui::PageHistory *ui;
};


#endif //CALCULMAID_PAGEHISTORY_H
