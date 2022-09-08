#include <QCoreApplication>
#include <QTimer>

#include "program.h"
#include "qdebug.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	// create the main class
	Program* program = new Program(&a);

	// connect up the signals
	QObject::connect(program, SIGNAL(finished()), &a, SLOT(quit()));
	QObject::connect(&a, SIGNAL(aboutToQuit()), program, SLOT(aboutToQuitApp()));

	// create singleshot timer to start run() in mainTask, while in the exec()
	QTimer::singleShot(0, program, SLOT(run()));

	return a.exec();
}
