/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef QT_COMUTILS_H
#define QT_COMUTILS_H

#if !defined(_WINDOWS_) && !defined(_WINDOWS_H) && !defined(__WINDOWS__)
#error Must include windows.h first!
#endif

#include <ocidl.h>
#include <QtCore/qstring.h>

QT_BEGIN_NAMESPACE


#ifndef QVariant2VARIANT
class QVariant;

// Originally QVariantToVARIANT copied from ActiveQt - renamed to avoid conflicts in static builds.
bool QVariant2VARIANT(const QVariant &var, VARIANT &arg, const QByteArray &typeName, bool out) {return false;}
#endif

#ifndef QAXTYPEFUNCTIONS_P_H
inline BSTR QStringToBSTR(const QString &str)
{
    return SysAllocStringLen(reinterpret_cast<const OLECHAR *>(str.unicode()), UINT(str.length()));
}
#endif


QT_END_NAMESPACE

/**
 * @brief The QConvertBSTR class
 * Wrapper class to convert QString(s) to BSTR and with auto release.
 *
 * E.g.
 *  QBSTRManager _bstr;
 *
 *  BSTR myVar = _bstr("WQL");
 */

class QConvertBSTR {

public:
	QConvertBSTR() = default;

	BSTR operator ()(const QString &str) {
		BSTR v = QStringToBSTR(str);
		_list.append(v);
		return v;
	}

	~QConvertBSTR() {
		for (BSTR v : _list) {
			SysFreeString(v);
		}
	}

private:
	QList<BSTR> _list;
};

/**
 *
 */
template <typename T>
class QComPtr
{
public:
    typedef T InterfaceType;

protected:
    InterfaceType *ptr_;

    void InternalAddRef() const throw()
    {
        if (ptr_ != nullptr)
        {
            ptr_->AddRef();
        }
    }

    unsigned long InternalRelease() throw()
    {
        unsigned long ref = 0;
        T* temp = ptr_;

        if (temp != nullptr)
        {
            ptr_ = nullptr;
            ref = temp->Release();
        }

        return ref;
    }

public:
	// region constructors
    QComPtr() throw() : ptr_(nullptr)
    {
    }

    template<class U>
    QComPtr(_In_opt_ U *other) throw() : ptr_(other)
    {
        InternalAddRef();
    }

    QComPtr(const QComPtr& other) throw() : ptr_(other.ptr_)
    {
        InternalAddRef();
    }

	QComPtr(_Inout_ QComPtr &&other) throw() : ptr_(nullptr)
    {
		if (this != reinterpret_cast<QComPtr*>(&reinterpret_cast<unsigned char&>(other)))
        {
            Swap(other);
        }
    }

	// region destructor
	~QComPtr() throw()
    {
        InternalRelease();
    }

	// region assignment
    QComPtr& operator=(_In_opt_ T *other) throw()
    {
        if (ptr_ != other)
        {
            QComPtr(other).Swap(*this);
        }
        return *this;
    }

    template <typename U>
    QComPtr& operator=(_In_opt_ U *other) throw()
    {
        QComPtr(other).Swap(*this);
        return *this;
    }

    QComPtr& operator=(const QComPtr &other) throw()
    {
        if (ptr_ != other.ptr_)
        {
            QComPtr(other).Swap(*this);
        }
        return *this;
    }

    template<class U>
    QComPtr& operator=(const QComPtr<U>& other) throw()
    {
        ComPtr(other).Swap(*this);
        return *this;
    }

    QComPtr& operator=(_Inout_ QComPtr &&other) throw()
    {
		QComPtr(static_cast<QComPtr&&>(other)).Swap(*this);
        return *this;
    }

    template<class U>
	QComPtr& operator=(_Inout_ QComPtr<U>&& other) throw()
    {
		QComPtr(static_cast<QComPtr<U>&&>(other)).Swap(*this);
        return *this;
    }

	// region modifiers
	void Swap(_Inout_ QComPtr&& r) throw()
    {
        T* tmp = ptr_;
        ptr_ = r.ptr_;
        r.ptr_ = tmp;
    }

	void Swap(_Inout_ QComPtr& r) throw()
    {
        T* tmp = ptr_;
        ptr_ = r.ptr_;
        r.ptr_ = tmp;
    }

	T* get() const throw()
    {
        return ptr_;
    }

	bool isNull() const
	{
		return ptr_ == nullptr;
	}

    // allow use of sealed / final in retail builds.
	typename QComPtr::InterfaceType* operator->() const throw()
    {
        return ptr_;
    }

	T* const* getAddressOf() const throw()
    {
        return &ptr_;
    }

	T** getAddressOf() throw()
    {
        return &ptr_;
    }

    T** ReleaseAndGetAddressOf() throw()
    {
        InternalRelease();
        return &ptr_;
    }

    T* Detach() throw()
    {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }

    void Attach(_In_opt_ InterfaceType* other) throw()
    {
        if (ptr_ != nullptr)
        {
            auto ref = ptr_->Release();
            DBG_UNREFERENCED_LOCAL_VARIABLE(ref);
            // Attaching to the same object only works if duplicate references are being coalesced. Otherwise
            // re-attaching will cause the pointer to be released and may cause a crash on a subsequent dereference.
            __WRL_ASSERT__(ref != 0 || ptr_ != other);
        }

        ptr_ = other;
    }

    unsigned long Reset()
    {
        return InternalRelease();
    }

    HRESULT CopyTo(_Outptr_result_maybenull_ InterfaceType** ptr) const throw()
    {
        InternalAddRef();
        *ptr = ptr_;
        return S_OK;
    }

    HRESULT CopyTo(REFIID riid, _Outptr_result_nullonfailure_ void** ptr) const throw()
    {
        return ptr_->QueryInterface(riid, ptr);
    }

    template<typename U>
    HRESULT CopyTo(_Outptr_result_nullonfailure_ U** ptr) const throw()
    {
        return ptr_->QueryInterface(__uuidof(U), reinterpret_cast<void**>(ptr));
    }

    // query for U interface
    template<typename U>
    HRESULT As(_Out_ QComPtr<U>* p) const throw()
    {
        return ptr_->QueryInterface(__uuidof(U), reinterpret_cast<void**>(p->ReleaseAndGetAddressOf()));
    }

    // query for riid interface and return as IUnknown
	HRESULT AsIID(REFIID riid, _Out_ QComPtr<IUnknown>* p) const throw()
    {
        return ptr_->QueryInterface(riid, reinterpret_cast<void**>(p->ReleaseAndGetAddressOf()));
    }

};    // ComPtr


#endif // QT_COMUTILS_H

