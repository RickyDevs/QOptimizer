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

#include "registryutil.h"

#include <qt_windows.h>
#include "registrystrategy.h"

namespace registry_util
{


HKEY hKeyFromRegistryKey(const RegistryKey& key)
{
	switch (key.root) {
	case RegistryKeyEnum::currentUser:
		return HKEY_CURRENT_USER;
	case RegistryKeyEnum::classesRoot:
		return HKEY_CLASSES_ROOT;
	default:
		break;
	}
	return 0;
}



// TODO ...
void set(const QString &uKey, const QVariant &value)
{
	if (writeHandle() == 0) {
		setStatus(QSettings::AccessError);
		return;
	}

	QString rKey = escapedKey(uKey);

	HKEY handle = createOrOpenKey(writeHandle(), registryPermissions, keyPath(rKey), access);
	if (handle == 0) {
		setStatus(QSettings::AccessError);
		return;
	}

	DWORD type;
	QByteArray regValueBuff;

	// Determine the type
	switch (value.type()) {
		case QVariant::List:
		case QVariant::StringList: {
			// If none of the elements contains '\0', we can use REG_MULTI_SZ, the
			// native registry string list type. Otherwise we use REG_BINARY.
			type = REG_MULTI_SZ;
			QStringList l = variantListToStringList(value.toList());
			QStringList::const_iterator it = l.constBegin();
			for (; it != l.constEnd(); ++it) {
				if ((*it).length() == 0 || it->contains(QChar::Null)) {
					type = REG_BINARY;
					break;
				}
			}

			if (type == REG_BINARY) {
				QString s = variantToString(value);
				regValueBuff = QByteArray((const char*)s.utf16(), s.length() * 2);
			} else {
				QStringList::const_iterator it = l.constBegin();
				for (; it != l.constEnd(); ++it) {
					const QString &s = *it;
					regValueBuff += QByteArray((const char*)s.utf16(), (s.length() + 1) * 2);
				}
				regValueBuff.append((char)0);
				regValueBuff.append((char)0);
			}
			break;
		}

		case QVariant::Int:
		case QVariant::UInt: {
			type = REG_DWORD;
			qint32 i = value.toInt();
			regValueBuff = QByteArray((const char*)&i, sizeof(qint32));
			break;
		}

		case QVariant::LongLong:
		case QVariant::ULongLong: {
			type = REG_QWORD;
			qint64 i = value.toLongLong();
			regValueBuff = QByteArray((const char*)&i, sizeof(qint64));
			break;
		}

		case QVariant::ByteArray:
			Q_FALLTHROUGH();

		default: {
			// If the string does not contain '\0', we can use REG_SZ, the native registry
			// string type. Otherwise we use REG_BINARY.
			QString s = variantToString(value);
			type = s.contains(QChar::Null) ? REG_BINARY : REG_SZ;
			if (type == REG_BINARY) {
				regValueBuff = QByteArray((const char*)s.utf16(), s.length() * 2);
			} else {
				regValueBuff = QByteArray((const char*)s.utf16(), (s.length() + 1) * 2);
			}
			break;
		}
	}

	// set the value
	LONG res = RegSetValueEx(handle, reinterpret_cast<const wchar_t *>(keyName(rKey).utf16()), 0, type,
							 reinterpret_cast<const unsigned char*>(regValueBuff.constData()),
							 regValueBuff.size());

	if (res == ERROR_SUCCESS) {
		deleteWriteHandleOnExit = false;
	} else {
		qWarning("QSettings: failed to set subkey \"%s\": %s",
				rKey.toLatin1().data(), errorCodeToString(res).toLatin1().data());
		setStatus(QSettings::AccessError);
	}

	RegCloseKey(handle);
}

bool get(const QString &uKey, QVariant *value)
{
	QString rKey = escapedKey(uKey);

	for (int i = 0; i < regList.size(); ++i) {
		HKEY handle = regList.at(i).handle();
		if (handle != 0 && readKey(handle, rKey, value))
			return true;

		if (!fallbacks)
			return false;
	}

	return false;
}



}
