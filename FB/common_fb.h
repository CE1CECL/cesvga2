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

#ifndef __CESVGA2_COMMON_FB_H__
#define __CESVGA2_COMMON_FB_H__

#define NUM_DISPLAY_MODES 1
#define CUSTOM_MODE_ID 1

#ifdef __cplusplus
extern "C" {
#endif

struct DisplayModeEntry
{
	unsigned width;
	unsigned height;
	unsigned flags;
};

struct CustomModeData
{
	unsigned flags;
	unsigned width;
	unsigned height;
};

extern DisplayModeEntry const modeList[NUM_DISPLAY_MODES] __attribute__((visibility("hidden")));

extern int logLevelFB;

#ifdef __cplusplus
}
#endif

#endif /* __CESVGA2_COMMON_FB_H__ */
