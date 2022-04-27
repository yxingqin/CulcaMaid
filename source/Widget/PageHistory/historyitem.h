//
// Created by 24100 on 2022/4/26.
//

#ifndef CALCUMAID_HISTORYITEM_H
#define CALCUMAID_HISTORYITEM_H

#include <QWidget>
#include <QLineEdit>


class HistoryItem : public QWidget
{
Q_OBJECT

public:
	explicit HistoryItem(const QString& expr,const QString& result ,QWidget *parent = nullptr);
	~HistoryItem() override;
private:
	QLineEdit *m_edt_expr;
	QLineEdit *m_edt_result;
};


#endif //CALCUMAID_HISTORYITEM_H
