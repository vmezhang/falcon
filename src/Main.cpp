// =====================================================================================
// 
//       Filename:  Main.cpp
//
//    Description:  falcon 程序的主函数文件，仅 main 函数的实现
//
//        Version:  1.0
//        Created:  2013年08月18日 21时09分07秒
//       Revision:  none
//       Compiler:  cl
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <QtGui>

#include "MainWindow.h"
#include "Debug.h"

int main(int argc, char *argv[])
{
	// 注册错误日志的MsgHandler
	qInstallMsgHandler(customMessageHandler);

	// 处理中文乱码问题
	QTextCodec *codec = QTextCodec::codecForName("system");

	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);

	QApplication app(argc, argv);

	QTranslator translator_cn, translator_en;
	
	translator_cn.load(":/res/language/qt_zh_CN.qm");
	translator_en.load(":/res/language/english.qm");

	QSettings settings("falcon.ini", QSettings::IniFormat);
	
	if (settings.value("Language", true).toString() == "cn") {
		app.installTranslator(&translator_cn);
	} else {
		app.installTranslator(&translator_en);
	}

	// 添加启动logo
	QSplashScreen *splash = new QSplashScreen;

	if (settings.value("Language", true).toString() == "cn") {
		splash->setPixmap(QPixmap(":/res/images/logo.png"));
	} else {
		splash->setPixmap(QPixmap(":/res/images/logo_en.png"));
	}
	
	splash->show();
	
	qDebug() << "创建主窗口\r\n";
	MainWindow *mainwindow = new MainWindow;

	mainwindow->move((QApplication::desktop()->width() - mainwindow->width()) >> 1,
				(QApplication::desktop()->height() - mainwindow->height() - 40) >> 1);

	mainwindow->show();

	qDebug() << "显示主窗口\r\n";

	splash->finish(mainwindow);
	delete splash;

	return app.exec();
}
