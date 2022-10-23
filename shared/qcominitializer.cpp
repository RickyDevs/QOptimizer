#include "qcominitializer.h"

QComInitializer::QComInitializer()
{
	_hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
}

QComInitializer::~QComInitializer()
{
	if (isOk()) {
		CoUninitialize();
	}
}

bool QComInitializer::isOk()
{
	return !FAILED(_hr);
}

bool QComInitializer::initSecurity()
{
	// Set general COM security levels --------------------------
	// Note: If you are using Windows 2000, you need to specify -
	// the default authentication credentials for a user by using
	// a SOLE_AUTHENTICATION_LIST structure in the pAuthList ----
	// parameter of CoInitializeSecurity ------------------------

	HRESULT hres =  CoInitializeSecurity(
		NULL,
		-1,                          // COM authentication
		NULL,                        // Authentication services
		NULL,                        // Reserved
		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication
		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
		NULL,                        // Authentication info
		EOAC_NONE,                   // Additional capabilities
		NULL                         // Reserved
		);


	return !FAILED(hres);
}
