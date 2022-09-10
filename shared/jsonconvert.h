#ifndef JSONCONVERT_H
#define JSONCONVERT_H

#include <functional>

#include <QString>
#include <QCoreApplication>
#include <QVector>

struct unused {};

template<typename T>
struct extract_value_type //lets call it extract_value_type
{
	typedef T value_type1;
	typedef T value_type2;
};

template<template<typename> class X, typename T>
struct extract_value_type<X<T*>>   //specialization
{
	typedef X<T*> value_type1;
	typedef T value_type2;
};


class JsonConvert
{
private:
	static bool deserializeQObject(const QString& json, QObject* target);

	template<typename T, typename Z = unused>
	static T* deserializeSingleObject(const QString& json, QObject* parent) {
		T* target = new T(parent);
		if (JsonConvert::deserializeQObject(json, target)) {
			return target;
		}
		delete target;
		return Q_NULLPTR;
	}

	static bool deserializeQVector(const QString& json, QVector<QObject*>* pVector, std::function<QObject*()> objCreator);

	template<typename X, typename T>
	static X* deserializeObjectVector(const QString& json, QObject* parent) {
		X* vector = new X(0);
		if (JsonConvert::deserializeQVector(json, (QVector<QObject*>*)(vector), [parent](){
				return static_cast<QObject*>(new T(parent));
				})) {
			return vector;
		}
		delete vector;
		return Q_NULLPTR;
	}

public:

	template<typename T>
	static T* deserializeObject(const QString& json, QObject* parent = Q_NULLPTR) {
		typedef typename extract_value_type<T>::value_type1 valueType1;
		typedef typename extract_value_type<T>::value_type2 valueType2;
		typedef QVector<valueType2*> QVector_T;

		if (std::is_same<valueType1, valueType2>::value) {
			return (T*)deserializeSingleObject<valueType2>(json, parent);

		} else if (std::is_same<valueType1, QVector_T>::value) {
			return (T*)deserializeObjectVector<valueType1, valueType2>(json, parent);
		}

		return Q_NULLPTR;
	}

private:
	JsonConvert() = default;
};

#endif // JSONCONVERT_H
