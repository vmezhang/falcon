// =====================================================================================
// 
//       Filename:  FluxViewWidget.cpp
//
//    Description:  流量列表显示
//
//        Version:  1.0
//        Created:  2013年08月20日 11时08分08秒
//       Revision:  none
//       Compiler:  cl
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <QtGui>

#include "FluxViewWidget.h"
#include "FluxWidget.h"
#include "MainWindow.h"

FluxViewWidget::FluxViewWidget(MainWindow *mainWindow)
{
	qDebug() << "FluxViewWidget 控件初始化\r\n";
	setStyleSheet("QGroupBox {border-width:1px; border-style:solid; border-color:gray;}");

	this->mainWindow = mainWindow;
	
	fluxView = new FluxWidget(mainWindow);

	upLabel = new QLabel(tr("上传速度：0 KB/s"));
	downLabel = new QLabel(tr("下载速度: 0 KB/s"));
	hBoxLayout = new QHBoxLayout();

	hBoxLayout->addStretch();
	hBoxLayout->addWidget(downLabel);
	hBoxLayout->addStretch();
	hBoxLayout->addWidget(upLabel);
	hBoxLayout->addStretch();

	vBoxLayout = new QVBoxLayout();
	vBoxLayout->addWidget(fluxView);
	vBoxLayout->addLayout(hBoxLayout);
	vBoxLayout->setStretchFactor(fluxView, 1); 

	setLayout(vBoxLayout);
}

FluxViewWidget::~FluxViewWidget()
{

}

/*================================================================
*  函 数 名： FluxViewWidget::updateLabelFluxData
*
*  功能描述： 更新一次标签流量显示数据
*
*  参    数： 
*			  
*			  
*  返 回 值： 无
*
*  作    者：刘欢 2013/8
================================================================*/
void FluxViewWidget::updateLabelFluxData(double upSpeed, double downSpeed)
{
	QString strUpLabel = QString((tr("上传速度：%1 KB/s"))).arg(upSpeed);
	QString strDownLabel = QString((tr("下载速度: %1 KB/s"))).arg(downSpeed);

	upLabel->setText(strUpLabel);
	downLabel->setText(strDownLabel);
}

/*================================================================
*  函 数 名： FluxViewWidget::resetFluxView
*
*  功能描述： 重置流量控件显示
*
*  参    数： 无
*			  
*			  
*  返 回 值： 无
*
*  作    者：刘欢 2013/8
================================================================*/
void FluxViewWidget::resetFluxView()
{
	fluxView->fluxDataClear();
}

/*================================================================
*  函 数 名： FluxViewWidget::showFluxInfoByIP
*
*  功能描述： 修改显示为指定IP的流量数据
*
*  参    数： 无
*			  
*			  
*  返 回 值： 无
*
*  作    者：刘欢 2013/8
================================================================*/
void FluxViewWidget::showFluxInfoByIP(QString strIP)
{
	nowSelectIP = strIP;
	fluxView->showFluxInfoByIP(strIP);
}

/*================================================================
*  函 数 名： FluxViewWidget::addOnceSpeedByIP
*
*  功能描述： 指定IP的数据添加函数
*
*  参    数： 无
*			  
*			  
*  返 回 值： 无
*
*  作    者：刘欢 2013/8
================================================================*/
void FluxViewWidget::addOnceSpeedByIP(QString strIP, double upSpeed, double downSpeed)
{
	if (nowSelectIP == strIP) {
		updateLabelFluxData(upSpeed, downSpeed);
	}
	fluxView->addOnceSpeedByIP(strIP, upSpeed, downSpeed);
}