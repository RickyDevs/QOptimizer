#ifndef QOPTIONAL_H
#define QOPTIONAL_H

#include <QtCore/qglobal.h>

template<class T>
class QOptional
{
public:
	QOptional() = default;
/*	explicit QOptional(const QOptional& source);
	explicit QOptional(QOptional&& source);

	// observers
	const T* operator->() const Q_DECL_NOTHROW;
	T* operator->() noexcept;
	const T& operator*() const& Q_DECL_NOTHROW;
	T& operator*() & Q_DECL_NOTHROW ;
	T&& operator*() && Q_DECL_NOTHROW ;
	const T&& operator*() const&& Q_DECL_NOTHROW ;
	explicit operator bool() const Q_DECL_NOTHROW ;
	bool hasValue() const Q_DECL_NOTHROW ;
	const T& value() const&;
	T& value() &;
	T&& value() &&;
	const T&& value() const&&;
	T valueOr(T&&) const&;
	T valueOr(T&&) &&;

	void clear();
private:
	T* pt;*/
};

#endif // QOPTIONAL_H
