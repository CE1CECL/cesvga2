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

#ifndef __GLDDATA_H__
#define __GLDDATA_H__

#ifdef __cplusplus
extern "C" {
#endif

extern char const BNDL1[];
extern char const BNDL2[];
extern char const LIBGLIMAGE[];
extern char const LIBGLPROGRAMMABILITY[];

extern void* bndl_handle[2];

extern GLD_GENERIC_FUNC bndl_ptrs[2][NUM_ENTRIES];

extern GLD_GENERIC_DISPATCH remote_dispatch[33];

#if LOGGING_LEVEL >= 1
extern int logLevel;
#endif

extern int bndl_index;

extern glr_io_data_t glr_io_data;

extern libglimage_t libglimage;

extern libglprogrammability_t libglprogrammability;

#ifdef __cplusplus
}
#endif

#endif /* __GLDDATA_H__ */
