#include "singleinstance.h"

#include <QTcpSocket>

SingleInstance::SingleInstance(QObject *parent) : QObject(parent), m_server(this) {
	// Listen to new connections on the defined port.
	connect(&m_server, &QTcpServer::newConnection, [=]() {
		QTcpSocket *conn = m_server.nextPendingConnection();

		// When we receive a message, simply reply with "OK"
		// to let the other instance know that we are alive and well.
		connect(conn, &QTcpSocket::readyRead, [=]() {
			QString msg {conn->readAll()};
			emit newMessage(msg);
			conn->write("OK");
		});

		// Close the connection socket when it is not needed anymore.
		connect(conn, &QTcpSocket::aboutToClose, conn, &QTcpSocket::deleteLater);
	});
}

void SingleInstance::startInstance() {
	// Try to start the TcpServer on the given port. If this is not possible,
	// we assume that another instance of the application is running.
	if(!m_server.listen(QHostAddress(QHostAddress::LocalHost), PORT)) {
		// If this is the case, try to connect to this other instance.
		checkForRunningInstance();
	} else {
		emit onlyInstance();
	}
}

void SingleInstance::checkForRunningInstance() {
	QTcpSocket *socket = new QTcpSocket(this);
	socket->connectToHost(QHostAddress(QHostAddress::LocalHost), PORT);

	// Wait for the connection
	connect(socket, &QTcpSocket::connected, [=]() {
		// Deactivate timeout-timer
		m_timer.stop();

		// Quick check
		connect(socket, &QTcpSocket::readyRead, [=]() {
			QString data {socket->readAll()};
			if(data != "OK") {
				// This is not our application
				emit otherInstanceFound(true);
			} else emit otherInstanceFound(false);
		});

		// Tell the running instance to restore the main window if it's minimized.
		socket->write("RESTORE");
	});

	// Detect timeout
	connect(&m_timer, &QTimer::timeout, [=]() {
		// Either there is no other running instance
		// or the other instance is frozen.
		emit otherInstanceFound(true);
	});
	m_timer.start(3000);
}
