// =====================================================================================
// 
//       Filename:  LinkTreeWidget.cpp
//
//    Description:  自动上线主机显示
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

#include "LinkTreeWidget.h"
#include "MainStackWidget.h"
#include "LinkProcessWidget.h"
#include "LinkCmdWidget.h"
#include "FluxViewWidget.h"
#include "InfoWidget.h"
#include "MainWindow.h"
#include "ControlSocket.h"
#include "FalconType.h"

LinkTreeWidget::LinkTreeWidget(MainWindow *mainWindow)
{
	qDebug() << "LinkTreeWidget 控件初始化\r\n";

	this->mainWindow = mainWindow;
	
	this->setHeaderLabel(QString(tr("局域网主机管理")));
	this->setColumnCount(1);
	connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)),
			 this, SLOT(changeNowSelectIP(QTreeWidgetItem *)));

	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            SLOT(showContextMenu(const QPoint &)));
}

LinkTreeWidget::~LinkTreeWidget()
{

}

void LinkTreeWidget::changeNowSelectIP(QTreeWidgetItem *current)
{
	QRegExp regExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");

	// 正则表达式匹配是否选择了 IP
	if (regExp.exactMatch(current->text(0))) {
		
		strNowSelectIP = current->text(0);
		mainWindow->strNowSelectIP = strNowSelectIP;

		// 当前选择的控件编号
		int index = mainWindow->getStackWidget()->getStackLayout()->currentIndex();

		switch (index) {
			case 2:
				((FluxViewWidget *)mainWindow->getStackWidget()->getStackLayout()
									->widget(2))->showFluxInfoByIP(strNowSelectIP);
				break;
			case 3:
				((LinkProcessWidget *)mainWindow->getStackWidget()->getStackLayout()->widget(3))->resetInfo();
				mainWindow->getConnSocket()->sendControlCommand(GetProcessInfo);
				break;
			case 4:
				((LinkCmdWidget *)mainWindow->getStackWidget()->getStackLayout()->widget(4))->resetCmdInfo();
				break;
			case 5:
				((InfoWidget *)mainWindow->getStackWidget()->getStackLayout()->widget(5))->resetView();
				mainWindow->getConnSocket()->sendControlCommand(GethardInfo);
				break;
			default:
				break;
		}
	} else {
		strNowSelectIP = "";
	}
	qDebug() << "当前列表框选择的IP更新为：" << strNowSelectIP << "\r\n";
}

/*================================================================
*  函 数 名： LinkTreeWidget::addGroupItem
*
*  功能描述： 添加一个组名
*
*  参    数： QString &strTitle   组名
*			  
*			  
*  返 回 值：bool
*
*  作    者：刘欢 2013/8
================================================================*/
bool LinkTreeWidget::addGroupItem(QString strTitle)
{
	QTreeWidgetItemIterator it(this);
	while (*it) {
		if ((*it)->text(0) == strTitle) {
			return false;
		}
		++it;
	}
	QTreeWidgetItem *imageItem = new QTreeWidgetItem(this, QStringList(strTitle), 1);
	imageItem->setIcon(0, QIcon(":/res/images/group.png"));

	vectGroupName.push_back(strTitle);

	return true;
}


/*================================================================
*  函 数 名： LinkTreeWidget::delGroupItem
*
*  功能描述： 删除一个组名
*
*  参    数： QString &strTitle   组名
*			  
*			  
*  返 回 值：bool
*
*  作    者：刘欢 2013/8
================================================================*/
bool LinkTreeWidget::delGroupItem(QString strTitle)
{
	QTreeWidgetItemIterator it(this);
	while (*it) {
		if ((*it)->text(0) == strTitle) {
			QList<QTreeWidgetItem *> listChild = (*it)->takeChildren();
			for (int i = 0; i < listChild.size(); ++i) {
				moveComputerItem(listChild[i]->text(0), "默认组");
			}
			// 更新组名菜单容器
			QVector<QString>::iterator index = vectGroupName.begin();
			for (; index != vectGroupName.end(); ++index) {
				if (*index == strTitle) {
					vectGroupName.erase(index);
					break;
				}
			}
			this->removeItemWidget(*it, 1);
			delete *it;
			return false;
		}
		++it;
	}

	return false;
}

/*================================================================
*  函 数 名： LinkTreeWidget::addComputerItem
*
*  功能描述： 列表增加一个连接计算机信息
*
*  参    数： QString &strGroup —— 要添加的组名
*			  QString &strTitle —— 要添加的计算机命名
*			  bool isOnline —— 该计算机是否连接上服务端
*  返 回 值： bool —— 成功或失败
*
*  作    者：刘欢 2013/8
================================================================*/
bool LinkTreeWidget::addComputerItem(QString strGroup, QString strTitle, bool isOnline)
{
	QTreeWidgetItemIterator it(this);

	while (*it) {
		if ((*it)->text(0) == strGroup) {
				QTreeWidgetItem *item = new QTreeWidgetItem(*it, QStringList(strTitle), 2);
				if (isOnline) {
					item->setIcon(0, QIcon(":/res/images/computer_online.png"));
				} else {
					item->setIcon(0, QIcon(":/res/images/computer_offline.png"));
				}
				
				(*it)->addChild(item);
			return true;
		}
		++it;
	}

	return false;
}

/*================================================================
*  函 数 名： LinkTreeWidget::moveComputerItem
*
*  功能描述： 列表移动一个连接计算机信息
*
*  参    数： QString &strTitle —— 要添加的计算机命名
*			  QString strNewGroup —— 要移动的组名
*			  bool isOnline —— 该计算机是否连接上服务端
*  返 回 值： bool —— 成功或失败
*
*  作    者：刘欢 2013/8
================================================================*/
bool LinkTreeWidget::moveComputerItem(QString strTitle, QString strNewGroup)
{
	removeComputerItem(strTitle);
	addComputerItem(strNewGroup, strTitle, true);
	expandAll();

	return true;
}

/*================================================================
*  函 数 名： LinkTreeWidget::removeComputerItem
*
*  功能描述： 列表删除一个连接计算机信息
*
*  参    数： QString &strTitle —— 要添加的计算机命名
*			  
*  返 回 值： bool —— 成功或失败
*
*  作    者：刘欢 2013/8
================================================================*/
bool LinkTreeWidget::removeComputerItem(QString strComputer)
{
	QTreeWidgetItemIterator it(this);

	while (*it) {
		QTreeWidgetItemIterator child(it);
		while(*child) {
			if ((*child)->text(0) == strComputer) {
				this->removeItemWidget(*child, 1);
				delete *child;
				return true;
			}
			++child;
		}
		++it;
	}

	return false;
}

/*================================================================
*  函 数 名： LinkTreeWidget::showContextMenu
*
*  功能描述： 树形控件节点显示菜单
*
*  参    数： 槽函数，不显式调用
*			  
*  返 回 值： 无
*
*  作    者：刘欢 2013/8
================================================================*/
void LinkTreeWidget::showContextMenu(const QPoint &pos)
{
	QMenu menu;
	QAction *addGroup;
	QAction *delGroup;

	QMenu *menuClient;
	QAction *moveToGroup;

	QTreeWidgetItem *item = itemAt(pos);
	QVector<QString>::iterator index = vectGroupName.begin();
	if (item == NULL) {
		return;
	}
	switch (item->type()) {
		// 组名
		case 1:
			addGroup = menu.addAction(tr("增加组"));
			connect(addGroup, SIGNAL(triggered()), this, SLOT(addGroupAction()));
			delGroup = menu.addAction(tr("删除组"));
			connect(delGroup, SIGNAL(triggered()), this, SLOT(delGroupAction()));
			break;
		// 客户端IP
		case 2:
			menuClient = menu.addMenu(tr("移动至.."));
			for (; index != vectGroupName.end(); ++index) {
				moveToGroup = menuClient->addAction(*index);
			}
			connect(menuClient, SIGNAL(triggered(QAction *)), this, SLOT(moveGroupAction(QAction *)));
			break;
		default:
			return;
	}
	menu.exec(mapToGlobal(pos));
}

void LinkTreeWidget::addGroupAction()
{
	bool ok;
	QString strGroup = QInputDialog::getText(this, tr("添加分组"),
										tr("要添加的组名:"), QLineEdit::Normal, NULL, &ok);
	if (ok && !strGroup.isEmpty()) {
		addGroupItem(strGroup);
	}
}

void LinkTreeWidget::delGroupAction()
{
	if (currentItem()->text(0) == tr("默认组")) {
		QMessageBox::warning(this, tr("不允许的操作"), tr("很抱歉，默认组不允许被删除。"));
		return;
	}
	QString strQuestion = QString(tr("您确认删除分组 <font color=\"red\">%1</font> 吗？(分组成员将被移至默认组)"))
									.arg(currentItem()->text(0));
	int result = QMessageBox::question(this, tr("删除分组"),
						strQuestion, QMessageBox::Yes | QMessageBox::No);

	if (result == QMessageBox::Yes) {

		// TODO 实现移动子节点到默认组

		delGroupItem(currentItem()->text(0));
	}
}

void LinkTreeWidget::moveGroupAction(QAction *action)
{
	moveComputerItem(currentItem()->text(0), action->text());
}

