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

#include "singleton.h"
#include <QtGlobal>
#include <unordered_map>
#include <typeindex>

namespace singleton_util {

static std::unordered_map<size_t, std::function<void*()>> _singletonRegistry;

void registerImplementation(const std::type_info& typeInfo, std::function<void*()> createFn)
{
	_singletonRegistry[typeInfo.hash_code()] = createFn;
}

void* createInstance(const std::type_info& typeInfo)
{
	auto createFnIt = _singletonRegistry.find(typeInfo.hash_code());
	Q_ASSERT_X(createFnIt != _singletonRegistry.end(), "Create singleton class", std::type_index(typeInfo).name());
	return createFnIt->second();
}

}



