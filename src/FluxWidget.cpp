// =====================================================================================
// 
//       Filename:  FluxWidget.cpp
//
//    Description:  流量显示
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

#include "FluxWidget.h"
#include "FalconType.h"

FluxWidget::FluxWidget()
{
	qDebug() << "FluxWidget 控件初始化\r\n";
	QFont legendFont = QFont("微软雅黑");

	this->setBackground(QBrush(QColor(52, 81, 112)));
	this->plotLayout()->insertRow(0);
	QCPPlotTitle *title= new QCPPlotTitle(this, tr("客户端流量变化图"));
	title->setTextColor(QColor("white"));
	legendFont.setPointSize(18);
	title->setFont(legendFont);
	this->plotLayout()->addElement(0, 0, title);

	this->xAxis->setRange(0, 20);
	this->yAxis->setRange(0, 15000);

	this->xAxis->setTickLabelColor(QColor("white"));
	this->xAxis->setLabelColor(QColor("white"));
	this->xAxis->setLabel("时间 / s");
	this->xAxis->setBasePen(QColor("white"));
	this->xAxis->setTickPen(QColor("white"));
	this->xAxis->setSubTickPen(QColor("white"));

	this->yAxis->setTickLabelColor(QColor("white"));
	this->yAxis->setLabelColor(QColor("white"));
	this->yAxis->setLabel("流量 / KB");
	this->yAxis->setBasePen(QColor("white"));
	this->yAxis->setTickPen(QColor("white"));
	this->yAxis->setSubTickPen(QColor("white"));

	this->legend->setVisible(true);
	legendFont.setPointSize(10);
	this->legend->setFont(legendFont);
	this->legend->setSelectedFont(legendFont);
	this->legend->setSelectableParts(QCPLegend::spItems);

	// graph(0) 下载速率
 	this->addGraph();	
	QCPScatterStyle downScatter;
	downScatter.setShape(QCPScatterStyle::ssCircle);
	downScatter.setPen(QPen(QColor(197, 238, 79)));
	downScatter.setBrush(Qt::white);
	downScatter.setSize(8);
	this->graph(0)->setScatterStyle(downScatter);
	this->graph(0)->setName(QString("上传速率"));
	QPen downPen(QColor(197, 238, 79));
	downPen.setWidth(2);
	this->graph(0)->setPen(downPen);

	// graph(1) 上传速率
	this->addGraph();
	QCPScatterStyle upScatter;
	upScatter.setShape(QCPScatterStyle::ssCircle);
	upScatter.setPen(QPen(QColor(240, 173, 7)));
	upScatter.setBrush(Qt::white);
	upScatter.setSize(8);
	this->graph(1)->setScatterStyle(upScatter);
	this->graph(1)->setName(QString("下载速率"));
	QPen upPen(QColor(240, 173, 7));
	upPen.setWidth(2);
	this->graph(1)->setPen(upPen);

	fluxPonitCount = 20;
}

FluxWidget::~FluxWidget()
{

}

// 指定IP的数据添加函数
void FluxWidget::addOnceSpeedByIP(QString strIP, double upSpeed, double downSpeed)
{
	QVector<ClientFluxInfoSave>::iterator index = vectAllClientFluxInfo.begin();

	for (; index != vectAllClientFluxInfo.end(); ++index) {
		if (index->strIP == strIP) {
			index->upLineY.remove(0);
			index->upLineY.push_back(upSpeed);
			index->downLineY.remove(0);
			index->downLineY.push_back(downSpeed);
			if (strNowSelectIP == strIP) {
				showFluxInfoByIP(strIP);
			}	
			return;
		}
	}

	// 这个客户第一次发送流量数据时创建初始数据结构
	ClientFluxInfoSave tmpFluxInfo;
	tmpFluxInfo.strIP = strIP;
	for (int i = 0; i < fluxPonitCount; ++i) {
		tmpFluxInfo.upLineX.push_back(i);
		tmpFluxInfo.downLineX.push_back(i);
		tmpFluxInfo.upLineY.push_back(0);
		tmpFluxInfo.downLineY.push_back(0);
	}

	tmpFluxInfo.upLineY.remove(0);
	tmpFluxInfo.upLineY.push_back(upSpeed);
	tmpFluxInfo.downLineY.remove(0);
	tmpFluxInfo.downLineY.push_back(downSpeed);

	vectAllClientFluxInfo.push_back(tmpFluxInfo);

	if (strNowSelectIP == strIP) {
		showFluxInfoByIP(strIP);
	}
}

// 修改显示为指定IP的流量数据
void FluxWidget::showFluxInfoByIP(QString strIP)
{
	QVector<ClientFluxInfoSave>::iterator index = vectAllClientFluxInfo.begin();

	for (; index != vectAllClientFluxInfo.end(); ++index) {
		if (index->strIP == strIP){
			this->graph(0)->setData(index->downLineX, index->downLineY);
			this->graph(1)->setData(index->upLineX, index->upLineY);
			this->replot();
			strNowSelectIP = strIP;
		}
	}
}

/*================================================================
*  函 数 名： FluxWidget::fluxDataClear
*
*  功能描述： 清空流量统计显示
*
*  参    数： 无
*			  
*  返 回 值： 无
*
*  作    者：刘欢 2013/8
================================================================*/
void FluxWidget::fluxDataClear()
{
	strNowSelectIP = "";
	this->graph(0)->clearData();
	this->graph(1)->clearData();
	this->replot();
}
