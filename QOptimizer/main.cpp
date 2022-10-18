#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QFile>
#include <qt_windows.h>
#include <io.h>

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

QScopedPointer<QFile>   m_logFile;

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);

//	QQuickStyle::setStyle("Material");
	// Set the logging file
	// check which a path to file you use
	m_logFile.reset(new QFile("logFile.txt"));
	// Open the file logging
	//m_logFile.data()->open(QFile::Append | QFile::Text);
	// Set handler
	qInstallMessageHandler(messageHandler);

	FILE *loggingStreamStdout;
		   FILE *loggingStreamStderr;
	//	   QFile loggingFile("app.log");

		   m_logFile.data()->open(QIODevice::Text | QIODevice::Append | QIODevice::Unbuffered);
		   int fd = m_logFile.data()->handle();

		   freopen_s(&loggingStreamStdout, "\\\\.\\NUL", "w", stdout);
		   setvbuf(loggingStreamStdout, NULL, _IONBF, 0);
		   freopen_s(&loggingStreamStderr, "\\\\.\\NUL", "w", stderr);
		   setvbuf(loggingStreamStderr, NULL, _IONBF, 0);
		   _dup2(fd, _fileno(stdout));
		   _dup2(fd, _fileno(stderr));


	QQmlApplicationEngine engine;
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
