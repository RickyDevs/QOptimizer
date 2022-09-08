#include "errorlogger.h"


#ifdef QO_CONSOLE
#include <iostream>
#endif

void ErrorLogger::logError(const QString& functionName, const QString& errorMessage)
{
#ifdef QO_CONSOLE
	std::cerr << "ERROR: " << errorMessage.toStdString() << " at " << functionName.toStdString() << std::endl;
#else
#error No log implementaion
#endif

}
