#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QObject>

class QCommandLineParser;
class QCommandLineOption;

class Program : public QObject
{
    Q_OBJECT
public:
	explicit Program(QObject *parent = 0);
	// call this to quit the application
	void quit();

signals:
	// signal to finish, this is connected to Application Quit.
	void finished();

public slots:
	// this is the slot that gets called from main to start everything
	// but, everything is set up in the constructor.
	void run();

	// slot that get signal when the application is about to quit.
	void aboutToQuitApp();

public:
	static QString getCurrentVersionToString();
	static float getCurrentVersion();

	static int major;
	static int minor;
	static bool EXPERIMENTAL_BUILD;
	static bool UNSAFE_MODE;

private:
	void processOptions(const QCommandLineParser& parser, const QList<QCommandLineOption>& options);
};

#endif // MAINCLASS_H
