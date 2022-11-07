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

#ifndef TAGSHELPER_H
#define TAGSHELPER_H

#define TAGS1(k0)         k0
#define TAGS2(k0, k1)     k0 " " k1
#define TAGS3(k0, k1, k2) k0 " " k1 " " k2

#define HEADER_TAG(k0)    k0 "_HEADER"
#define ITEM_TAG(k0)      k0 "_ITEM"


#define k_tagBIOS        "BIOS"
#define k_tagDiskDrive   "DRIVE"
#define k_tagGraphics    "GRAPHIC"
#define k_tagMemory      "MEMORY"
#define k_tagMotherboard "BOARD"
#define k_tagNetwork     "NETWORK"
#define k_tagProcessor   "PROCESSOR"
#define k_tagWindows     "WINDOWS"




#endif // TAGSHELPER_H
