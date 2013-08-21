// =====================================================================================
// 
//       Filename:  MainStackWidget.cpp
//
//    Description:  标签显示管理
//
//        Version:  1.0
//        Created:  2013年08月18日 14时05分08秒
//       Revision:  none
//       Compiler:  cl
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <QtGui>

#include "MainStackWidget.h"
#include "MainListWidget.h"
#include "LinkProcessWidget.h"
#include "LinkControlWidget.h"
#include "LinkCmdWidget.h"
#include "ScreenViewWidget.h"
#include "FluxViewWidget.h"

MainStackWidget::MainStackWidget()
{
	createMainWeiget();
	setLayout(stackedLayout);
}

MainStackWidget::~MainStackWidget()
{

}

/*================================================================
*  函 数 名： 
*
*  功能描述： 
*
*  参    数： 
*			  
*			  
*  返 回 值：
*
*  作    者：刘欢 2013/8
================================================================*/
void MainStackWidget::createMainWeiget()
{
	stackedLayout = new QStackedLayout(this);
	stackedLayout->setStackingMode(QStackedLayout::StackOne);

	mainListWidget = new MainListWidget();
	screenViewWidget = new ScreenViewWidget();
	fluxViewWidget = new FluxViewWidget();
	linkProcessWidget = new LinkProcessWidget();
	linkControlWidget = new LinkControlWidget();
	linkCmdWidget = new LinkCmdWidget();

	stackedLayout->addWidget(mainListWidget);
	stackedLayout->addWidget(screenViewWidget);
	stackedLayout->addWidget(fluxViewWidget);
	stackedLayout->addWidget(linkProcessWidget);
	stackedLayout->addWidget(linkControlWidget);
	stackedLayout->addWidget(linkCmdWidget);
}

/*================================================================
*  函 数 名： 
*
*  功能描述： 
*
*  参    数： 
*			  
*			  
*  返 回 值：
*
*  作    者：刘欢 2013/8
================================================================*/
QStackedLayout *MainStackWidget::getStackLayout()
{
	return stackedLayout;
}