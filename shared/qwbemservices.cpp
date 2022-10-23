
#include "qwbemservices.h"

#define _WIN32_DCOM

#include <ActiveQt/qaxtypes.h>

#include <qt_windows.h>
#include "qt_comutils.h"

#include <comdef.h>
#include <Wbemidl.h>


struct QWbemServicesPrivate {
	QComPtr<IWbemLocator> loc;
	QComPtr<IWbemServices> svc;
};

// ----

//class EventSink : public IWbemObjectSink
//{
//	LONG m_lRef;
//	bool bDone;

//public:
//	EventSink() { m_lRef = 0; }
//   ~EventSink() { bDone = true; }

//	virtual ULONG STDMETHODCALLTYPE AddRef();
//	virtual ULONG STDMETHODCALLTYPE Release();
//	virtual HRESULT
//		STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);

//	virtual HRESULT STDMETHODCALLTYPE Indicate(
//			LONG lObjectCount,
//			IWbemClassObject __RPC_FAR *__RPC_FAR *apObjArray
//			);

//	virtual HRESULT STDMETHODCALLTYPE SetStatus(
//			/* [in] */ LONG lFlags,
//			/* [in] */ HRESULT hResult,
//			/* [in] */ BSTR strParam,
//			/* [in] */ IWbemClassObject __RPC_FAR *pObjParam
//			);
//};

// ----

QWbemServices::QWbemServices(QObject *parent)
	: QObject(parent), _q(new QWbemServicesPrivate())
{
}

QWbemServices::~QWbemServices()
{
	delete _q;
}

bool QWbemServices::ensureConnected()
{
	if (!_q->svc.isNull()) {
		return true;
	}
	QConvertBSTR _bstr;

	HRESULT hres = CoCreateInstance(
				CLSID_WbemLocator,
				0,
				CLSCTX_INPROC_SERVER,
				IID_IWbemLocator,
				(LPVOID *) _q->loc.getAddressOf());

	if (FAILED(hres)) {
		// fail to init locator
		emit initializationError();
		return false;
	}

	// Connect to the root\cimv2 namespace with
	// the current user and obtain pointer pSvc
	// to make IWbemServices calls.
	hres = _q->loc->ConnectServer(
		 _bstr("ROOT\\CIMV2"),    // Object path of WMI namespace
		 NULL,                    // User name. NULL = current user
		 NULL,                    // User password. NULL = current
		 0,                       // Locale. NULL indicates current
		 NULL,                    // Security flags.
		 0,                       // Authority (e.g. Kerberos)
		 0,                       // Context object
		 _q->svc.getAddressOf()   // pointer to IWbemServices proxy
	);

	if (FAILED(hres)) {
		// fail to connect to service
		emit initializationError();
		return false;
	}

	// Set security levels on the proxy -------------------------

	hres = CoSetProxyBlanket(
	   _q->svc.get(),               // Indicates the proxy to set
	   RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
	   RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
	   NULL,                        // Server principal name
	   RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx
	   RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
	   NULL,                        // client identity
	   EOAC_NONE                    // proxy capabilities
	);

	if (FAILED(hres)) {
		// fail to set proxy blanket
		emit initializationError();
		return false;
	}
	return true;
}

bool QWbemServices::query()
{
	if (!ensureConnected()) {
		return false;
	}
	QConvertBSTR _bstr;

	//QHash<QString, QVariant> map;
	QVariantMap map;

	QVariant xx = QVariant::fromValue(map);

	VARIANT v;

	QVariant x = VARIANTToQVariant(v, "");

	// TODO sleep(1) ... para deixar o sistema processar :P

	return !x.isNull() && !xx.isNull();
	// Receive event notifications -----------------------------

	// Use an unsecured apartment for security
//	IUnsecuredApartment* pUnsecApp = NULL;

//	HRESULT hres = CoCreateInstance(CLSID_UnsecuredApartment, NULL,
//		CLSCTX_LOCAL_SERVER, IID_IUnsecuredApartment,
//		(void**)&pUnsecApp);

//	EventSink* pSink = new EventSink;
//	pSink->AddRef();

//	IUnknown* pStubUnk = NULL;
//	pUnsecApp->CreateObjectStub(pSink, &pStubUnk);

//	IWbemObjectSink* pStubSink = NULL;
//	pStubUnk->QueryInterface(IID_IWbemObjectSink,
//		(void **) &pStubSink);

//	// The ExecNotificationQueryAsync method will call
//	// The EventQuery::Indicate method when an event occurs
//	hres = _q->svc->ExecNotificationQueryAsync(
//		_bstr("WQL"),
//		_bstr("SELECT * "
//			"FROM __InstanceCreationEvent WITHIN 1 "
//			"WHERE TargetInstance ISA 'Win32_Process'"),
//		WBEM_FLAG_SEND_STATUS,
//		NULL,
//		pStubSink);

	return true;
}
