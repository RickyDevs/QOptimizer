#ifndef QWBEMSERVICES_H
#define QWBEMSERVICES_H

#include <QObject>
#include <memory>

struct QWbemServicesPrivate;

class QWbemServices : public QObject
{
	Q_OBJECT
public:
	explicit QWbemServices(QObject *parent = 0);
	virtual ~QWbemServices();

	bool query();

signals:
	void initializationError();

private:
	bool ensureConnected();

private:
	QWbemServicesPrivate* _q;
};

#endif // QWBEMSERVICES_H
