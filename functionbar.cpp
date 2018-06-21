﻿#include "functionbar.h"
#include "ui_functionbar.h"
#include "goopal.h"
#include "commondialog.h"
#include "debug_log.h"
#include "datamgr.h"
#include "extra/dynamicmove.h"

#include <QPainter>
#include <QDebug>


FunctionBar::FunctionBar(QWidget *parent) :
QWidget(parent),
ui(new Ui::FunctionBar)
{
    DLOG_QT_WALLET_FUNCTION_BEGIN;
	ui->setupUi(this);
	setAutoFillBackground(true);

	ui->homeBtn->setPixmap(DataMgr::getDataMgr()->getWorkPath() + "pic2/home_btn.png");
	ui->homeBtn->setBtnText(tr("Home"));

	ui->billBtn->setPixmap(DataMgr::getDataMgr()->getWorkPath() + "pic2/ledger_btn.png");
	ui->billBtn->setBtnText(tr("Ledger"));

	ui->transferBtn->setPixmap(DataMgr::getDataMgr()->getWorkPath() + "pic2/transfer_btn.png");
	ui->transferBtn->setBtnText(tr("Transfer"));

	ui->accountBtn->setPixmap(DataMgr::getDataMgr()->getWorkPath() + "pic2/account_btn.png");
	ui->accountBtn->setBtnText(tr("Account"));

	ui->quotationBtn->setPixmap(DataMgr::getDataMgr()->getWorkPath() + "pic2/markets_btn.png");
	ui->quotationBtn->setBtnText(tr("Markets"));

    choosePage(0);

	ui->versionLabel->setText(ACHAIN_WALLET_VERSION_STR);

    DLOG_QT_WALLET_FUNCTION_END;
}

FunctionBar::~FunctionBar()
{
    delete ui;
}

void FunctionBar::retranslator()
{
	ui->retranslateUi(this);

	ui->homeBtn->setBtnText(tr("Home"));
	ui->billBtn->setBtnText(tr("Ledger"));
	ui->transferBtn->setBtnText(tr("Transfer"));
	ui->accountBtn->setBtnText(tr("Account"));
	ui->quotationBtn->setBtnText(tr("Markets"));

	ui->versionLabel->setText(ACHAIN_WALLET_VERSION_STR);
}

void FunctionBar::on_homeBtn_clicked()
{
	choosePage(0);
	emit showHomePage();
}

void FunctionBar::on_billBtn_clicked()
{
	int size = DataMgr::getInstance()->getAccountInfo()->size();

	if (size != 0)   {
		// 有至少一个账户
		choosePage(1);
		const QString& accountName = DataMgr::getInstance()->getCurrentAccount();
		emit showBillPage(accountName);
	}
	else {
		CommonDialog commonDialog(CommonDialog::OkOnly);
		commonDialog.setText(tr("You have no accounts,\nadd an account first"));
		commonDialog.pop();
		on_accountBtn_clicked();
	}
}

void FunctionBar::on_transferBtn_clicked()
{
	int size = DataMgr::getInstance()->getAccountInfo()->size();

	if (size > 0) {
		choosePage(2);
		emit showTransferPage();
	}
	else {
		CommonDialog commonDialog(CommonDialog::OkOnly);
		commonDialog.setText(tr("No accounts for transfering,\nadd an account first"));
		commonDialog.pop();
		on_accountBtn_clicked();
	}
}

void FunctionBar::on_accountBtn_clicked()
{
	choosePage(3);
	emit showAccountPage();
}

void FunctionBar::on_quotationBtn_clicked()
{
	choosePage(4);
	emit showQuotationPage();
}

void FunctionBar::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	painter.setBrush(QColor(255, 255, 255));
	painter.setPen(QPen(QColor(187, 187, 187), 2));
	painter.drawRect(QRect(0, 0, 136, 532));
}

void FunctionBar::choosePage(int pageIndex)
{
    switch (pageIndex) {
    case 0:
		ui->homeBtn->setSelected(true);
		ui->billBtn->setSelected(false);
		ui->transferBtn->setSelected(false);
		ui->accountBtn->setSelected(false);
		ui->quotationBtn->setSelected(false);
        break;

	case 1:
		ui->homeBtn->setSelected(false);
		ui->billBtn->setSelected(true);
		ui->transferBtn->setSelected(false);
		ui->accountBtn->setSelected(false);
		ui->quotationBtn->setSelected(false);
        break;

	case 2:
		ui->homeBtn->setSelected(false);
		ui->billBtn->setSelected(false);
		ui->transferBtn->setSelected(true);
		ui->accountBtn->setSelected(false);
		ui->quotationBtn->setSelected(false);
        break;

	case 3:
		ui->homeBtn->setSelected(false);
		ui->billBtn->setSelected(false);
		ui->transferBtn->setSelected(false);
		ui->accountBtn->setSelected(true);
		ui->quotationBtn->setSelected(false);
        break;

	case 4:
		ui->homeBtn->setSelected(false);
		ui->billBtn->setSelected(false);
		ui->transferBtn->setSelected(false);
		ui->accountBtn->setSelected(false);
		ui->quotationBtn->setSelected(true);
        break;

    default:
        break;
    }
}