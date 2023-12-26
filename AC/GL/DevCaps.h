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

#ifndef __DEVCAPS_H__
#define __DEVCAPS_H__

#ifdef __cplusplus
extern "C" {
#endif

uint32_t* allocGPUCaps(void);
void freeGPUCaps(uint32_t* accelBlock);
void dumpGPUCaps(uint32_t* const accelBlock);
void getGPUCaps(uint32_t const* deviceBlock, uint32_t* accelBlock);

#ifdef __cplusplus
}
#endif

#endif /* __DEVCAPS_H__ */
