// =====================================================================================
// 
//       Filename:  SettingDialog.cpp
//
//    Description:  设置对话框
//
//        Version:  1.0
//        Created:  2013年08月31日 22时03分50秒
//       Revision:  none
//       Compiler:  cl
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <QtGui>

#include "SettingDialog.h"

SettingDialog::SettingDialog()
{
	setupUi(this);

	setFixedSize(this->width(), this->height());

	QRegExp regExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
	editServerIP->setValidator(new QRegExpValidator(regExp, this));
	editServerIP->setMaxLength(15);

	spinServerPort->setRange(1, 65535);

	editFetionPass->setEchoMode(QLineEdit::Password);
	editFetionPass->setStyleSheet("lineedit-password-character: 42");
}

SettingDialog::~SettingDialog()
{

}

// 设置对话框选项信息
void SettingDialog::setDialogSetting(SettingInfo &setInfo)
{
	editServerIP->setText(setInfo.strServerIP);
	spinServerPort->setValue(setInfo.serverPort);

	if (setInfo.isReConn) {
		checkBoxReConn->setCheckState(Qt::Checked);
	} else {
		checkBoxReConn->setCheckState(Qt::Unchecked);
	}
	if (setInfo.isShowTrayInfo) {
		checkBoxTray->setCheckState(Qt::Checked);
	} else {
		checkBoxTray->setCheckState(Qt::Unchecked);
	}
	if (setInfo.isPlaySound) {
		checkBoxSound->setCheckState(Qt::Checked);
	} else {
		checkBoxSound->setCheckState(Qt::Unchecked);
	}
	if (setInfo.isSendPhoneMessage) {
		checkBoxSendMsg->setCheckState(Qt::Checked);
	} else {
		checkBoxSendMsg->setCheckState(Qt::Unchecked);
	}

	editFetionNumber->setText(setInfo.strFetionNumber);
	editFetionPass->setText(setInfo.strFetionPass);

	// TODO 获取黑名单信息
}

// 获取对话框选项信息
void SettingDialog::getDialogSetting(SettingInfo &setInfo)
{
	setInfo.strServerIP = editServerIP->text();
	setInfo.serverPort = spinServerPort->value();

	if (checkBoxReConn->checkState() == Qt::Checked) {
		setInfo.isReConn = true;
	} else {
		setInfo.isReConn = false;
	}
	if (checkBoxTray->checkState() == Qt::Checked) {
		setInfo.isShowTrayInfo = true;
	} else {
		setInfo.isShowTrayInfo = false;
	}
	if (checkBoxSound->checkState() == Qt::Checked) {
		setInfo.isPlaySound = true;
	} else {
		setInfo.isPlaySound = false;
	}
	if (checkBoxSendMsg->checkState() == Qt::Checked) {
		setInfo.isSendPhoneMessage = true;
	} else {
		setInfo.isSendPhoneMessage = false;
	}

	setInfo.strFetionNumber = editFetionNumber->text();
	setInfo.strFetionPass = editFetionPass->text();
}