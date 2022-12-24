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

#ifndef REGISTRYSTRATEGY_H
#define REGISTRYSTRATEGY_H

#include <string>
#include <QString>


struct RegistryKey
{
	int root;
	std::string path;

	RegistryKey() { root = 0; }
};

enum RegistryActionValueType {
	Number,
	String,
	Null
};

struct RegistryActionValue {

	RegistryActionValueType type; // String / DWord / delete
	std::string subPath;
	std::string name;
	qint32 number;  // --> TODO QVariant..
	std::string string;

	RegistryActionValue(const std::string& subPath = "")
		: type(Null), subPath(subPath) {}
	RegistryActionValue(const std::string& name, qint32 n, const std::string& subPath = "")
		: type(Number), name(name), number(n), subPath(subPath) {}
	RegistryActionValue(const std::string& name, const std::string& str, const std::string& subPath = "")
		: type(String), name(name), string(str), subPath(subPath) {}
};

class RegistryStrategy;

class RegistryAction
{
public:
	RegistryActionValue get();
	bool equalsTo(const RegistryActionValue& value) const;
	void setTo(const RegistryActionValue& value);
protected:
	RegistryAction(RegistryStrategy *parent);

private:
	RegistryStrategy* _parent;
	friend class RegistryStrategy;
};

class RegistryStrategy
{
public:
	RegistryStrategy(const RegistryKey& key);

	RegistryKey key() const;
	RegistryAction currentValue();
	RegistryActionValue activeValue() const;
	RegistryActionValue deactiveValue() const;

	static RegistryKey currentUser(const char* subKey);
	static RegistryKey classesRoot(const char* subKey);
	static RegistryKey localMachine(const char* subKey);

private:
	RegistryKey _key;
	RegistryActionValue _activeValue;
	RegistryActionValue _deactiveValue;
	friend class RegistryBuilder;
};



class RegistryBuilder
{
public:
	RegistryBuilder(const RegistryKey& key)
		: _registry(key){ }

	operator RegistryStrategy() const { return std::move(_registry); }

	RegistryBuilder& activeValue(const RegistryActionValue& value) {
		_registry._activeValue = std::move(value);
		return *this;
	}
	RegistryBuilder& deactiveValue(const RegistryActionValue& value) {
		_registry._deactiveValue = std::move(value);
		return *this;
	}

private:
	RegistryStrategy _registry;
};

#endif // REGISTRYSTRATEGY_H
