#ifndef QTGLOBALMUTEX_H
#define QTGLOBALMUTEX_H

#include <QString>
#include <QSharedMemory>

class QtGlobalMutex
{
public:
	QtGlobalMutex(const QString& name);
	~QtGlobalMutex();

	bool lock();
	bool unlock();

private:
   QSharedMemory* sharedMemory; /*!< Used to provide the locking and unlocking
									 implementation*/
};

#endif // QTGLOBALMUTEX_H
