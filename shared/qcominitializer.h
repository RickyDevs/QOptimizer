#ifndef QCOMINITIALIZER_H
#define QCOMINITIALIZER_H

#include <qt_windows.h>

class QComInitializer
{
public:
	QComInitializer();
	~QComInitializer();

	bool isOk();
	bool initSecurity();

private:
	HRESULT _hr;
};

#endif // QCOMINITIALIZER_H
