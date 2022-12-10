#ifndef IACTIVEFROMORIGIN_H
#define IACTIVEFROMORIGIN_H

#include "singleton.h"

#include <QString>

class IActiveFromOrigin : public Singleton<IActiveFromOrigin>
{
public:
	virtual bool shouldRunProcess() = 0;
	virtual QString group() = 0;
	virtual void startGroup(const char* groupIdentifier) = 0;
	virtual void endGroup() = 0;
	virtual bool isActive(const char* identifier) = 0;
	virtual void setActive(const char* identifier, bool active) = 0;

protected:
	IActiveFromOrigin() {}
};

#endif // IACTIVEFROMORIGIN_H
