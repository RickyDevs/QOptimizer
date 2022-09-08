#ifndef ERRORLOGGER_H
#define ERRORLOGGER_H

#include <QString>

#define LOG_ERROR(message)	ErrorLogger::logError(__func__, message);

class ErrorLogger
{
public:
	static void logError(const QString& functionName, const QString& errorMessage);

private:
	ErrorLogger() = default;
};

#endif // ERRORLOGGER_H
