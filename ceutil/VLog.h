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

#ifndef __VLOG_H__
#define __VLOG_H__

#ifdef __cplusplus
extern "C" {
#endif

char CELog_SendString(char const* str);
__attribute__((format(printf, 2, 3)))
void VLog(char const* prefix_str, char const* fmt, ...);
void CEGetScreenSize(unsigned short* width, unsigned short* height);

#ifdef __cplusplus
}
#endif

#endif /* __VLOG_H__ */
