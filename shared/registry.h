#ifndef REGISTRY_H
#define REGISTRY_H

#include <QString>

struct RegistryKey {

};

class Registry
{
public:
	Registry();

	QString getValue(const QString& v, const QString& v1, const QString& v2) {
		Q_UNUSED(v)
		Q_UNUSED(v1)
		Q_UNUSED(v2)
		return ""; }
};

#endif // REGISTRY_H
