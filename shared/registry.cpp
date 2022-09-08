#include "registry.h"

#include <qt_windows.h>

Registry::Registry()
{

}



/**
 *
 *
 *
 *
 * #include "registryqt.h"

/ Original author: Nikolai S | https://github.com/doublejim

  This file is released under the MIT license.
 /

QStringList RegistryQt::subkeys(const HKEY rootKey, const QString subkey)
{
	HKEY hKey;                              // Handle

	QStringList result;

	if (ERROR_SUCCESS == RegOpenKeyEx( rootKey, (LPCWSTR) subkey.utf16(), 0, KEY_READ, &hKey))
	{
		TCHAR achKey[MAX_KEY_LENGTH];       // Buffer for subkey name
		DWORD cSubKeys = 0;                 // Number of subkeys
		DWORD retCode;

		// Get the number of subkeys:

		RegQueryInfoKey(hKey, NULL, NULL, NULL, &cSubKeys, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

		// If there are any subkeys, we iterate through them, gathering their names.

		if (cSubKeys)
		{
			for (DWORD i = 0; i < cSubKeys; i++)
			{
				DWORD cbName = MAX_KEY_LENGTH;       // Size of name string

				// Find the name of the key at index i:

				retCode = RegEnumKeyEx(hKey, i, achKey, &cbName, NULL, NULL, NULL, NULL);

				// Append key name to results:

				if (retCode == ERROR_SUCCESS)
					result.append( QString::fromWCharArray(achKey));
			}
		}
	}

	RegCloseKey(hKey);

	return result;
}

bool RegistryQt::insertValue( const HKEY rootKey, const QString subkey, const QString valueName, const BYTE* value, const DWORD valueType, const int sizeOfValue)
{
	HKEY hKey;           // Handle
	bool okay = true;

	if (ERROR_SUCCESS == RegCreateKeyEx( rootKey, (LPCWSTR) subkey.utf16(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL))
	{
		DWORD retCode = RegSetValueEx( hKey, (LPCWSTR) valueName.utf16(), 0, valueType, value, sizeOfValue);

		if (retCode != ERROR_SUCCESS)
			okay = false;
	} else {
		okay = false;
	}
	RegCloseKey(hKey);

	return okay;
}

bool RegistryQt::insertKey(const HKEY rootKey, const QString subkey)
{
	HKEY hKey;           // Handle
	bool okay = true;

	if (ERROR_SUCCESS != RegCreateKeyEx( rootKey, (LPCWSTR) subkey.utf16(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL))
		okay = false;

	RegCloseKey(hKey);
	return okay;
}

bool RegistryQt::insertValueDWORD(const HKEY rootKey, const QString subkey, const QString valueName, const DWORD& value)
{
	return insertValue( rootKey, subkey, valueName, (const BYTE*) &value, REG_DWORD, sizeof(DWORD));
}

#ifdef Q_PROCESSOR_X86_64
bool RegistryQt::insertValueQWORD(const HKEY rootKey, const QString subkey, const QString valueName, const QWORD& value)
{
	return insertValue( rootKey, subkey, valueName, (const BYTE*) &value, REG_QWORD, sizeof(QWORD));
}
#endif

bool RegistryQt::insertValueSZ(const HKEY rootKey, const QString subkey, const QString valueName, const QString& value)
{
	return insertValue( rootKey, subkey, valueName, (const BYTE*) value.utf16(), REG_SZ, value.size() * sizeof(ushort));
}

bool RegistryQt::insertValueMultiSZ(const HKEY rootKey, const QString subkey, const QString valueName, const QStringList &value)
{
	QString combinedData;

	for (const QString& str : value)
		combinedData.append( str + QChar('\0'));
	combinedData.append(QChar('\0'));

	return insertValue( rootKey, subkey, valueName, (const BYTE*) combinedData.utf16(), REG_MULTI_SZ, combinedData.size() * sizeof(ushort));
}

bool RegistryQt::insertValueExpandSZ(const HKEY rootKey, const QString subkey, const QString valueName, const QString& value)
{
	return insertValue( rootKey, subkey, valueName, (const BYTE*) value.utf16(), REG_EXPAND_SZ, value.size() * sizeof(ushort));
}

bool RegistryQt::insertValueBinary( const HKEY rootKey, const QString subkey, const QString valueName, const QByteArray& value)
{
	return insertValue( rootKey, subkey, valueName, (const BYTE*) value.constData(), REG_BINARY, value.size() * sizeof(BYTE));
}

RegValue RegistryQt::value(const HKEY rootKey, const QString subkey, const QString valueName)
{
	BYTE* data = new BYTE[MAX_KEY_LENGTH];      // Deleted by RegistryValueInfo after it has been copied.
	DWORD cbData = MAX_KEY_LENGTH;
	DWORD type;
	HKEY hKey;
	bool okay = true;

	DWORD retCode = RegOpenKeyEx( rootKey, (LPCWSTR) subkey.utf16(), 0, KEY_READ, &hKey);

	if (retCode == ERROR_SUCCESS)       // Directory existed.
	{
		// Retrieve value.
		retCode = RegQueryValueEx( hKey, (LPCWSTR) valueName.utf16(), 0, &type, data, &cbData);

		switch(retCode)
		{
		case ERROR_MORE_DATA:           // The 255 bytes aren't enough. Allocate the necessary amount.
		{
			delete[] data;
			data = new BYTE[cbData];
			retCode = RegQueryValueEx( hKey, (LPCWSTR) valueName.utf16(), 0, &type, data, &cbData);
		}
		default: break;
		}
	}

	if (retCode != ERROR_SUCCESS)
		okay = false;

	RegCloseKey(hKey);

	return RegValue( retCode, data, cbData, type);
}

QStringList RegistryQt::valueNames( const HKEY rootKey, const QString subkey)
{
	HKEY hKey;

	QMap<QString,bool> result;      // The bool isn't used. I just need to sort the strings.

	DWORD retCode = RegOpenKeyEx( rootKey, (LPCWSTR) subkey.utf16(), 0, KEY_READ, &hKey);

	if (retCode == ERROR_SUCCESS)                       // Directory existed.
	{
		DWORD cValues = 0;                              // number of values

		// Get number of values in the key.
		RegQueryInfoKey(hKey, NULL, NULL, NULL, NULL, NULL, NULL, &cValues, NULL, NULL, NULL, NULL);

		for (DWORD i = 0; i < cValues; ++i)
		{
			TCHAR valueName[MAX_KEY_LENGTH];            // Buffer for value name
			DWORD cchValueName = MAX_KEY_LENGTH;        // Size of name string

			retCode = RegEnumValue(hKey, i, valueName, &cchValueName, NULL, NULL, NULL, NULL);

			if (retCode != ERROR_SUCCESS)
				break;

			result.insert( QString::fromWCharArray(valueName), true );      // true isn't used for anything.
		}
	}

	RegCloseKey(hKey);

	return result.keys();
}

void RegistryQt::removeKey(const HKEY rootKey, const QString subkey)
{
	HKEY hKey;

	if (ERROR_SUCCESS == RegOpenKeyEx( rootKey, (LPCWSTR) subkey.utf16(), 0, KEY_READ, &hKey))
	{
		DWORD cSubKeys = 0;                  // number of subkeys

		// bool innerRes = true;

		// Get the number of subkeys:

		RegQueryInfoKey(hKey, NULL, NULL, NULL, &cSubKeys, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

		if (cSubKeys)                                   // If there are any subkeys:
		{                                               // Go to each subkey.
			for (int i = cSubKeys - 1; i >= 0; --i)     // Find the name of the key at index i. Start at the highest index,
			{                                           // then delete lower and lower indices until (including) index 0.
				TCHAR achKey[MAX_KEY_LENGTH];           // Buffer for subkey name
				DWORD cName = MAX_KEY_LENGTH;          // Size of name string

				DWORD retCode = RegEnumKeyEx(hKey, i, achKey, &cName, NULL, NULL, NULL, NULL);

				if (retCode == ERROR_SUCCESS)
				{
					QString next_subkey = subkey + "\\" + QString::fromWCharArray(achKey);
					removeKey( rootKey, next_subkey);
				}
			}
		}
		RegDeleteKey( rootKey, (LPCWSTR) subkey.utf16());
	}
	RegCloseKey(hKey);
}

bool RegistryQt::valueExists(const HKEY rootKey, const QString subkey, const QString valueName)
{
	HKEY hKey;

	bool result = false;

	DWORD retCode = RegOpenKeyEx( rootKey, (LPCWSTR) subkey.utf16(), 0, KEY_READ, &hKey);

	if (retCode == ERROR_SUCCESS)       // Directory existed.
	{
		// Retrieve value.
		retCode = RegQueryValueEx( hKey, (LPCWSTR) valueName.utf16(), 0, NULL, NULL, NULL);

		// If it worked out, the value actually existed.
		if (retCode == ERROR_SUCCESS)
			result = true;
	}

	RegCloseKey(hKey);

	return result;
}

bool RegistryQt::keyExists(const HKEY rootKey, const QString subkey)
{
	HKEY hKey;                              // Handle

	bool result = false;

	if (ERROR_SUCCESS == RegOpenKeyEx( rootKey, (LPCWSTR) subkey.utf16(), 0, KEY_READ, &hKey))
		result = true;

	RegCloseKey(hKey);

	return result;
}
*/
