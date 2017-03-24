#include <QCoreApplication>

#include "singleinstance.h"

int main(int argc, char **argv) {
	// Create a QApplication as usual
	QCoreApplication app(argc, argv);

	// Init our SingleInstance object
	SingleInstance si;

	// React appropriately if we find another running instance of this program.
	QObject::connect(&si, &SingleInstance::otherInstanceFound, [&](bool frozen) {
		if(frozen) {
			qDebug() << "Other instance is frozen";
			// If you reach this point, you will have to let the user know
			// about the problem.
		} else {
			qDebug() << "Other instance reacted nicely.";
		}
		app.quit();
	});

	// If this is the only/first instance of our application, we can
	// continue as normal.
	QObject::connect(&si, &SingleInstance::onlyInstance, [&]() {
		qDebug() << "This is the only instance.";
		qDebug() << "Waiting for messages...";
	});

	// If we get a message from a second instance, we would probably like
	// to react somehow.
	QObject::connect(&si, &SingleInstance::newMessage, [&](const QString &msg) {
		qDebug() << "Got a message: " << msg;
		if(msg == "QUIT") {
			// For example: Quit the application if requested.
			app.quit();
		}
	});

	// Now start this instance.
	si.startInstance();

	return app.exec();
}

