#ifndef JSONCONVERT_H
#define JSONCONVERT_H

#include <QString>
#include <QCoreApplication>

class JsonConvert
{
public:
	static bool deserializeQObject(const QString& json, QObject* target);

	template<typename T>
	static T* deserializeObject(const QString& json) {
		T* target = new T((QObject*)QCoreApplication::instance());
		QObject* targetObj = static_cast<QObject*>(target);
		if (JsonConvert::deserializeQObject(json, targetObj)) {
			return target;
		}
		delete target;
		return nullptr;
	}

private:
	JsonConvert() = default;
};

#endif // JSONCONVERT_H
