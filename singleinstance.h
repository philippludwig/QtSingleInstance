#pragma once


#include <QTcpServer>
#include <QTimer>

/**
 * This is the main class which handles the Instance of the application.
 * Please note that this just works by creating a TcpServer, therefore this
 * method is only suitable if you quickly want to prototype something;
 * for production scenarios you should utilize pid files, Mutexes or something
 * else, depending on your platform.
 **/
class SingleInstance : public QObject {
Q_OBJECT

	/**
	 * This is the port on which this server listens. Change it to something
	 * hopefully unique.
	 **/
	static int constexpr PORT = 56984;

	// Our TCPServer instance.
	QTcpServer m_server;

	// We need this timer to detect connection timeouts.
	QTimer m_timer;

	void checkForRunningInstance();

public:
	SingleInstance(QObject *parent = nullptr);

	/**
	 * Trys to start the Server. If it no already running instance of this
	 * application is found, the signal \e onlyInstance is emitted.
	 *
	 * If an already running instance is found, the signal \e otherInstanceFound
	 * is emitted.
	 **/
	void startInstance();

signals:
	//! Emitted if this instance receives a new message from a second instance.
	void newMessage(const QString &msg);

	/**
	 * @brief Emitted if an already running instance has been found.
	 *
	 * @param frozen \e true if the other instance doesn't react to our messages.
	 **/
	void otherInstanceFound(bool frozen);

	//! Emitted if this is the only instance of the application.
	void onlyInstance();
};
