#ifndef ENUMS_H
#define ENUMS_H


enum class LogType
{
	Information,
	Error,
};

enum WindowsVersion
{
	Unsupported,
	Windows7 = 7,
	Windows8 = 8,
	Windows10 = 10,
	Windows11 = 11
};

enum class StartupItemLocation
{
	Folder,
	HKLM,
	HKLMWoW,
	HKCU
};

enum StartupItemType
{
	None,
	Run,
	RunOnce
};

enum class MessageType
{
	Error,
	Startup,
	Restart,
	Hosts,
	Integrator
};

enum class DesktopItemType
{
	Program,
	Folder,
	Link,
	File,
	Command
};

enum DesktopTypePosition
{
	Top,
	Middle,
	Bottom
};

enum Theme
{
	Amethyst,
	Azurite,
	Amber,
	Ruby,
	Jade,
	Silver
};

enum RecycleFlag : int
{
	SHERB_NOCONFIRMATION = 0x00000001,
	SHERB_NOPROGRESSUI = 0x00000001,
	SHERB_NOSOUND = 0x00000004
};

enum class ToggleSwitchAlignment
{
	Near,
	Center,
	Far
};

enum class ToggleSwitchButtonAlignment
{
	Left,
	Center,
	Right
};

#endif // ENUMS_H
