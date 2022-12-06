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

#ifndef ACTIVEFROMORIGINIMPL_H
#define ACTIVEFROMORIGINIMPL_H

#include "iactivefromorigin.h"

#include <QSettings>

class ActiveFromOriginImpl : public IActiveFromOrigin
{
public:
	static ActiveFromOriginImpl* create();

	bool shouldRunProcess() override;

	void startGroup(const char* groupIdentifier) override;
	void endGroup() override;

	bool isActive(const char* identifier) override;
	void setActive(const char* identifier, bool active) override;

private:
	ActiveFromOriginImpl() = default;

	QSettings _settings;
};

#endif // ACTIVEFROMORIGINIMPL_H
