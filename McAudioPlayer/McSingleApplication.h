#ifndef _MC_SINGLE_APPLICATION_H_
#define _MC_SINGLE_APPLICATION_H_

#include <QGuiApplication>

QT_FORWARD_DECLARE_CLASS(QLocalServer)

class McSingleApplication : public QGuiApplication {
	Q_OBJECT

public:
	McSingleApplication(int& argc, char** argv);

	bool isRunning();                // 是否已經有实例在运行
	QObject* mainWindow{ nullptr };             // MainWindow指针

private slots:
	// 有新连接时触发
	void _newLocalConnection();

private:
	// 初始化本地连接
	void _initLocalConnection();
	// 创建服务端
	void _newLocalServer();
	// 激活窗口
	void _activateWindow();

	bool _isRunning{ false };					// 是否已經有实例在运行
	QLocalServer* _localServer{ nullptr };		// 本地socket Server
	QString _serverName;						// 服务名称
};

#endif // !_MC_SINGLE_APPLICATION_H_