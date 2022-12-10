/****************************************************************************
**
** QOptimizer
** Copyright (C) 2022 by RickyDevs
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QFile>
#include <qt_windows.h>
#include <io.h>
#include <QQmlContext>

#include "program.h"
#include "qcominitializer.h"
#include "qoptimizeproxymanager.h"
#include "activefromoriginimpl.h"
#include "optimizemanager.h"

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

QScopedPointer<QFile>   m_logFile;

int main(int argc, char *argv[])
{
	QComInitializer comInit;

	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);

//	QQuickStyle::setStyle("Material");
	// Set the logging file
	// check which a path to file you use
	//m_logFile.reset(new QFile("logFile.txt"));
	// Open the file logging
	//m_logFile.data()->open(QFile::Append | QFile::Text);
	// Set handler
	// qInstallMessageHandler(messageHandler);

	// FILE *loggingStreamStdout;
		   // FILE *loggingStreamStderr;
		  // QFile loggingFile("app.log");

		   // m_logFile.data()->open(QIODevice::Text | QIODevice::Append | QIODevice::Unbuffered);
		   // int fd = m_logFile.data()->handle();

		   // freopen_s(&loggingStreamStdout, "\\\\.\\NUL", "w", stdout);
		   // setvbuf(loggingStreamStdout, NULL, _IONBF, 0);
		   // freopen_s(&loggingStreamStderr, "\\\\.\\NUL", "w", stderr);
		   // setvbuf(loggingStreamStderr, NULL, _IONBF, 0);
		   // _dup2(fd, _fileno(stdout));
		   // _dup2(fd, _fileno(stderr));


	QCoreApplication::setOrganizationName("RickyDevs-Soft");
	QCoreApplication::setApplicationName("QOptimizer");

	QQmlApplicationEngine engine;
	QQmlContext *context = engine.rootContext();

	if (comInit.isOk()) {
		comInit.initSecurity();
	}


	// Inject singleton implementations
	IActiveFromOrigin::registerImplementation(ActiveFromOriginImpl::create);
	OptimizeManager::registerImplementation();

	// Inject C++ class to QML
	context->setContextProperty(QStringLiteral("optimizeManager"), new QOptimizeProxyManager(&engine));
	context->setContextProperty(QStringLiteral("program"), new Program(&engine));

	engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

	return app.exec();
}

// The implementation of the handler
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	// Open stream file writes
	QTextStream out(m_logFile.data());
	// Write the date of recording
	out << msg << endl;
	out.flush();    // Clear the buffered data
}
