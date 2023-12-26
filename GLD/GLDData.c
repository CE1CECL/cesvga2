/*

    CEsvga2 - ChrisEric1 Super Video Graphics Array 2
    Copyright (C) 2023-2024, Christopher Eric Lentocha

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include <IOKit/IOKitLib.h>
#include "EntryPointNames.h"
#include "GLDTypes.h"
#include "GLDData.h"

#pragma GCC visibility push(hidden)

char const BNDL1[] = "/System/Library/Extensions/AppleIntelGMA950GLDriver.bundle/Contents/MacOS/AppleIntelGMA950GLDriver";
char const BNDL2[] = "/System/Library/Frameworks/OpenGL.framework/Resources/GLRendererFloat.bundle/GLRendererFloat";
char const LIBGLIMAGE[] = "/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGLImage.dylib";
char const LIBGLPROGRAMMABILITY[] = "/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGLProgrammability.dylib";

void* bndl_handle[2];

GLD_GENERIC_FUNC bndl_ptrs[2][NUM_ENTRIES];

GLD_GENERIC_DISPATCH remote_dispatch[33];

#if LOGGING_LEVEL >= 1
int logLevel = LOGGING_LEVEL;
#endif

int bndl_index;

glr_io_data_t glr_io_data;

libglimage_t libglimage;

libglprogrammability_t libglprogrammability;

#pragma GCC visibility pop
