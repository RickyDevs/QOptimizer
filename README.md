# QOptimizer
QOptimizer is Windows utility to optimize it for performance and customize Windows to your needs.
Useful after a clean installation, or to enable/disable/tweak services (and settings) that you actually need for a daily use.
It started to be just a port of the Windows Optimizer (by hellzerg) to Qt5.

 > Personal thought: 
 > Windows, after installation, is configured in a way that tries to fill every type of user needs. Even though most services are idle, they aren't footprint free, they take very little CPU and memory power, but multiply that by millions of users worldwide and every day... In the end, that amounts to a more significant wasted energy.

**The project is in a Under Development state, and is not ready for any practical use.**

### Summary:
* **NOT** .NET Framework dependent
* Portable (command line and Windows UI versions)
* No hidden/obscured optimizations [^1]

## Roadmap
 * Generic Optimize manager (ONGOING)
 * Profiles
 * Apps UWP
 * Most common app install 
 * Optimize recomendations (based on hardware and others)
 * Other ideias...

## Architecture
QOptimizer consists of the following components:
- **QOptimizer** - provides a Windows UI 
- **QOptimizerCmd** - provides a command line 

## Requirements
- Windows 7, 8, 10, 11

## Authors
RickyDevs

## License
Node.qml is available under the terms of the GNU General Public License version 3 (GPLv3).

[^1]: All optimizations are user driven and each have enough description in order to let the user make an informed decision

