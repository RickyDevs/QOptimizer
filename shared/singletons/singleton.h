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

#ifndef SINGLETON_H
#define SINGLETON_H

#include <functional>
#include <memory>

namespace singleton_util {

void registerImplementation(const std::type_info& typeInfo, std::function<void*()> createFn);
void* createInstance(const std::type_info& typeInfo);

}

template <typename I>
class Singleton
{
public:
	static I& instance();
	static void registerImplementation(std::function<I*()> createFn);

protected:
	Singleton() = default;
	//~Singleton() = default;
    Singleton( const Singleton& ) = delete;
    Singleton& operator=( const Singleton& ) = delete;
};

template <typename I>
inline I& Singleton<I>::instance()
{
	static std::unique_ptr<I> theInstance(static_cast<I*>(singleton_util::createInstance(typeid(I))));
	return *theInstance;
}

template <typename I>
void Singleton<I>::registerImplementation(std::function<I*()> createFn)
{
	singleton_util::registerImplementation(typeid(I), createFn);
}

#endif // SINGLETON_H
