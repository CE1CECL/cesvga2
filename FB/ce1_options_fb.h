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

#ifndef __CE1_OPTIONS_FB_H__
#define __CE1_OPTIONS_FB_H__

#define CE1_OPTION_FB_FIFO_INIT			0x01U
#define CE1_OPTION_FB_REFRESH_TIMER		0x02U
#define CE1_OPTION_FB_ACCEL				0x04U
#define CE1_OPTION_FB_CURSOR_BYPASS_2	0x08U
#define CE1_OPTION_FB_REG_DUMP			0x10U

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned ce1_options_fb;

static inline int checkOptionFB(unsigned mask)
{
	return (ce1_options_fb & mask) != 0U;
}

#ifdef __cplusplus
}
#endif

#endif /* __CE1_OPTIONS_FB_H__ */
