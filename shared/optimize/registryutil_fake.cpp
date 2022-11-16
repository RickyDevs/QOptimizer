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

#include <QSettings>
#include "registrystrategy.h"

namespace registry_util
{

static QSettings settings("FakeRegistry.ini", QSettings::IniFormat);

QVariant get(const QString &uKey)
{
	return settings.value(uKey);
}


void set(const QString &uKey, const QVariant &value)
{
	settings.setValue(uKey, value);
}

void remove(const QString &uKey)
{
	settings.remove(uKey);
}


}
