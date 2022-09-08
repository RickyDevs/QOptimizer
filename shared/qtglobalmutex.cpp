#include "qtglobalmutex.h"

QtGlobalMutex::QtGlobalMutex(const QString& name)
{
	sharedMemory = new QSharedMemory(name);
}

QtGlobalMutex::~QtGlobalMutex()
{
	delete sharedMemory;
}

bool QtGlobalMutex::lock()
{
	return sharedMemory->create(1);
}

bool QtGlobalMutex::unlock()
{
	// no implementation
	return false; //return sharedMemory->unlock();
}
