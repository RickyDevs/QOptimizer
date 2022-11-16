/****************************************************************************
**
** QOptimizer
** Copyright (C) 2022 by RickyDevs
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

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

QVariant variantToQVariant(const VARIANT* pVarValue) {

	auto type = V_VT(pVarValue);
	if (type == VT_I4) {
		return V_INT(pVarValue);
	}
	if (type == VT_DECIMAL) {
		_variant_t test(pVarValue);
		return QVariant(static_cast<double>(test));
	}
	if (type == VT_BOOL) {
		return QVariant(V_BOOL(pVarValue));
	}
	if (type == VT_BSTR) {
		//printf("%s: %ls\n", _field.toStdString().c_str(), V_BSTR(&varName));
		return QString::fromWCharArray(V_BSTR(pVarValue));
	}
	return QVariant();
}

class ResponseSink : public IWbemObjectSink
{
	LONG _lRef;
	QStringList _fieldList;
	QVariantMap _initMap;
	QWbemServices* _wbemServices;
	QWbemQueryResult* _result;

public:
	ResponseSink(const QStringList& fieldList, int resultData, QWbemServices* wbem)
	{
		_lRef = 0;
		_fieldList = fieldList;
		_wbemServices = wbem;
		_result = new QWbemQueryResult(resultData);
	}

	virtual ~ResponseSink()
	{
		delete _result;
	}

	void setInitMap(const QVariantMap& map) {
		_initMap = map;
	}

	virtual ULONG STDMETHODCALLTYPE AddRef() override
	{
		return InterlockedIncrement(&_lRef);
	}

	virtual ULONG STDMETHODCALLTYPE Release() override
	{
		LONG lRef = InterlockedDecrement(&_lRef);
		if (lRef == 0) {
			delete this;
		}
		return lRef;
	}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv) override
	{
		if (riid == IID_IUnknown || riid == IID_IWbemObjectSink) {
			*ppv = (IWbemObjectSink *) this;
			AddRef();
			return WBEM_S_NO_ERROR;
		}
		return E_NOINTERFACE;
	}

	virtual HRESULT STDMETHODCALLTYPE Indicate(
			LONG lObjectCount,
			IWbemClassObject __RPC_FAR *__RPC_FAR *apObjArray) override
	{
		HRESULT hRes = S_OK;

		QConvertBSTR _bstr;
		std::vector<BSTR> fieldNameBSTRList;
		for (QString f : _fieldList) {
			fieldNameBSTRList.emplace_back(_bstr(f));
		}

		for (int i = 0; i < lObjectCount; i++)
		{
			VARIANT varValue;
			QVariantMap map = _initMap;
			int idx = 0;
			for (BSTR fieldNameBstr : fieldNameBSTRList) {

				hRes = apObjArray[i]->Get(fieldNameBstr, 0, &varValue, 0, 0);
				if (FAILED(hRes))
				{
					//printf("Failed to get the data from the query" \
					//		" Error code = 0x", hRes);
					return WBEM_E_FAILED;       // Program has failed.
				}
				QString fieldName = _fieldList[idx];
				map[fieldName] = variantToQVariant(&varValue);

				VariantClear(&varValue);
				idx++;
			}

			_result->resultList.append(map);
		}
		_result->success = true;
		return WBEM_S_NO_ERROR;
	}

	virtual HRESULT STDMETHODCALLTYPE SetStatus(
			LONG lFlags,
			HRESULT hResult,
			BSTR strParam,
			IWbemClassObject __RPC_FAR *pObjParam
			) override
	{
		Q_UNUSED(hResult)
		Q_UNUSED(strParam)
		Q_UNUSED(pObjParam)
		if (lFlags == WBEM_STATUS_COMPLETE) {
			QWbemQueryResultPublisher* publisher = new QWbemQueryResultPublisher();
			QObject::connect(publisher, &QWbemQueryResultPublisher::sinkResult, _wbemServices, &QWbemServices::sinkResult, Qt::QueuedConnection);

			publisher->sendResult(this, _result);
			delete publisher;
		}

		return WBEM_S_NO_ERROR;
	}
};

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

bool QWbemServices::query(const QString& query, const QStringList& fieldList, int resultData)
{
	if (!ensureConnected()) {
		return false;
	}
	QConvertBSTR _bstr;

	// Receive event notifications -----------------------------
	ResponseSink* sink = new ResponseSink(fieldList, resultData,  this);
	sink->AddRef();

	// The ResponseSink::Indicate method when an event occurs
	HRESULT hRes = _q->svc->ExecQueryAsync(
		_bstr("WQL"),
		_bstr(query),
		WBEM_FLAG_SEND_STATUS,
		NULL,
		sink);
	if (FAILED(hRes)) {
		sink->Release();
		return false;
	}
	return true;
}

void QWbemServices::sinkResult(void* sink, QWbemQueryResult* queryResult) {
	printf("void QWbemServices::sinkResult(\n");

	emit result(*queryResult);

	printf("aku");
	static_cast<IUnknown*>(sink)->Release();
}
