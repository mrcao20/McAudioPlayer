#ifndef _MC_SINGLE_APPLICATION_H_
#define _MC_SINGLE_APPLICATION_H_

#include <QGuiApplication>

QT_FORWARD_DECLARE_CLASS(QLocalServer)

class McSingleApplication : public QGuiApplication {
	Q_OBJECT

public:
	McSingleApplication(int& argc, char** argv);

	bool isRunning();                // �Ƿ��ѽ���ʵ��������
	QObject* mainWindow{ nullptr };             // MainWindowָ��

private slots:
	// ��������ʱ����
	void _newLocalConnection();

private:
	// ��ʼ����������
	void _initLocalConnection();
	// ���������
	void _newLocalServer();
	// �����
	void _activateWindow();

	bool _isRunning{ false };					// �Ƿ��ѽ���ʵ��������
	QLocalServer* _localServer{ nullptr };		// ����socket Server
	QString _serverName;						// ��������
};

#endif // !_MC_SINGLE_APPLICATION_H_