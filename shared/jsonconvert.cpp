#include "jsonconvert.h"

#include <QVariant>

#include "errorlogger.h"
#include "hjson.h"


QVariant toQVariant(const Hjson::Value& value) {
	switch (value.type()) {
	case Hjson::Type::Bool:
		return QVariant(static_cast<bool>(value));
	case Hjson::Type::Int64:
		return QVariant(static_cast<long long>(value));
	case Hjson::Type::String:
		return QVariant(static_cast<const char*>(value));
	default:
		LOG_ERROR(QString("Parse error: Unknown json type %1").arg((int)value.type()));
	}

	return QVariant();
}




bool JsonConvert::deserializeQObject(const QString& json, QObject* target)
{
	try {
		Hjson::Value jsonRoot = Hjson::Unmarshal(json.toStdString());

		if (jsonRoot.type() != Hjson::Type::Map) {
			LOG_ERROR("Parse error: Invalid root element");
			return false;
		}

		for (const auto& jsonNode : jsonRoot) {
			if (!target->setProperty(jsonNode.first.c_str(), toQVariant(jsonNode.second))) {
				LOG_ERROR(QString("Parse error: Unknown field '%1'").arg(jsonNode.first.c_str()));
			}
		}
	} catch (std::exception e) {
		LOG_ERROR(QString("Parse error: %1").arg(e.what()));
	}
	return true;
}



bool JsonConvert::deserializeQVector(const QString& json, QVector<QObject*>* vector, std::function<QObject*()> objCreator) {
	try {
		Hjson::Value jsonRoot = Hjson::Unmarshal(json.toStdString());

		if (jsonRoot.type() != Hjson::Type::Vector) {
			LOG_ERROR("Parse error: Invalid root element");
			return false;
		}
		for (size_t i = 0; i < jsonRoot.size(); i++) {
			QObject* target = objCreator();
			vector->push_back(target);
			for (const auto& jsonNode : jsonRoot[(int)i]) {
				if (!target->setProperty(jsonNode.first.c_str(), toQVariant(jsonNode.second))) {
					LOG_ERROR(QString("Parse error: Unknown field '%1'").arg(jsonNode.first.c_str()));
				}
			}
		}

	} catch (std::exception e) {
		LOG_ERROR(QString("Parse error: %1").arg(e.what()));
	}

	return true;
}
