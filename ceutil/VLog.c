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

#include <stdarg.h>
#include <string.h>
#ifdef KERNEL
#include <libkern/libkern.h>
#include <IOKit/IOLib.h>
#else
#include <stdio.h>
#endif
#include "VLog.h"

#define VLOG_BUF_SIZE 256

__attribute__((visibility("hidden"), format(printf, 2, 3)))
void VLog(char const* prefix_str, char const* fmt, ...)
{
	va_list ap;
	size_t l;
	char print_buf[VLOG_BUF_SIZE];

	va_start(ap, fmt);
	l = strlcpy(&print_buf[0], "log ", sizeof print_buf);
	l += strlcpy(&print_buf[l], prefix_str, sizeof print_buf - l);
	vsnprintf(&print_buf[l], sizeof print_buf - l, fmt, ap);
	va_end(ap);
#if defined(KERNEL) && defined(VLOG_LOCAL)
	IOLog("%s", &print_buf[4]);
#endif
	CELog_SendString(&print_buf[0]);
}
