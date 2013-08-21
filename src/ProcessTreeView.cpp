// =====================================================================================
// 
//       Filename:  ProcessTreeView.cpp
//
//    Description:  进程浏览显示
//
//        Version:  1.0
//        Created:  2013年08月19日 19时14分01秒
//       Revision:  none
//       Compiler:  cl
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <QtGui>

#include "ProcessTreeView.h"

ProcessTreeView::ProcessTreeView()
{
	iPosition = 0;

	mainModel = new QStandardItemModel;

	mainModel->setColumnCount(5);
	mainModel->setHeaderData(0, Qt::Horizontal, tr("映像名称"));
	mainModel->setHeaderData(1, Qt::Horizontal, tr("PID"));
	mainModel->setHeaderData(2, Qt::Horizontal, tr("内存"));
	mainModel->setHeaderData(3, Qt::Horizontal, tr("映像路径"));
	mainModel->setHeaderData(4, Qt::Horizontal, tr("描述"));

	this->setModel(mainModel);
}

ProcessTreeView::~ProcessTreeView()
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
void ProcessTreeView::rebuildInfo()
{
	mainModel->clear();
	iPosition = 0;

	mainModel->setColumnCount(5);
	mainModel->setHeaderData(0, Qt::Horizontal, tr("映像名称"));
	mainModel->setHeaderData(1, Qt::Horizontal, tr("PID"));
	mainModel->setHeaderData(2, Qt::Horizontal, tr("内存"));
	mainModel->setHeaderData(3, Qt::Horizontal, tr("映像路径"));
	mainModel->setHeaderData(4, Qt::Horizontal, tr("描述"));
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
void ProcessTreeView::addOneProcessItem(QString strProcess, QString strPID, QString strMem, 
										QString strPart, QString strDes)
{
	QStandardItem *item;

	item = new QStandardItem(QString(strProcess));
	mainModel->setItem(iPosition, 0, item);
	item = new QStandardItem(QString(strPID));
	mainModel->setItem(iPosition, 1, item);
	item = new QStandardItem(QString(strMem));
	mainModel->setItem(iPosition, 2, item);
	item = new QStandardItem(QString(strPart));
	mainModel->setItem(iPosition, 3, item);
	item = new QStandardItem(QString(strDes));
	mainModel->setItem(iPosition, 4, item);

	iPosition++;
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
QString ProcessTreeView::getStrNowProcess()
{
	return strNowProcess;
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
void ProcessTreeView::setNowSelectProcess(QModelIndex &index)
{
	strNowProcess = mainModel->data(index, 0).toString();
}