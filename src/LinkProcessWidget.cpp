// =====================================================================================
// 
//       Filename:  LinkServerWidget.cpp
//
//    Description:  服务管理标签 Widget
//
//        Version:  1.0
//        Created:  2013年08月18日 09时23分08秒
//       Revision:  none
//       Compiler:  cl
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <QtGui>

#include "LinkProcessWidget.h"
#include "ProcessTreeView.h"
#include "MainWindow.h"
#include "ControlSocket.h"

LinkProcessWidget::LinkProcessWidget(MainWindow *mainWindow)
{
	qDebug() << "LinkProcessWidget 控件初始化\r\n";
	this->mainWindow = mainWindow;
	setStyleSheet("QGroupBox {border-width:1px; border-style:solid; border-color:gray;}");
	createMainWeiget();
}

LinkProcessWidget::~LinkProcessWidget()
{

}

ProcessTreeView *LinkProcessWidget::getProcessView()
{
	return processTreeView;
}

/*================================================================
*  函 数 名： LinkProcessWidget::createMainWeiget
*
*  功能描述： 创建主显示控件
*
*  参    数： 无
*			  
*  返 回 值： 无
*
*  作    者：刘欢 2013/8
================================================================*/
void LinkProcessWidget::createMainWeiget()
{
	processLayout = new QVBoxLayout();
	processButtonLayout = new QHBoxLayout();

	processTreeView = new ProcessTreeView(mainWindow);
	getProcessButton = new QPushButton(tr("刷新进程列表"));
	connect(getProcessButton, SIGNAL(clicked()), this, SLOT(getProcessList()));
	
	killProcessButton = new QPushButton(tr("结束选中进程"));
	connect(killProcessButton, SIGNAL(clicked()), processTreeView, SLOT(removeNowSelectProcess()));

	processButtonLayout->addStretch();
	processButtonLayout->addWidget(getProcessButton);
	processButtonLayout->addStretch();
	processButtonLayout->addWidget(killProcessButton);
	processButtonLayout->addStretch();
	
	processLayout->addWidget(processTreeView);
	processLayout->addLayout(processButtonLayout);
	
	setLayout(processLayout);
}

/*================================================================
*  函 数 名： LinkProcessWidget::getProcessList
*
*  功能描述： 发送获取进程列表消息
*
*  参    数： 无
*			  
*  返 回 值： 无
*
*  作    者：刘欢 2013/8
================================================================*/
void LinkProcessWidget::getProcessList()
{
	mainWindow->getConnSocket()->sendControlCommand(GetProcessInfo);
}

/*================================================================
*  函 数 名： LinkProcessWidget::resetInfo
*
*  功能描述： 初始化界面进程信息显示
*
*  参    数： 无
*			  
*  返 回 值： 无
*
*  作    者：刘欢 2013/8
================================================================*/
void LinkProcessWidget::resetInfo()
{
	processTreeView->rebuildInfo();
}
