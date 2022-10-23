#ifndef PROGRAM_H
#define PROGRAM_H

#include <QObject>
#include <QVariant>
#include "qwbemservices.h"

class Program : public QObject
{
	Q_OBJECT
public:
	explicit Program(QObject *parent = 0);

	Q_INVOKABLE QVariant createModel(const QString& modelName, const QVariantList& modelData);

public:
	static bool UNSAFE_MODE;

//public slots:
//	 void initServices();

private:
	QWbemServices* wbemServices;
};

#endif // PROGRAM_H
