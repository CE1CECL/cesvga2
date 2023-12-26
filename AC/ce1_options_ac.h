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

#ifndef __CE1_OPTIONS_AC_H__
#define __CE1_OPTIONS_AC_H__

#define CE1_OPTION_AC_SURFACE_CONNECT		0x0001
#define CE1_OPTION_AC_2D_CONTEXT			0x0002
#define CE1_OPTION_AC_GL_CONTEXT			0x0004
#define CE1_OPTION_AC_DVD_CONTEXT			0x0008

#define CE1_OPTION_AC_SVGA3D				0x0010
#define CE1_OPTION_AC_NO_YUV				0x0020
#define CE1_OPTION_AC_DIRECT_BLIT			0x0040
#define CE1_OPTION_AC_NO_SCREEN_OBJECT		0x0080
#define CE1_OPTION_AC_QE					0x0100
#define CE1_OPTION_AC_PACKED_BACKING		0x0200
#define CE1_OPTION_AC_REGION_BOUNDS_COPY	0x0400

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned ce1_options_ac;

static inline int checkOptionAC(unsigned mask)
{
	return (ce1_options_ac & mask) != 0U;
}
	
#ifdef __cplusplus
}
#endif

#endif /* __CE1_OPTIONS_AC_H__ */
