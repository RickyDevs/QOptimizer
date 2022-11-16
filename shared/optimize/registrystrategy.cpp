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

#include "registrystrategy.h"

#include "registryutil.h"

RegistryAction::RegistryAction(RegistryStrategy *parent)
	: _parent(parent)
{

}

bool RegistryAction::equalsTo(const RegistryActionValue& value) const
{
	std::string path = _parent->key().path;
	if (!value.subPath.empty()) {
		path += "\\" + value.subPath;
	}
	QVariant v = registry_util::get(path.c_str());

	switch (value.type) {
	case Number:
	case String:
		return (v.toString() == value.string.c_str());
	case Null:
// TODO
		break;
	}
	return false; //TODO
}

void RegistryAction::setTo(const RegistryActionValue& value)
{
	std::string path = _parent->key().path;
	if (!value.subPath.empty()) {
		path += "\\" + value.subPath;
	}

	switch (value.type) {
	case Number:
	case String:
		registry_util::set(path.c_str(), QVariant(value.string.c_str()));

		break;
	case Null:
// TODO
		registry_util::remove(path.c_str());
		break;
	default:
		Q_ASSERT(false);
		break;
	}
}

RegistryStrategy::RegistryStrategy(const RegistryKey& key)
	: _key(key)
{
}

RegistryKey RegistryStrategy::currentUser(const char* subKey)
{
	RegistryKey key;
	key.root = RegistryKeyEnum::currentUser;
	key.path = subKey;
	return key;
}

RegistryKey RegistryStrategy::classesRoot(const char* subKey)
{
	RegistryKey key;
	key.root = RegistryKeyEnum::classesRoot;
	key.path = subKey;
	return key;
}

RegistryKey RegistryStrategy::localMachine(const char* subKey)
{
	RegistryKey key;
	key.root = RegistryKeyEnum::localMachine;
	key.path = subKey;
	return key;
}

RegistryKey RegistryStrategy::key() const
{
	return _key;
}

RegistryActionValue RegistryStrategy::activeValue() const
{
	return _activeValue;
}

RegistryAction RegistryStrategy::currentValue()
{
	return RegistryAction(this);
}

RegistryActionValue RegistryStrategy::deactiveValue() const
{
	return _deactiveValue;
}
