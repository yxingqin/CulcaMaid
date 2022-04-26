//
// Created by 24100 on 2022/4/26.
//

// You may need to build the project (run Qt uic code generator) to get "ui_HistoryItem.h" resolved

#include <QVBoxLayout>
#include "historyitem.h"



HistoryItem::HistoryItem(const QString &expr, const QString &result, QWidget *parent):QWidget(parent)
{
	m_edt_expr = new QLineEdit(this);
	m_edt_expr->setObjectName(QString::fromUtf8("expr"));
	m_edt_result = new QLineEdit(this);
	m_edt_result->setObjectName(QString::fromUtf8("result"));

	m_edt_expr->setText(expr);
	m_edt_result->setText("="+result);

	m_edt_result->setReadOnly(true);
	m_edt_expr->setReadOnly(true);

	//界面设置
	QVBoxLayout *verticalLayout;
	verticalLayout = new QVBoxLayout(this);
	verticalLayout->setSpacing(0);
	verticalLayout->setContentsMargins(0, 0, 0, 0);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);

	m_edt_expr->setSizePolicy(sizePolicy);
	//m_edt_expr->setMinimumSize(QSize(0, ));
	verticalLayout->addWidget(m_edt_expr);

	m_edt_result->setSizePolicy(sizePolicy);
	verticalLayout->addWidget(m_edt_result);
}

HistoryItem::~HistoryItem()
{
}

