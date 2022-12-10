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

#include "activefromoriginimpl.h"
#include <QCoreApplication>

ActiveFromOriginImpl* ActiveFromOriginImpl::create()
{
	return new ActiveFromOriginImpl();
}

ActiveFromOriginImpl::ActiveFromOriginImpl()
	: _settings(QSettings::SystemScope, QCoreApplication::organizationName(), QCoreApplication::applicationName())
{

}

bool ActiveFromOriginImpl::shouldRunProcess()
{
	// compare versions
	// TODO

	return true;
}

QString ActiveFromOriginImpl::group()
{
	return _settings.group();
}

void ActiveFromOriginImpl::startGroup(const char* groupIdentifier)
{
	Q_ASSERT_X(!QString(groupIdentifier).contains('/'), qPrintable(QString("ActiveFromOriginImpl::startGroup '%1'").arg(groupIdentifier)), "groupIdentifier's can't have '/'");
	_settings.beginGroup(groupIdentifier);
}

void ActiveFromOriginImpl::endGroup()
{
	_settings.endGroup();
}

bool ActiveFromOriginImpl::isActive(const char* identifier)
{
	Q_ASSERT_X(!QString(identifier).contains('/'), qPrintable(QString("ActiveFromOriginImpl::isActive '%1'").arg(identifier)), "identifier's can't have '/'");
	return _settings.value(identifier).toBool();
}

void ActiveFromOriginImpl::setActive(const char* identifier, bool active)
{
	Q_ASSERT_X(!QString(identifier).contains('/'), qPrintable(QString("ActiveFromOriginImpl::setActive '%1'").arg(identifier)), "identifier's can't have '/'");
	return _settings.setValue(identifier, active);
}
