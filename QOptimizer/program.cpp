#include "program.h"

#include <iostream>
#include <functional>

#include <QCoreApplication>
#include <QDebug>
#include <QCommandLineParser>

#include "utilities.h"
#include "qtglobalmutex.h"
#include "configops.h"
#include "config.h"


enum CommandLineOption : int {
	UnsafeMode = 0,
	DisableHPET,
	EnableHPET,
//	AddStartup,
//	DeleteStartup,
	UnlockCores,
	Reset,
	DisableHibernation,
	EnableHibernation,
	Config,

	Help,
	Version,
	EnumLast
};

/* VERSION PROPERTIES */
/* DO NOT LEAVE THEM EMPTY */

int Program::major = 13;
int Program::minor = 9;

bool Program::EXPERIMENTAL_BUILD = false;
bool Program::UNSAFE_MODE = false;

const QString optimizerMutexId = "QOtimizer_GlobalMutex_02";

struct CommandRun {
	CommandLineOption option;
	std::function<void()> callback;
	QString message;
	bool adminRequired;

	CommandRun(CommandLineOption opt, const std::function<void()>& cb, const QString& msg, bool ar = true) :
		option(opt), callback(cb), message(msg), adminRequired(ar) {}
};

Program::Program(QObject *parent) : QObject(parent)
{
}

QString Program::getCurrentVersionToString()
{
	return QString("%1.%2").arg(major).arg(minor);
}

float Program::getCurrentVersion()
{
	return getCurrentVersionToString().toFloat();
}


void Program::run()
{
	QList<QCommandLineOption> options =
	{
		{"unsafe",
					"Unsafe mode (windows server)"
		},
		{"disablehpet",
					"DisableHPET."},
		{"enablehpet",
					"EnableHPET."},
//		{"addstartup",
//					"Add to startup"},
//		{"deletestartup",
//					"delete from startup"},
		{"unlockcores",
					"unlock cores"},
		{"reset",
					"reset"},
		{"disablehibernate",
					"disable hibernate"},
		{"enablehibernate",
					"enable hibernate"},
		{"config",
					"applies a config <file>",
					"file"},
	};

	QCommandLineParser parser;

	parser.addOptions(options);
	options << parser.addHelpOption();
	options << parser.addVersionOption();

	 Q_ASSERT_X(options.size() == CommandLineOption::EnumLast, "parser", "sanity check failed");

	if (!parser.parse(QCoreApplication::arguments())) {
		std::cerr << parser.errorText().toStdString() << std::endl;
		QCoreApplication::exit(-1);
		return;
	}

	if (parser.isSet(options[CommandLineOption::Version])) {
		std::cout << "QOptimizer: v" << Program::getCurrentVersionToString().toStdString() << std::endl;
		std::cout << "Ported by: Amilcar Santos" << std::endl;
		std::cout << "Based on Optimizer v13.9 by deadmoon" << std::endl;
		quit();
		return;
	}

	if (parser.isSet(options[CommandLineOption::Help])) {
		parser.showHelp();
	}

	processOptions(parser, options);
	quit();

}

void Program::processOptions(const QCommandLineParser& parser, const QList<QCommandLineOption>& options)
{
	QtGlobalMutex mutex(optimizerMutexId);
	if (!mutex.lock()) {
		std::cerr << "Another instance is already running" << std::endl;
		QCoreApplication::exit(-2);
		return;
	}

	if (parser.isSet(options[CommandLineOption::UnsafeMode])) {
		UNSAFE_MODE = true;
		std::cout << "Using unsafe mode" << std::endl;
	}

	QList<CommandRun> commandRuns = {
		{
			CommandLineOption::DisableHPET,
			Utilities::disableHPET,
			"HPET is disabled"
		},
		{
			CommandLineOption::EnableHPET,
			Utilities::enableHPET,
			"HPET is enabled"
		},
		{
			CommandLineOption::UnlockCores,
			Utilities::unlockAllCores,
			"All cores are unlocked"
		},
		{
			CommandLineOption::DisableHibernation,
			Utilities::disableHibernation,
			"Hibernation is disabled"
		},
		{
			CommandLineOption::EnableHibernation,
			Utilities::enableHibernation,
			"Hibernation is enabled"
		},
		{
			CommandLineOption::Config,
			[&parser]() {
				//std::cout << parser.value("config").toStdString() << std::endl;
				ConfigOps::processConfigFile(parser.value("config"));
			},
			"Config file applied"
		}
	};

	for (const CommandRun& run : commandRuns) {
		if (parser.isSet(options[run.option])) {
			if (run.adminRequired && !Utilities::isAdmin()) {
				std::cerr << "QOptimizer needs to be run as administrator!" << std::endl;
				QCoreApplication::exit(-1);
				return;
			}
			run.callback();
			std::cout << run.message.toStdString() << std::endl;
			return;
		}
	}
}


void Program::quit()
{
	// send finished signal to quit
	emit finished();
}


void Program::aboutToQuitApp()
{
	// stop threads
	//qDebug() << "stopping threads ...";
	// sleep(1)
	// delete any objects ...
}

