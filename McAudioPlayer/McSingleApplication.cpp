#include "McSingleApplication.h"

#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>
#include <QFileInfo>

#define TIME_OUT                (500)    // 500ms

McSingleApplication::McSingleApplication(int& argc, char** argv)
	: QGuiApplication(argc, argv)
{
#ifndef QT_DEBUG
	// ȡӦ�ó�������ΪLocalServer������
	_serverName = QFileInfo(QCoreApplication::applicationFilePath()).fileName();

	_initLocalConnection();
#endif // !_DEBUG
}

////////////////////////////////////////////////////////////////////////////////
// ˵����
// ����Ƿ��ѽ���һ��ʵ��������, true - ��ʵ�����У� false - û��ʵ������
////////////////////////////////////////////////////////////////////////////////
bool McSingleApplication::isRunning() {
	return _isRunning;
}

////////////////////////////////////////////////////////////////////////////////
// ˵����
// ͨ��socketͨѶʵ�ֳ���ʵ�����У��������µ�����ʱ�����ú���
////////////////////////////////////////////////////////////////////////////////
void McSingleApplication::_newLocalConnection() {
	QLocalSocket* socket = _localServer->nextPendingConnection();
	if (socket) {
		socket->waitForReadyRead(2 * TIME_OUT);
		delete socket;

		// ���������磺��ȡ��������

		_activateWindow();
	}
}

////////////////////////////////////////////////////////////////////////////////
// ˵����
// ͨ��socketͨѶʵ�ֳ���ʵ�����У�
// ��ʼ���������ӣ�������Ӳ���server���򴴽��������˳�
////////////////////////////////////////////////////////////////////////////////
void McSingleApplication::_initLocalConnection() {
	_isRunning = false;

	QLocalSocket socket;
	socket.connectToServer(_serverName);
	if (socket.waitForConnected(TIME_OUT)) {
		fprintf(stderr, "%s already running.\n",
			_serverName.toLocal8Bit().constData());
		_isRunning = true;
		// ���������磺�������������͵������
		return;
	}

	//���Ӳ��Ϸ��������ʹ���һ��
	_newLocalServer();
}

////////////////////////////////////////////////////////////////////////////////
// ˵����
// ����LocalServer
////////////////////////////////////////////////////////////////////////////////
void McSingleApplication::_newLocalServer() {
	_localServer = new QLocalServer(this);
	connect(_localServer, SIGNAL(newConnection()), this, SLOT(_newLocalConnection()));
	if (!_localServer->listen(_serverName)) {
		// ��ʱ����ʧ�ܣ������ǳ������ʱ,�������̷����µ�,�Ƴ�֮
		if (_localServer->serverError() == QAbstractSocket::AddressInUseError) {
			QLocalServer::removeServer(_serverName); // <-- �ص�
			_localServer->listen(_serverName); // �ٴμ���
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// ˵����
// ����������
////////////////////////////////////////////////////////////////////////////////
void McSingleApplication::_activateWindow() {
	if (mainWindow)
		QMetaObject::invokeMethod(mainWindow, "showWindow");
}
